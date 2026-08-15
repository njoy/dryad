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
   *  @brief Create a MultigroupProjectileTarget from a GENDF file
   *
   *  If there are multiple materials in the GENDF file, only the first material
   *  will be transformed into a MultigroupProjectileTarget.
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] filename     the GENDF file name
   *  @param[in] relative     the flag to indicate whether or not the covariance data is relative
   *  @param[in] frame        the reference frame
   */
  inline dryad::MultigroupProjectileTarget
  createMultigroupProjectileTargetFromFile( const dryad::id::ParticleID& projectile,
                                            const dryad::id::ParticleID& target,
                                            const std::string& filename,
                                            bool relative = true,
                                            const dryad::ReferenceFrame& frame = dryad::ReferenceFrame::CentreOfMass ) {

    Log::info( "Reading GENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile< ENDFtk::tree::GTape >( filename );
    return createMultigroupProjectileTarget( projectile, target, relative, frame, tape.materials().front() );
  }

} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
