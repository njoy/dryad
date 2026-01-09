#ifndef NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATETABULATEDDEBYEWALLERINTEGRAL
#define NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATETABULATEDDEBYEWALLERINTEGRAL

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/createBoundaries.hpp"
#include "njoy/dryad/format/endf/createInterpolants.hpp"
#include "njoy/dryad/thermal/TabulatedDebyeWallerIntegral.hpp"
#include "ENDFtk/section/7/2.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace thermal {

  /**
   *  @brief Create a TabulatedDebyeWallerIntegral from a parsed incoherent
   *         elastic thermal scattering component
   *
   *  @param[in] incoherent   the incoherent elastic thermal scattering component
   */
  dryad::thermal::TabulatedDebyeWallerIntegral
  createTabulatedDebyeWallerIntegral(
      const ENDFtk::section::Type< 7, 2 >::IncoherentElastic& incoherent ) {

    try {

      auto temperatures = createVector( incoherent.temperatures() );
      auto values = createVector( incoherent.debyeWallerValues() );
      auto boundaries = createBoundaries( incoherent.boundaries() );
      auto interpolants = createInterpolants( incoherent.interpolants() );
      return dryad::thermal::TabulatedDebyeWallerIntegral(
               std::move( temperatures ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a Debye-Waller integral table "
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
