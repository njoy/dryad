#ifndef NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPPROJECTILETARGETFROMFILE
#define NJOY_FORMAT_GENDF_READ_CREATEMULTIGROUPPROJECTILETARGETFROMFILE

// system includes
#include <string>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/format/gendf/read/createMultigroupProjectileTarget.hpp"
#include "ENDFtk/tree/GTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {

  /**
   *  @brief Create a MultigroupProjectileTarget from oen or more GENDF file
   *
   *  The main GENDF file has to be a groupr output file, and the optional covariance
   *  files are errorr output files. When lumped covariances are used, the corresponding
   *  cross section values are read from the errorr file itself.
   *
   *  @param[in] projectile                  the projectile identifier
   *  @param[in] target                      the target identifier
   *  @param[in] filename                    the file name for the main GENDF file
   *  @param[in] xsCovarianceFilename        the optional file name for the xs covariance GENDF file
   *  @param[in] angularCovarianceFilename   the optional file name for the angular covariance GENDF file
   *  @param[in] relative                    the flag to indicate whether or not the covariance data is relative
   *  @param[in] frame                       the reference frame for the angular distribution data
   */
  inline dryad::MultigroupProjectileTarget
  createMultigroupProjectileTargetFromFile( const dryad::id::ParticleID& projectile,
                                            const dryad::id::ParticleID& target,
                                            const std::string& filename,
                                            const std::optional< std::string >& xsCovarianceFilename = std::nullopt,
                                            const std::optional< std::string >& angularCovarianceFilename = std::nullopt,
                                            bool relative = true,
                                            const dryad::ReferenceFrame& frame = dryad::ReferenceFrame::CentreOfMass ) {

    Log::info( "Reading GENDF file \'{}\'", filename );

    ENDFtk::tree::GMaterial material = ENDFtk::tree::fromFile< ENDFtk::tree::GTape >( filename ).materials().front();

    std::optional< ENDFtk::tree::GMaterial > xs = std::nullopt;
    if ( xsCovarianceFilename.has_value() ) {

      xs = ENDFtk::tree::fromFile< ENDFtk::tree::GTape >( xsCovarianceFilename.value() ).materials().front();
    }

    std::optional< ENDFtk::tree::GMaterial > angular = std::nullopt;
    if ( angularCovarianceFilename.has_value() ) {

      angular = ENDFtk::tree::fromFile< ENDFtk::tree::GTape >( angularCovarianceFilename.value() ).materials().front();
    }

    return createMultigroupProjectileTarget( projectile, target, relative, frame,
                                             material, xs, angular );
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
