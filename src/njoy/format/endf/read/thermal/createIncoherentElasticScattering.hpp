#ifndef NJOY_FORMAT_ENDF_READ_THERMAL_CREATEINCOHERENTELASTICSCATTERING
#define NJOY_FORMAT_ENDF_READ_THERMAL_CREATEINCOHERENTELASTICSCATTERING

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"
#include "njoy/format/endf/read/thermal/createDebyeWallerIntegralData.hpp"
#include "ENDFtk/section/7/2.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace thermal {

  /**
   *  @brief Create an IncoherentElasticScattering from a parsed incoherent
   *         elastic thermal scattering component
   *
   *  @param[in] lower        the lower energy limit
   *  @param[in] upper        the upper energy limit
   *  @param[in] incoherent   the incoherent elastic thermal scattering component
   */
  inline dryad::thermal::IncoherentElasticScattering
  createIncoherentElasticScattering(
      double lower, double upper,
      const ENDFtk::section::Type< 7, 2 >::IncoherentElastic& incoherent ) {

    Log::info( "Reading incoherent elastic scattering data" );
    return dryad::thermal::IncoherentElasticScattering(
             lower, upper,
             incoherent.boundCrossSection(),
             createDebyeWallerIntegralData( incoherent ) );
  }

} // thermal namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
