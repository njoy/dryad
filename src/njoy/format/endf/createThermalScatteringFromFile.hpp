#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETHERMALSCATTERINGFROMFILE
#define NJOY_DRYAD_FORMAT_ENDF_CREATETHERMALSCATTERINGFROMFILE

// system includes

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/dryad/format/endf/createThermalScattering.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a ThermalScattering instance from an ENDF file
   *
   *  If there are multiple materials in the ENDF file, only the first material
   *  will be transformed into a ThermalScattering instance.
   *
   *  @param[in] filename    the ENDF file name
   */
  inline ThermalScattering
  createThermalScatteringFromFile( const std::string& filename ) {

    Log::info( "Reading ENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile< ENDFtk::tree::Tape >( filename );
    return createThermalScattering( tape.materials().front() );
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
