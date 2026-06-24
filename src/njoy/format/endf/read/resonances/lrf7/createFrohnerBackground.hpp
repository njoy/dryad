#ifndef NJOY_FORMAT_ENDF_READ_CREATEFROHNERBACKGROUND
#define NJOY_FORMAT_ENDF_READ_CREATEFROHNERBACKGROUND

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/FrohnerBackground.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create a FrohnerBackground from a parsed ENDF section
   *
   *  @param[in] background   the energy dependent scattering radius record
   */
  inline dryad::resonances::FrohnerBackground
  createFrohnerBackground(
      const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::FrohnerBackgroundRMatrix& background ) {

    try {

      Log::info( "Reading channel background parametrisation (Frohner)" );
      double level = background.R0();
      double pole = background.S0();
      double width = background.GA();
      double lower = background.ED();
      double upper = background.EU();
      return dryad::resonances::FrohnerBackground( level, pole, width, lower, upper );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a Frohner channel background parametrisation" );
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
