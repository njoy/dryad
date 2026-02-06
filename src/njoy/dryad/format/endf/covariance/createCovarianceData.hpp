#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATECOVARIANCEDATA
#define NJOY_DRYAD_FORMAT_ENDF_CREATECOVARIANCEDATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/CovarianceData.hpp"
#include "njoy/dryad/format/endf/covariance/createCrossSectionCovarianceData.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace covariance {

  /**
   *  @brief Create a CovarianceData from an unparsed ENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed ENDF material
   */
  inline std::optional< dryad::covariance::CovarianceData >
  createCovarianceData( const id::ParticleID& projectile,
                        const id::ParticleID& target,
                        const ENDFtk::tree::Material& material ) {

    std::optional< dryad::covariance::CrossSectionCovarianceData > xs =
    createCrossSectionCovarianceData( projectile, target, material );

    if ( xs.has_value() ) {

      return dryad::covariance::CovarianceData( std::move( xs ) );
    }
    else {

      return std::nullopt;
    }
  }

} // covariance namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
