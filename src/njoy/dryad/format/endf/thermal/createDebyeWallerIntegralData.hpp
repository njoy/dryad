#ifndef NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATEDEBYEWALLERINTEGRALDATA
#define NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATEDEBYEWALLERINTEGRALDATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/thermal/DebyeWallerIntegralData.hpp"
#include "ENDFtk/section/7/2.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace thermal {

  /**
   *  @brief Create a DebyeWallerIntegralData from a parsed incoherent
   *         elastic thermal scattering component
   *
   *  @param[in] incoherent   the incoherent elastic thermal scattering component
   */
  dryad::thermal::DebyeWallerIntegralData
  createDebyeWallerIntegralData(
      const ENDFtk::section::Type< 7, 2 >::IncoherentElastic& incoherent ) {

    try {

      auto temperatures = createVector( incoherent.temperatures() );
      auto values = createVector( incoherent.debyeWallerValues() );
      return dryad::thermal::DebyeWallerIntegralData( std::move( temperatures ), std::move( values ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating Debye-Waller integral data "
                 "for incoherent elastic thermal scattering" );
      throw;
    }
  }

} // thermal namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
