#ifndef NJOY_FORMAT_GNDS_READ_CREATELEGENDREANGULARDISTRIBUTIONFUNCTION
#define NJOY_FORMAT_GNDS_READ_CREATELEGENDREANGULARDISTRIBUTIONFUNCTION

// system includes
#include <optional>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/LegendreAngularDistributionFunction.hpp"
#include "njoy/format/convertLegendreMoments.hpp"
#include "njoy/format/gnds/read/readAxes.hpp"
#include "njoy/format/gnds/read/readLegendre.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a LegendreAngularDistributionFunction from a GNDS legendre node
   *
   *  @param[in] legendre   the gnds Legendre node
   *  @param[in] units      the unit information
   */
  inline std::pair< std::optional< double >,
                    dryad::LegendreAngularDistributionFunction >
  createLegendreAngularDistributionFunction( pugi::xml_node legendre, const Axes& units ) {

    // read data from the node and convert to coefficients
    auto data = readLegendre( legendre );
    convertLegendreMoments( data.moments );

    // convert outer domain value if necessary
    if ( data.energy.has_value() ) {

      convertEnergy( data.energy.value(), units[0].unit.value() );
    }

    return { std::move( data.energy ),
             dryad::LegendreAngularDistributionFunction( std::move( data.moments ) ) };
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
