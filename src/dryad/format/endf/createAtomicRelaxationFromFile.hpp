#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILETARGETFROMFILE
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPROJECTILETARGETFROMFILE

// system includes
#include <vector>

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include "dryad/AtomicRelaxation.hpp"
#include "dryad/format/endf/createAtomicRelaxation.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create an AtomicRelaxation from an ENDF file
   *
   *  If there are multiple materials in the ENDF file, only the first material
   *  will be transformed into an AtomicRelaxation.
   *
   *  @param[in] filename    the ENDF file name
   *  @param[in] normalise   option to indicate whether or not to normalise
   *                         all probability data
   */
  AtomicRelaxation createAtomicRelaxationFromFile( const std::string& filename,
                                                   bool normalise ) {

    Log::info( "Reading ENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile( filename );
    return createAtomicRelaxation( tape.materials().front(), normalise );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
