#ifndef NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATEINCOHERENTELASTICSCATTERING
#define NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATEINCOHERENTELASTICSCATTERING

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"
#include "njoy/dryad/format/endf/thermal/createTabulatedDebyeWallerIntegral.hpp"
#include "ENDFtk/section/7/2.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace thermal {

  /**
   *  @brief Create a IncoherentElasticScattering from a parsed incoherent
   *         elastic thermal scattering component
   *
   *  @param[in] incoherent   the incoherent elastic thermal scattering component
   */
  dryad::thermal::IncoherentElasticScattering
  createIncoherentElasticScattering(
      const ENDFtk::section::Type< 7, 2 >::IncoherentElastic& incoherent ) {

    Log::info( "Reading incoherent elastic scattering data" );
    return dryad::thermal::IncoherentElasticScattering(
             incoherent.boundCrossSection(),
             createTabulatedDebyeWallerIntegral( incoherent ) );
  }

} // thermal namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
