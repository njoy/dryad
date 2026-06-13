#ifndef NJOY_FORMAT_ENDF_READ_CREATETHERMALSCATTERINGFROMFILE
#define NJOY_FORMAT_ENDF_READ_CREATETHERMALSCATTERINGFROMFILE

// system includes

// other includes
#include "ENDFtk/tree/fromFile.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/format/endf/read/createThermalScattering.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a ThermalScattering instance from an ENDF file
   *
   *  If there are multiple materials in the ENDF file, only the first material
   *  will be transformed into a ThermalScattering instance.
   *
   *  @param[in] filename    the ENDF file name
   */
  inline dryad::ThermalScattering
  createThermalScatteringFromFile( const std::string& filename ) {

    Log::info( "Reading ENDF file \'{}\'", filename );

    auto tape = ENDFtk::tree::fromFile< ENDFtk::tree::Tape >( filename );
    return createThermalScattering( tape.materials().front() );
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
