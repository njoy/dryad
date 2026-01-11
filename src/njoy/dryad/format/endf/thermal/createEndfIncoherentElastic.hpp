#ifndef NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATEENDFINCOHERENTELASTIC
#define NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATEENDFINCOHERENTELASTIC

// system includes
#include <vector>

// other includes
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"
#include "njoy/dryad/format/endf/createEndfInterpolants.hpp"
#include "njoy/dryad/format/endf/createEndfBoundaries.hpp"
#include "ENDFtk/section/7/2.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace thermal {

  /**
   *  @brief Create an ENDF MF7 MT2 IncoherentElastic object from an
   *         IncoherentElasticScattering object
   *
   *  @param[in] incoherent   the incoherent elastic data
   */
  inline ENDFtk::section::Type< 7, 2 >::IncoherentElastic
  createEndfIncoherentElastic( const dryad::thermal::IncoherentElasticScattering& incoherent ) {

    double sb = incoherent.boundCrossSection();
    std::vector< long > boundaries = createEndfBoundaries( incoherent.debyeWallerIntegral().boundaries() );
    std::vector< long > interpolants = createEndfInterpolants( incoherent.debyeWallerIntegral().interpolants() );
    std::vector< double > temperatures = incoherent.debyeWallerIntegral().temperatures();
    std::vector< double > integrals = incoherent.debyeWallerIntegral().values();

    return ENDFtk::section::Type< 7, 2 >::IncoherentElastic(
             sb,
             std::move( boundaries ),
             std::move( interpolants ),
             std::move( temperatures ),
             std::move( integrals ) );
  }

} // atomic namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
