#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATELEGENDREANGULARDISTRIBUTION
#define NJOY_DRYAD_FORMAT_GNDS_CREATELEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/readAxes.hpp"
#include "dryad/format/gnds/readLegendre.hpp"
#include "dryad/format/gnds/convertEnergy.hpp"
#include "dryad/LegendreAngularDistribution.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a LegendreAngularDistribution from a GNDS legendre node
   */
  static
  std::pair< std::optional< double >,
             LegendreAngularDistribution >
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
             LegendreAngularDistribution( std::move( data.second ), normalise ) };
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
