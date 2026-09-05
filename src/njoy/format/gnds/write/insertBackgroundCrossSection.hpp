#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTBACKGROUNDCROSSSECTION
#define NJOY_FORMAT_GNDS_WRITE_INSERTBACKGROUNDCROSSSECTION

// system includes
#include <algorithm>
#include <optional>
#include <string>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertTabulatedFunction.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a background region into a gnds node
   *
   *  @param[in,out] parent         the parent node
   *  @param[in]     option         the gnds write options
   *  @param[in]     energy         the end of the current region
   *  @param[in]     energies       the energy values
   *  @param[in]     values         the cross section values
   *  @param[in]     boundaries     the boundaries of the interpolation regions
   *  @param[in]     interpolants   the interpolation types of the interpolation regions
   *  @param[in]     table          the tabulated data
   *  @param[in]     name           the name of the current region
   */
  inline pugi::xml_node
  insertRegion( pugi::xml_node& parent,
                const Options& options,
                double energy,
                std::vector< double >& energies,
                std::vector< double >& values,
                std::vector< std::size_t >& boundaries,
                std::vector< dryad::InterpolationType >& interpolants,
                const dryad::TabulatedCrossSection& table,
                const std::string& name ) {

    // look for the upper limit of the resolved energy range
    auto eiter = std::lower_bound( energies.begin(), energies.end(), energy );
    std::size_t eindex = std::distance( energies.begin(), eiter );
    auto viter = std::next( values.begin(), eindex );
    auto biter = std::lower_bound( boundaries.begin(), boundaries.end(), eindex );
    std::size_t bindex = std::distance( boundaries.begin(), biter );
    auto iiter = std::next( interpolants.begin(), bindex );

    // if there is no such energy, insert it and adjust boundaries
    if ( eiter != energies.end() && *eiter != energy ) {

      eiter = energies.insert( eiter, energy );
      viter = values.insert( viter, table( energy ) );
      std::transform( biter, boundaries.end(), biter, [] ( auto&& boundary ) { return boundary + 1; } );
    }

    // get the data for this region
    std::vector< double > region_energies( energies.begin(), std::next( eiter ) );
    std::vector< double > region_values( values.begin(), std::next( viter ) );
    std::vector< std::size_t > region_boundaries( boundaries.begin(), std::next( biter ) );
    region_boundaries.back() = region_energies.size() - 1;
    std::vector< dryad::InterpolationType > region_interpolants( interpolants.begin(), std::next( iiter ) );
    std::size_t size = region_energies.size();

    // check for a jump
    if ( *eiter == *std::next( eiter ) ) {

      ++eiter;
      ++viter;
      ++biter;
      ++iiter;
      ++size;
    }

    // erase the data for this region and adjust remaining boundaries
    energies.erase( energies.begin(), eiter );
    values.erase( values.begin(), viter );
    boundaries.erase( boundaries.begin(), biter );
    std::transform( boundaries.begin(), boundaries.end(), boundaries.begin(),
                    [&] ( auto&& boundary ) { return boundary - size; } );
    interpolants.erase( interpolants.begin(), iiter );

    pugi::xml_node region = parent.append_child( name.c_str() );

    insertTabulatedFunction( region, options, region_energies, region_values,
                             region_boundaries, region_interpolants,
                             "incidentEnergy", "crossSection", "eV", "b" );

    return region;
  }

  /**
   *  @brief Insert a tabulated background cross section into a gnds node
   *
   *  @param[in,out] parent       the parent node
   *  @param[in]     option       the gnds write options
   *  @param[in]     table        the tabulated data
   *  @param[in]     resonances   the resonance parameters
   *  @param[in]     style        the style label to be used
   */
  inline pugi::xml_node
  insertBackgroundCrossSection( pugi::xml_node& parent,
                                const Options& options,
                                const dryad::TabulatedCrossSection& table,
                                const dryad::resonances::ResonanceParameters& resonances,
                                const std::string& style ) {

    pugi::xml_node node = parent.append_child( "crossSection" );

    pugi::xml_node resonancesWithBackground = node.append_child( "resonancesWithBackground" );
    resonancesWithBackground.append_attribute( "label" ) = style;

    pugi::xml_node resonances_node = resonancesWithBackground.append_child( "resonances" );
    resonances_node.append_attribute( "href" ) = "/reactionSuite/resonances";
    pugi::xml_node background = resonancesWithBackground.append_child( "background" );

    std::vector< double > energies = table.energies();
    std::vector< double > values = table.values();
    std::vector< std::size_t > boundaries = table.boundaries();
    std::vector< dryad::InterpolationType > interpolants = table.interpolants();

    // look for the upper limit of the resolved energy range
    double energy = energies.front();
    if ( resonances.resolved().size() > 0 ) {

      energy = resonances.resolved().back().upperEnergyLimit();
    }
    else if ( resonances.unresolved().has_value() ) {

      energy = resonances.unresolved()->lowerEnergyLimit();
    }
    else {

      throw std::runtime_error( "insertBackgroundCrossSection: This should be unreachable code, contact a developer" );
    }

    // insert the resolved region
    auto resolved = insertRegion( background, options, energy,
                                  energies, values, boundaries, interpolants,
                                  table, "resolvedRegion" );

    // insert the unresolved if it exists
    if ( resonances.unresolved().has_value() ) {

      // the upper energy of the unresolved energy limit
      energy = resonances.unresolved()->upperEnergyLimit();

      // insert the resolved region
      auto unresolved = insertRegion( background, options, energy,
                                      energies, values, boundaries, interpolants,
                                      table, "unresolvedRegion" );
    }

    // insert the remainder of the cross section data in the fast region
    pugi::xml_node fast = background.append_child( "fastRegion" );
    insertTabulatedFunction( fast, options, energies, values,
                             boundaries, interpolants,
                             "incidentEnergy", "crossSection", "eV", "b" );

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
