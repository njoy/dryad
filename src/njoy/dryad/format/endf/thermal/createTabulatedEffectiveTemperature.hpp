#ifndef NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATETABULATEDEFFECTIVETEMPERATURE
#define NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATETABULATEDEFFECTIVETEMPERATURE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/createBoundaries.hpp"
#include "njoy/dryad/format/endf/createInterpolants.hpp"
#include "njoy/dryad/thermal/TabulatedEffectiveTemperature.hpp"
#include "ENDFtk/section/7/4.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace thermal {

  /**
   *  @brief Create a TabulatedEffectiveTemperature from a parsed inelastic
   *         thermal scattering effective temperature component
   *
   *  @param[in] temperature   the effective temperature component
   */
  dryad::thermal::TabulatedEffectiveTemperature
  createTabulatedEffectiveTemperature(
      const ENDFtk::section::Type< 7, 4 >::EffectiveTemperature& temperature ) {

    try {

      auto temperatures = createVector( temperature.moderatorTemperatures() );
      auto values = createVector( temperature.effectiveTemperatures() );
      auto boundaries = createBoundaries( temperature.boundaries() );
      auto interpolants = createInterpolants( temperature.interpolants() );
      return dryad::thermal::TabulatedEffectiveTemperature(
               std::move( temperatures ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating an effective temperature table "
                 "for inelastic thermal scattering" );
      throw;
    }
  }

} // thermal namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
