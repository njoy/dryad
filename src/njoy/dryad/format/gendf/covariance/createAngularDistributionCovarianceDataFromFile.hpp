#ifndef NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATAFROMFILE
#define NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATAFROMFILE

// system includes

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"
#include "njoy/dryad/format/gendf/covariance/createAngularDistributionCovarianceData.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gendf {
namespace covariance {

  /**
   *  @brief Create an AngularCovarianceData from an ERRORR GENDF file
   *
   *  If there are multiple materials in the ENDF file, only the first material
   *  will be transformed into a ProjectileTarget.
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] filename     the GENDF file name
   */
  inline std::optional< dryad::covariance::AngularDistributionCovarianceData >
  createAngularDistributionCovarianceDataFromFile( const id::ParticleID& projectile,
                                            const id::ParticleID& target,
                                            const ReferenceFrame& frame,
                                            const std::string& filename ) {

    Log::info( "Reading GENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile< ENDFtk::tree::GTape >( filename );
    return createAngularDistributionCovarianceData( projectile, target, frame, tape.materials().front() );
  }

} // covariance namespace
} // gendf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif // NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATAFROMFILE