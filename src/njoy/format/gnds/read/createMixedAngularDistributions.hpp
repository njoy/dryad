#ifndef NJOY_FORMAT_GNDS_READ_CREATEMIXEDANGULARDISTRIBUTIONS
#define NJOY_FORMAT_GNDS_READ_CREATEMIXEDANGULARDISTRIBUTIONS

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "tools/apply_permutation.hpp"
#include "njoy/dryad/MixedAngularDistributions.hpp"
#include "njoy/format/gnds/read/createLegendreAngularDistributionFunctions.hpp"
#include "njoy/format/gnds/read/createTabulatedAngularDistributionFunctions.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a MixedAngularDistributions instance from a GNDS regions2d node
   *
   *  @param[in] regions2d   the gnds regions2d node
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline dryad::MixedAngularDistributions
  createMixedAngularDistributions( pugi::xml_node regions2d, bool normalise = false ) {

    // check that this is a valid regions2d node
    throwExceptionOnWrongNode( regions2d, "regions2d" );

    // read the axes
    auto units = readAxes( regions2d.child( "axes" ) );

    std::vector< double > grid;
    std::vector< dryad::MixedAngularDistribution > distributions;

    // get the groups of functions
    auto function2ds = regions2d.child( "function2ds" );
    for ( pugi::xml_node group = function2ds.child( "XYs2d" );
          group; group = group.next_sibling( "XYs2d" ) ) {

      // get the functions
      auto function1ds = group.child( "function1ds" );
      auto function = function1ds.first_child();
      if ( strcmp( function.name(), "Legendre" ) == 0 ||
           strcmp( function.name(), "XYs1d" ) == 0 ) {

        if ( strcmp( function.name(), "Legendre" ) == 0 ) {

          auto data = createLegendreAngularDistributionFunctions( function1ds, units );
          for ( std::size_t i = 0; i < data.first.size(); ++i ) {

            grid.emplace_back( data.first[i].value() );
            distributions.emplace_back( std::move( data.second[i] ), normalise );
          }
        }
        else {

          auto data = createTabulatedAngularDistributionFunctions( function1ds, units );
          for ( std::size_t i = 0; i < data.first.size(); ++i ) {

            grid.emplace_back( data.first[i].value() );
            distributions.emplace_back( std::move( data.second[i] ), normalise );
          }
        }
      }
      else {

        Log::error( "Only Legendre or XYs1d nodes are allowed in an angular XYs2d" );
        throw std::exception();
      }
    }

    // ensure everything is sorted correctly (since the XYs2d might not be in order)
    if ( ! std::is_sorted( grid.begin(), grid.end() ) ) {

      // get the order
      std::vector< std::size_t > order( grid.size() );
      std::iota( order.begin(), order.end(), 0 );
      std::sort( order.begin(), order.end(),
                 [&] ( auto&& i, auto&& j ) { return grid[i] < grid[j]; } );

      // sort the channels and perform a permutation on the columns
      std::sort( grid.begin(), grid.end() );
      tools::apply_permutation( distributions, order );
    }

    return dryad::MixedAngularDistributions( std::move( grid ), std::move( distributions ) );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
