#ifndef NJOY_FORMAT_GNDS_READ_CREATELEGENDREANGULARDISTRIBUTIONS
#define NJOY_FORMAT_GNDS_READ_CREATELEGENDREANGULARDISTRIBUTIONS

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/LegendreAngularDistributions.hpp"
#include "njoy/format/gnds/read/createLegendreAngularDistributionFunctions.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a LegendreAngularDistributions instance from a GNDS XYs2d node
   *
   *  @param[in] XYs2d       the gnds XYs2d node
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline dryad::LegendreAngularDistributions
  createLegendreAngularDistributions( pugi::xml_node XYs2d, bool normalise = false ) {

    // check that this is a valid regions2d node
    throwExceptionOnWrongNode( XYs2d, "XYs2d" );

    // read the axes
    auto units = readAxes( XYs2d.child( "axes" ) );

    // get the functions
    auto function1ds = XYs2d.child( "function1ds" );

    // the grid and distributions
    std::vector< double > grid;
    std::vector< dryad::LegendreAngularDistribution > distributions;

    auto data = createLegendreAngularDistributionFunctions( function1ds, units );
    for ( std::size_t i = 0; i < data.first.size(); ++i ) {

      grid.emplace_back( data.first[i].value() );
      distributions.emplace_back( std::move( data.second[i] ), normalise );
    }

    return dryad::LegendreAngularDistributions( std::move( grid ), std::move( distributions ) );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
