#ifndef NJOY_FORMAT_ENDF_READ_CREATEPROJECTILETARGETFROMFILE
#define NJOY_FORMAT_ENDF_READ_CREATEPROJECTILETARGETFROMFILE

// system includes

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/format/endf/read/createProjectileTarget.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a ProjectileTarget from an ENDF file
   *
   *  If there are multiple materials in the ENDF file, only the first material
   *  will be transformed into a ProjectileTarget.
   *
   *  @param[in] filename    the ENDF file name
   *  @param[in] normalise   the flag to indicate whether or not distributions
   *                         need to be normalised
   */
  inline dryad::ProjectileTarget
  createProjectileTargetFromFile( const std::string& filename, bool normalise ) {

    Log::info( "Reading ENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile< ENDFtk::tree::Tape >( filename );
    return createProjectileTarget( tape.materials().front(), normalise );
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
