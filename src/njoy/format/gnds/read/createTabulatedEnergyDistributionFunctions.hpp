#ifndef NJOY_FORMAT_GNDS_READ_CREATETABULATEDENERGYDISTRIBUTIONFUNCTIONS
#define NJOY_FORMAT_GNDS_READ_CREATETABULATEDENERGYDISTRIBUTIONFUNCTIONS

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/TabulatedEnergyDistributionFunction.hpp"
#include "njoy/format/gnds/read/createTabulatedEnergyDistributionFunction.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a TabulatedAngularDistribution from a GNDS legendre node
   */
  inline std::pair< std::vector< std::optional< double > >,
                    std::vector< dryad::TabulatedEnergyDistributionFunction > >
  createTabulatedEnergyDistributionFunctions( pugi::xml_node function1ds, const Axes& units ) {

    // check that this is a valid function1ds node
    throwExceptionOnWrongNode( function1ds, "function1ds" );

    // check if this is a collection of XYs1d nodes
    if ( strcmp( function1ds.first_child().name(), "XYs1d" ) == 0 ) {

      std::vector< std::optional< double > > grid;
      std::vector< dryad::TabulatedEnergyDistributionFunction > functions;

      for ( pugi::xml_node function = function1ds.first_child();
            function; function = function.next_sibling() ) {

        auto data = createTabulatedEnergyDistributionFunction( function, units );
        grid.emplace_back( std::move( data.first ) );
        functions.emplace_back( std::move( data.second ) );
      }

      return { std::move( grid ), std::move( functions ) };
    }
    else {

      Log::error( "The function1ds node does not contain XYs1d nodes, found \'{}\' nodes",
                  function1ds.first_child().name() );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
