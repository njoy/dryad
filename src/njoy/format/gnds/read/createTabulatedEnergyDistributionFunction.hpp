#ifndef NJOY_FORMAT_GNDS_READ_CREATETABULATEDENERGYDISTRIBUTIONFUNCTION
#define NJOY_FORMAT_GNDS_READ_CREATETABULATEDENERGYDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedEnergyDistributionFunction.hpp"
#include "njoy/format/gnds/read/createInterpolationType.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"
#include "njoy/format/gnds/read/convertEnergies.hpp"
#include "njoy/format/gnds/read/readXYs1d.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a TabulatedEnergyDistributionFunction from a GNDS XYs1d or regions1d node
   *
   *  @param[in] legendre   the gnds XYs1d or regions1d node
   *  @param[in] units      the unit information
   */
  inline std::pair< std::optional< double >,
                    dryad::TabulatedEnergyDistributionFunction >
  createTabulatedEnergyDistributionFunction( pugi::xml_node node, const Axes& units ) {

    std::optional< double > outer = std::nullopt;
    std::vector< double > energies;
    std::vector< double > values;
    std::vector< std::size_t > boundaries;
    std::vector< dryad::InterpolationType > interpolants;

    if ( strcmp( node.name(), "XYs1d" ) == 0 ) {

      // read the cross section data
      auto data = readXYs1D( node, units );

      // get the interpolation type
      auto interpolant = createInterpolationType( data.interpolation );

      // probability data does not need to be converted
      // convert outer domain value if necessary
      if ( data.outer.has_value() ) {

        convertEnergy( data.outer.value(), data.outer_unit.value() );
      }
      convertEnergies( data.x, data.x_unit.value() );

      // assign data
      outer = std::move( data.outer );
      energies = std::move( data.x );
      values = std::move( data.y );
      boundaries.emplace_back( energies.size() - 1 );
      interpolants.emplace_back( interpolant );
    }
    else if ( strcmp( node.name(), "regions1d" ) == 0 ) {

      // get the outer domain value
      auto attribute = node.attribute( "outerDomainValue" );
      if ( attribute ) {

        outer = attribute.as_double();
        convertEnergy( outer.value(), units[0].unit.value() );
      }

      // loop over the children of function1ds
      pugi::xml_node function1ds = node.child( "function1ds" );
      for ( pugi::xml_node xys1d = function1ds.child( "XYs1d" );
            xys1d; xys1d = xys1d.next_sibling(  "XYs1d"  ) ) {

        // read the current interpolation region
        auto data = readXYs1D( xys1d, units );

        // get the interpolation type
        auto interpolant = createInterpolationType( data.interpolation );

        // convert units - if necessary
        // probability data does not need to be converted
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

      Log::error( "Expected an XYs1d or regions1d node for tabulated energy distribution data" );
      throw std::exception();
    }

    return { std::move( outer ),
             dryad::TabulatedEnergyDistributionFunction(
               std::move( energies ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) ) };
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
