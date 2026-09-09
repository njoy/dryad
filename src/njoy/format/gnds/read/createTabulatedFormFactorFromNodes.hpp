#ifndef NJOY_FORMAT_GNDS_READ_CREATETABULATEDFORMFACTORFROMNODES
#define NJOY_FORMAT_GNDS_READ_CREATETABULATEDFORMFACTORFROMNODES

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedFormFactor.hpp"
#include "njoy/format/gnds/read/createInterpolationType.hpp"
#include "njoy/format/gnds/read/readXYs1d.hpp"
#include "njoy/format/gnds/read/convertEnergies.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a TabulatedFormFactor from a GNDS form factor node
   *
   *  @param[in] node   the gnds XYs1d or regions1d node
   */
  inline dryad::TabulatedFormFactor
  createTabulatedFormFactorFromNodes( const pugi::xml_node& node ) {

    std::vector< double > energies;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< dryad::InterpolationType > interpolants;

    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the form factor data
      auto data = readXYs1D( node );

      // get the interpolation type
      auto interpolant = createInterpolationType( data.interpolation );

      // convert units - if necessary
      convertEnergies( data.x, data.x_unit.value() );

      // assign data
      energies = std::move( data.x );
      values = std::move( data.y );
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
        auto interpolant = createInterpolationType( data.interpolation );

        // convert units - if necessary
        convertEnergies( data.x, data.x_unit.value() );

        // check for duplicate points at interpolation region boundaries
        std::size_t offset = 0;
        if ( energies.size() > 0 ) {

          if ( energies.back() == data.x.front() && values.back() == data.y.front() ) {

            offset = 1;
          }
        }

        // grow the data accordingly
        energies.insert( energies.end(), std::next( data.x.begin(), offset ), data.x.end() );
        values.insert( values.end(), std::next( data.y.begin(), offset ), data.y.end() );
        boundaries.emplace_back( energies.size() - 1 );
        interpolants.emplace_back( interpolant );
      }
    }
    else {

      Log::error( "Expected either an XYs1d node or regions1d node with XYs1d nodes "
                  "for tabulated form factor data data" );
      throw std::exception();
    }

    return dryad::TabulatedFormFactor(
             std::move( energies ), std::move( values ),
             std::move( boundaries ), std::move( interpolants ) );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
