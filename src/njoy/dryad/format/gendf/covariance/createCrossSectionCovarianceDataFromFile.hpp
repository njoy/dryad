#ifndef NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATECROSSSECTIONCOVARIANCEDATAFROMFILE
#define NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATECROSSSECTIONCOVARIANCEDATAFROMFILE

// system includes

// other includes
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"
#include "njoy/dryad/format/gendf/covariance/createCrossSectionCovarianceData.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gendf {
namespace covariance {

  /**
   *  @brief Create a CrossSectionCovarianceData from an ERRORR GENDF file
   *
   *  If there are multiple materials in the ENDF file, only the first material
   *  will be transformed into a ProjectileTarget.
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] relative     the flag to indicate whether or not the covariance data is relative
   *  @param[in] filename     the GENDF file name
   */
  inline std::optional< dryad::covariance::CrossSectionCovarianceData >
  createCrossSectionCovarianceDataFromFile( const id::ParticleID& projectile,
                                            const id::ParticleID& target,
                                            bool relative,
                                            const std::string& filename ) {

    Log::info( "Reading GENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile< ENDFtk::tree::GTape >( filename );
    return createCrossSectionCovarianceData( projectile, target, relative, tape.materials().front() );
  }

} // covariance namespace
} // gendf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
