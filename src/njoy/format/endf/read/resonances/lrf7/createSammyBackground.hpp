#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATESAMMYBACKGROUND
#define NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATESAMMYBACKGROUND

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/SammyBackground.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create a SammyBackground from a parsed ENDF section
   *
   *  @param[in] background   the energy dependent scattering radius record
   */
  inline dryad::resonances::SammyBackground
  createSammyBackground(
      const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SammyBackgroundRMatrix& background ) {

    try {

      Log::info( "Reading channel background parametrisation (SAMMY)" );
      std::array< double, 3 > polynomial = { background.R0(), background.R1(), background.R2() };
      std::array< double, 2 > logarithmic = { background.S0(), background.S1() };
      double lower = background.ED();
      double upper = background.EU();
      return dryad::resonances::SammyBackground(
               std::move( polynomial ), std::move( logarithmic ),
               lower, upper );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a SAMMY channel background parametrisation" );
      throw;
    }
  }

} // lrf7 namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
