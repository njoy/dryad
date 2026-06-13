#ifndef NJOY_FORMAT_GNDS_READ_CREATETABULATEDAVERAGEENERGY
#define NJOY_FORMAT_GNDS_READ_CREATETABULATEDAVERAGEENERGY

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedAverageEnergy.hpp"
#include "njoy/format/gnds/read/createInterpolationType.hpp"
#include "njoy/format/gnds/read/readXYs1d.hpp"
#include "njoy/format/gnds/read/convertEnergies.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a TabulatedAverageEnergy from a GNDS average node
   */
  inline dryad::TabulatedAverageEnergy
  createTabulatedAverageEnergy( const pugi::xml_node& average,
                                const std::string& style = "eval" ) {

    std::vector< double > energies;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< dryad::InterpolationType > interpolants;

    // check that this is a valid average energy node
    throwExceptionOnWrongNode( average, "averageProductEnergy" );

    auto node = average.find_child_by_attribute( "label", style.c_str() );
    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the average energy data
      auto data = readXYs1D( node );

      // get the interpolation type
      auto interpolant = createInterpolationType( std::get< 6 >( data ) );

      // convert units - if necessary
      convertEnergies( std::get< 2 >( data ), std::get< 3 >( data ) );
      convertEnergies( std::get< 4 >( data ), std::get< 5 >( data ) );

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
        convertEnergies( std::get< 4 >( data ), std::get< 5 >( data ) );

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

      Log::error( "Expected either an XYs1d node or regions1d node with XYs1d nodes"
                  "for average energy data" );
      throw std::exception();
    }

    return dryad::TabulatedAverageEnergy(
             std::move( energies ), std::move( values ),
             std::move( boundaries ), std::move( interpolants ) );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
