#ifndef NJOY_FORMAT_ENDF_WRITE_THERMAL_CREATEINCOHERENTELASTIC
#define NJOY_FORMAT_ENDF_WRITE_THERMAL_CREATEINCOHERENTELASTIC

// system includes
#include <vector>

// other includes
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"
#include "njoy/format/endf/write/createInterpolants.hpp"
#include "njoy/format/endf/write/createBoundaries.hpp"
#include "ENDFtk/section/7/2.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {
namespace thermal {

  /**
   *  @brief Create an ENDF MF7 MT2 IncoherentElastic object from an
   *         IncoherentElasticScattering object
   *
   *  @param[in] incoherent   the incoherent elastic data
   */
  inline ENDFtk::section::Type< 7, 2 >::IncoherentElastic
  createIncoherentElastic( const dryad::thermal::IncoherentElasticScattering& incoherent ) {

    double sb = incoherent.boundCrossSection();
    std::vector< double > temperatures = incoherent.debyeWallerIntegral().temperatures();
    std::vector< double > integrals = incoherent.debyeWallerIntegral().values();
    std::vector< long > boundaries = { static_cast< long >( temperatures.size() ) };
    std::vector< long > interpolants = { 2 };

    return ENDFtk::section::Type< 7, 2 >::IncoherentElastic(
             sb,
             std::move( boundaries ),
             std::move( interpolants ),
             std::move( temperatures ),
             std::move( integrals ) );
  }

} // thermal namespace
} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
