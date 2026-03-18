#ifndef NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATECOHERENTELASTICSCATTERING
#define NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATECOHERENTELASTICSCATTERING

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/CoherentElasticScattering.hpp"
#include "njoy/dryad/format/endf/thermal/createBraggEdges.hpp"
#include "ENDFtk/section/7/2.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace thermal {

  /**
   *  @brief Create a CoherentElasticScattering from a parsed coherent
   *         elastic thermal scattering component
   *
   *  @param[in] coherent   the coherent elastic thermal scattering component
   */
  dryad::thermal::CoherentElasticScattering
  createCoherentElasticScattering(
      const ENDFtk::section::Type< 7, 2 >::CoherentElastic& coherent ) {

    Log::info( "Reading coherent elastic scattering data" );
    return dryad::thermal::CoherentElasticScattering(
             createBraggEdges( coherent ) );
  }

} // thermal namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
