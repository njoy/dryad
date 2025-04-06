#ifndef NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATEVARIANCESCALING
#define NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATEVARIANCESCALING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/covariance/createScalingType.hpp"
#include "dryad/format/gnds/readAxes.hpp"
#include "dryad/format/gnds/convertEnergies.hpp"
#include "dryad/covariance/VarianceScaling.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace covariance {

  /**
   *  @brief Create a VarianceScaling from a GNDS variance scaling node
   */
  static dryad::covariance::VarianceScaling
  createVarianceScaling( const pugi::xml_node& scaling ) {

    // check that this is a valid variance scaling node
    throwExceptionOnWrongNode( scaling, "shortRangeSelfScalingVariance" );

    // get the type from the attribute
    auto attribute = scaling.attribute( "dependenceOnProcessedGroupWidth" ).as_string();
    dryad::covariance::ScalingType type = covariance::createScalingType( attribute );

    // get the group structure from the axes - convert units if required
    auto axes = readAxes( scaling.child( "gridded2d" ).child( "axes" ) );
    std::vector< double > energies = std::move( std::get< 2 >( axes[0] ).value() );
    convertEnergies( energies, std::get< 1 >( axes[0] ).value() );

    std::vector< double > factors = energies;
    factors.pop_back();

    return dryad::covariance::VarianceScaling( std::move( type ),
                                               std::move( energies ),
                                               std::move( factors ) );
  }

} // covariance namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
