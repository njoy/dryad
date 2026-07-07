#ifndef NJOY_FORMAT_GNDS_READ_CREATELEGENDREANGULARDISTRIBUTIONFUNCTIONS
#define NJOY_FORMAT_GNDS_READ_CREATELEGENDREANGULARDISTRIBUTIONFUNCTIONS

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/LegendreAngularDistributionFunction.hpp"
#include "njoy/format/gnds/read/createLegendreAngularDistributionFunction.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create LegendreAngularDistributionFunction instances from a GNDS function1ds node
   *
   *  @param[in] function1ds   the gnds function1ds node
   *  @param[in] units         the unit information
   */
  inline std::pair< std::vector< std::optional< double > >,
                    std::vector< dryad::LegendreAngularDistributionFunction > >
  createLegendreAngularDistributionFunctions( pugi::xml_node function1ds, const Axes& units ) {

    // check that this is a valid function1ds node
    throwExceptionOnWrongNode( function1ds, "function1ds" );

    // check if this is a collection of Legendre nodes
    if ( strcmp( function1ds.first_child().name(), "Legendre" ) == 0 ) {

      std::vector< std::optional< double > > grid;
      std::vector< dryad::LegendreAngularDistributionFunction > functions;

      for ( pugi::xml_node function = function1ds.child( "Legendre" );
            function; function = function.next_sibling( "Legendre" ) ) {

        auto data = createLegendreAngularDistributionFunction( function, units );
        grid.emplace_back( std::move( data.first ) );
        functions.emplace_back( std::move( data.second ) );
      }

      return { std::move( grid ), std::move( functions ) };
    }
    else {

      Log::error( "The function1ds node does not contain Legendre nodes, found \'{}\' nodes",
                  function1ds.first_child().name() );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
