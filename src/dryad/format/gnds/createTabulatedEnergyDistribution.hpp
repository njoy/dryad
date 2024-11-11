#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDENERGYDISTRIBUTION
#define NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDENERGYDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createInterpolationType.hpp"
#include "dryad/format/gnds/convertEnergy.hpp"
#include "dryad/format/gnds/convertEnergies.hpp"
#include "dryad/format/gnds/readXYs1d.hpp"
#include "dryad/TabulatedEnergyDistribution.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a TabulatedEnergyDistribution from a GNDS XYs1d node
   */
  static std::pair< std::optional< double >, 
                    TabulatedEnergyDistribution >
  createTabulatedEnergyDistribution( pugi::xml_node node,
                                     const std::vector< std::string > units ) {

    std::optional< double > outer = std::nullopt;
    std::vector< double > energies;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< InterpolationType > interpolants;

    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the cross section data
      auto data = readXYs1D( node, units );

      // get the interpolation type
      auto interpolant = createInterpolationType( std::get< 6 >( data ) );

      // cosine and probability data does not need to be converted
      // convert outer domain value if necessary
      if ( std::get< 0 >( data ).has_value() ) {

        convertEnergy( std::get< 0 >( data ).value(), std::get< 1 >( data ).value() );
      }
      convertEnergies( std::get< 2 >( data ), std::get< 3 >( data ) );

      // assign data
      outer = std::move( std::get< 0 >( data ) );
      energies = std::move( std::get< 2 >( data ) );
      values = std::move( std::get< 4 >( data ) );
      boundaries.emplace_back( energies.size() - 1 );
      interpolants.emplace_back( interpolant );
    }
    else {

      Log::error( "Expected an XYs1d node for tabulated energy distribution data" );
      throw std::exception();
    }

    return { std::move( outer ), 
             TabulatedEnergyDistribution(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) ) };
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
