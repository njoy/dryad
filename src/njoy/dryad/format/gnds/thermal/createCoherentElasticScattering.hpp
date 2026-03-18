#ifndef NJOY_DRYAD_FORMAT_GNDS_THERMAL_CREATECOHERENTELASTICSCATTERING
#define NJOY_DRYAD_FORMAT_GNDS_THERMAL_CREATECOHERENTELASTICSCATTERING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/CoherentElasticScattering.hpp"
#include "njoy/dryad/format/gnds/convertTemperatures.hpp"
#include "njoy/dryad/format/gnds/convertEnergies.hpp"
#include "njoy/dryad/format/gnds/readAxes.hpp"
#include "njoy/dryad/format/gnds/readArray.hpp"
#include "njoy/dryad/format/createVector.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace thermal {

  /**
   *  @brief Create an CoherentElasticScattering from a GNDS tsl node
   *
   *  @param[in] tsl   the GNDS tsl node
   */
  inline dryad::thermal::CoherentElasticScattering
  createCoherentElasticScattering( const pugi::xml_node& tsl ) {

    Log::info( "Reading coherent elastic scattering data" );

    // check that this is a valid coherent elastic thermal scattering node
    throwExceptionOnWrongNode( tsl, "thermalNeutronScatteringLaw_coherentElastic" );

    // get the Debye-Waller integral
    auto node = tsl.first_child();
    if ( strcmp( node.name(), "S_table" ) == 0 ) {

      // get the axes and array data
      auto axes = readAxes( node.child( "gridded2d" ).child( "axes" ) );
      auto data = readArray( node.child( "gridded2d" ).child( "array" ) );

      // temperatures are the first entry
      auto temperatures = std::get< 2 >( axes[0] ).value();
      convertTemperatures( temperatures, std::get< 1 >( axes[0] ).value() );

      // energies are the second entry
      auto energies = std::get< 2 >( axes[1] ).value();
      convertEnergies( energies, std::get< 1 >( axes[1] ).value() );

      // extract Bragg edge data
      auto number_temperatures = temperatures.size();
      auto number_energies = energies.size();
      std::vector< dryad::thermal::BraggEdgeData > edges;
      for ( std::size_t i = 0; i < number_temperatures; ++i ) {

        std::vector< double > values;
        values.reserve( number_energies );
        for ( std::size_t j = 0; j < number_energies; ++j ) {

          values.emplace_back( data( i, j ) );
        }

        //! @todo convert values to ev barns

        edges.emplace_back( temperatures[i], energies, std::move( values ) );

      }

      return dryad::thermal::CoherentElasticScattering( std::move( edges ) );
    }
    else if ( strcmp( node.name(), "BraggEdges" ) == 0 ) {

      Log::error( "Found a BraggEdges node, not yet implemented, contact a developer",
                  node.name() );
      throw std::exception();
    }
    else {

      Log::error( "Expected either an S_table node or BraggEdges node, found \'{}\'",
                  node.name() );
      throw std::exception();
    }

    throw std::exception();
  }

} // thermal namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
