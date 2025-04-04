#ifndef NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATEVARIANCESCALING
#define NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATEVARIANCESCALING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "dryad/format/gnds/convertEnergy.hpp"
#include "dryad/covariance/VarianceScaling.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace covariance {

  /**
   *  @brief Create a PolynomialMultiplicity from a GNDS multiplicity node
   */
  static dryad::covariance::VarianceScaling
  createVarianceScaling( const pugi::xml_node& scaling ) {

    dryad::covariance::ScalingType type = dryad::covariance::ScalingType::Direct;
    std::vector< double > energies = { 1., 2. };
    std::vector< double > factors = { 1. };

    // check that this is a valid scaling variance node
    throwExceptionOnWrongNode( scaling, "shortRangeSelfScalingVariance" );

    return dryad::covariance::VarianceScaling(
               std::move( type ),
               std::move( energies ), std::move( factors ) );
  }

} // covariance namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
