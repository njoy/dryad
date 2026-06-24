#ifndef NJOY_FORMAT_GNDS_READ_CREATELEGENDREANGULARDISTRIBUTION
#define NJOY_FORMAT_GNDS_READ_CREATELEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/LegendreAngularDistribution.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"
#include "njoy/format/gnds/read/readLegendre.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a LegendreAngularDistribution from a GNDS legendre node
   */
  inline std::pair< std::optional< double >,
                    dryad::LegendreAngularDistribution >
  createLegendreAngularDistribution( pugi::xml_node legendre, const Axes& units,
                                     bool normalise ) {

    // read data from the node
    auto data = readLegendre( legendre );
    for ( std::size_t index = 0; index < data.second.size(); ++index ) {

      data.second[index] *= 0.5 * ( 2 * index + 1 );
    }

    // convert outer domain value if necessary
    if ( data.first.has_value() ) {

      convertEnergy( data.first.value(), std::get< 1 >( units[0] ).value() );
    }

    return { std::move( data.first ),
             dryad::LegendreAngularDistribution( std::move( data.second ), normalise ) };
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
