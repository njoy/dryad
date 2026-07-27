#ifndef NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATAFROMFILE
#define NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATAFROMFILE

// system includes

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"
#include "njoy/format/gendf/read/covariance/createAngularDistributionCovarianceData.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {
namespace covariance {

  /**
   *  @brief Create an AngularCovarianceData from an ERRORR GENDF file
   *
   *  If there are multiple materials in the ENDF file, only the first material
   *  will be transformed into a ProjectileTarget.
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] frame        the reference frame
   *  @param[in] filename     the GENDF file name
   */
  inline std::optional< dryad::covariance::AngularDistributionCovarianceData >
  createAngularDistributionCovarianceDataFromFile( const dryad::id::ParticleID& projectile,
                                                   const dryad::id::ParticleID& target,
                                                   const dryad::ReferenceFrame& frame,
                                                   const std::string& filename ) {

    Log::info( "Reading GENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile< ENDFtk::tree::GTape >( filename );
    return createAngularDistributionCovarianceData( projectile, target, frame, tape.materials().front() );
  }

} // covariance namespace
} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
