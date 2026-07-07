#ifndef NJOY_FORMAT_ENDF_READ_COVARIANCE_CREATECOVARIANCEDATA
#define NJOY_FORMAT_ENDF_READ_COVARIANCE_CREATECOVARIANCEDATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/CovarianceData.hpp"
#include "njoy/format/endf/read/covariance/createCrossSectionCovarianceData.hpp"
#include "njoy/format/endf/read/covariance/createAngularDistributionCovarianceData.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace covariance {

  /**
   *  @brief Create a CovarianceData from an unparsed ENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed ENDF material
   */
  inline std::optional< dryad::covariance::CovarianceData >
  createCovarianceData( const dryad::id::ParticleID& projectile,
                        const dryad::id::ParticleID& target,
                        const ENDFtk::tree::Material& material ) {

    std::optional< dryad::covariance::CrossSectionCovarianceData > xs =
    createCrossSectionCovarianceData( projectile, target, material );

    std::optional< dryad::covariance::AngularDistributionCovarianceData > angular =
    createAngularDistributionCovarianceData( projectile, target, material );

    if ( xs.has_value() || angular.has_value() ) {

      return dryad::covariance::CovarianceData( std::move( xs ), std::move( angular ) );
    }
    else {

      return std::nullopt;
    }
  }

} // covariance namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
