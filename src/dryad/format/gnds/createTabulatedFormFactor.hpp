#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDFORMFACTOR
#define NJOY_DRYAD_FORMAT_GNDS_CREATETABULATEDFORMFACTOR

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/createInterpolationType.hpp"
#include "dryad/format/gnds/convertEnergies.hpp"
#include "dryad/format/gnds/readXYs1d.hpp"
#include "dryad/TabulatedFormFactor.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a TabulatedFormFactor from a GNDS node
   */
  static TabulatedFormFactor
  createTabulatedFormFactor( pugi::xml_node node ) {

    std::vector< double > energies;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< InterpolationType > interpolants;

    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the form factor data
      auto data = readXYs1D( node );

      // get the interpolation type
      auto interpolant = createInterpolationType( std::get< 6 >( data ) );

      // convert units - if necessary
      convertEnergies( std::get< 2 >( data ), std::get< 3 >( data ) );

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

      Log::error( "Expected an XYs1d or regions1d node for tabulated form factor data" );
      throw std::exception();
    }

    return TabulatedFormFactor(
             std::move( energies ), std::move( values ),
             std::move( boundaries ), std::move( interpolants ) );
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
