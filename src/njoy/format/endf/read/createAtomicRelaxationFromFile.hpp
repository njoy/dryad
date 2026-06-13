#ifndef NJOY_FORMAT_ENDF_READ_CREATEATOMICRELAXATIONFROMFILE
#define NJOY_FORMAT_ENDF_READ_CREATEATOMICRELAXATIONFROMFILE

// system includes
#include <vector>

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include "njoy/dryad/AtomicRelaxation.hpp"
#include "njoy/format/endf/read/createAtomicRelaxation.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

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
  inline dryad::AtomicRelaxation
  createAtomicRelaxationFromFile( const std::string& filename, bool normalise ) {

    Log::info( "Reading ENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile< ENDFtk::tree::Tape >( filename );
    return createAtomicRelaxation( tape.materials().front(), normalise );
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
