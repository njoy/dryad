#ifndef NJOY_DRYAD_FORMAT_ENDF_FROMFILE
#define NJOY_DRYAD_FORMAT_ENDF_FROMFILE

// system includes
#include <vector>

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "dryad/format/endf/createProjectileTarget.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a ProjectileTarget from an ENDF file
   *
   *  If there are multiple materials in the ENDF file, only the first material
   *  will be transformed into a ProjectileTarget.
   *
   *  @param[in] filename   the ENDF file name
   */
  ProjectileTarget createProjectileTargetFromFile( const std::string& filename ) {

    Log::info( "Reading ENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile( filename );
    return createProjectileTarget( tape.materials().front() );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
