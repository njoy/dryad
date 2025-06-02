#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDCROSSSECTION
#define NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createInterpolationType.hpp"
#include "dryad/format/gnds/readXYs1d.hpp"
#include "dryad/format/gnds/convertEnergies.hpp"
#include "dryad/format/gnds/convertCrossSections.hpp"
#include "dryad/TabulatedCrossSection.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a TabulatedCrossSection from a GNDS XYs1d or regions1d node
   */
  static TabulatedCrossSection
  createTabulatedCrossSectionFromNodes( const pugi::xml_node& node ) {

    std::vector< double > energies;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< InterpolationType > interpolants;

    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the cross section data
      auto data = readXYs1D( node );

      // get the interpolation type
      auto interpolant = createInterpolationType( std::get< 6 >( data ) );

      // convert units - if necessary
      convertEnergies( std::get< 2 >( data ), std::get< 3 >( data ) );
      convertCrossSections( std::get< 4 >( data ), std::get< 5 >( data ) );

      // assign data
      energies = std::move( std::get< 2 >( data ) );
      values = std::move( std::get< 4 >( data ) );
      boundaries.emplace_back( energies.size() - 1 );
      interpolants.emplace_back( interpolant );
    }
    else if ( strcmp( node.name(), "regions1d" ) == 0 ) {

      // get the units
      auto units = readAxes( node.child( "axes" ) );

      // loop over the children of function1ds
      pugi::xml_node function1ds = node.child( "function1ds" );
      for ( pugi::xml_node xys1d = function1ds.child( "XYs1d" );
            xys1d; xys1d = xys1d.next_sibling(  "XYs1d"  ) ) {

        // read the current interpolation region
        auto data = readXYs1D( xys1d, units );

        // get the interpolation type
        auto interpolant = createInterpolationType( std::get< 6 >( data ) );

        // convert units - if necessary
        convertEnergies( std::get< 2 >( data ), std::get< 3 >( data ) );
        convertCrossSections( std::get< 4 >( data ), std::get< 5 >( data ) );

        // check for duplicate points at interpolation region boundaries
        std::size_t offset = 0;
        if ( energies.size() > 0 ) {

          if ( energies.back() == std::get< 2 >( data ).front() &&
               values.back() == std::get< 4 >( data ).front() ) {

            offset = 1;
          }
        }

        // grow the data accordingly
        energies.insert( energies.end(), std::get< 2 >( data ).begin() + offset, std::get< 2 >( data ).end() );
        values.insert( values.end(), std::get< 4 >( data ).begin() + offset, std::get< 4 >( data ).end() );
        boundaries.emplace_back( energies.size() - 1 );
        interpolants.emplace_back( interpolant );
      }
    }
    else {

      Log::error( "Expected either an XYs1d node or regions1d node with XYs1d nodes "
                  "for cross section data" );
      throw std::exception();
    }

    return TabulatedCrossSection(
             std::move( energies ), std::move( values ),
             std::move( boundaries ), std::move( interpolants ) );
  }

  /**
   *  @brief Create a TabulatedCrossSection from a GNDS cross section node
   */
  static TabulatedCrossSection
  createTabulatedCrossSection( const pugi::xml_node& xs,
                               const std::string& style = "eval" ) {

    Log::info( "Reading cross section data" );

    // check that this is a valid crossSection node
    throwExceptionOnWrongNode( xs, "crossSection" );

    auto node = xs.find_child_by_attribute( "label", style.c_str() );
    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // return a cross section
      return createTabulatedCrossSectionFromNodes( node );
    }
    else if ( strcmp( node.name(), "regions1d" ) == 0 ) {

      // return a cross section
      return createTabulatedCrossSectionFromNodes( node );
    }
    else if ( strcmp( node.name(), "resonancesWithBackground" ) == 0 ) {

      // get the resolved background data
      auto resolved = node.child( "background" ).child( "resolvedRegion" );
      auto result = createTabulatedCrossSectionFromNodes( resolved.first_child() );

      // start to assemble the data together
      std::vector< double > energies = result.energies();
      std::vector< double > values = result.values();
      std::vector< std::size_t > boundaries = result.boundaries();
      std::vector< InterpolationType > interpolants = result.interpolants();

      // get the unresolved background data
      auto unresolved = node.child( "background" ).child( "unresolvedRegion" );
      if ( unresolved ) {

        result = createTabulatedCrossSectionFromNodes( unresolved.first_child() );

        // check for duplicate points at interpolation region boundaries
        std::size_t offset = 0;
        if ( energies.back() == result.energies().front() &&
             values.back() == result.values().front() ) {

          offset = 1;
        }

        // add data
        std::size_t size = energies.size();
        energies.insert( energies.end(), result.energies().begin() + offset, result.energies().end() );
        values.insert( values.end(), result.values().begin() + offset, result.values().end() );
        for ( unsigned int i = 0; i < result.numberRegions(); ++i ) {

          boundaries.emplace_back( result.boundaries()[i] - offset + size );
          interpolants.emplace_back( result.interpolants()[i] );
        }
      }

      // get the fast background data
      auto fast = node.child( "background" ).child( "fastRegion" );

      result = createTabulatedCrossSectionFromNodes( fast.first_child() );

      // check for duplicate points at interpolation region boundaries
      std::size_t offset = 0;
      if ( energies.back() == result.energies().front() &&
           values.back() == result.values().front() ) {

        offset = 1;
      }

      // add data
      std::size_t size = energies.size();
      energies.insert( energies.end(), result.energies().begin() + offset, result.energies().end() );
      values.insert( values.end(), result.values().begin() + offset, result.values().end() );
      for ( unsigned int i = 0; i < result.numberRegions(); ++i ) {

        boundaries.emplace_back( result.boundaries()[i] - offset + size );
        interpolants.emplace_back( result.interpolants()[i] );
      }

      return TabulatedCrossSection(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    else {

      Log::error( "Expected either an XYs1d, regions1d (with XYs1d nodes) or a "
                  "background node for cross section data" );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
