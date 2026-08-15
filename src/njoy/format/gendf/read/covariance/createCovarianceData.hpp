#ifndef NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECOVARIANCEDATA
#define NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECOVARIANCEDATA

// system includes
#include <optional>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/dryad/covariance/CovarianceData.hpp"
#include "njoy/format/gendf/read/covariance/createCrossSectionCovarianceData.hpp"
#include "njoy/format/gendf/read/covariance/createAngularDistributionCovarianceData.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {
namespace covariance {

  /**
   *  @brief Create a CovarianceData from an unparsed GENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] relative     the flag to indicate whether or not the covariance data is relative
   *  @param[in] frame        the reference frame
   *  @param[in] material     the unparsed GENDF material
   */
  inline std::optional< dryad::covariance::CovarianceData >
  createCovarianceData( const dryad::id::ParticleID& projectile,
                        const dryad::id::ParticleID& target,
                        bool relative,
                        const dryad::ReferenceFrame& frame,
                        const ENDFtk::tree::GMaterial& material ) {

    std::optional< dryad::covariance::CrossSectionCovarianceData > xs =
    createCrossSectionCovarianceData( projectile, target, relative, material );

    std::optional< dryad::covariance::AngularDistributionCovarianceData > angular =
    createAngularDistributionCovarianceData( projectile, target, frame, material );

    if ( xs.has_value() || angular.has_value() ) {

      return dryad::covariance::CovarianceData( std::move( xs ), std::move( angular ) );
    }
    else {

      return std::nullopt;
    }
  }

} // covariance namespace
} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
