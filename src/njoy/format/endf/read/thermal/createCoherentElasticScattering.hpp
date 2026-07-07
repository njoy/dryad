#ifndef NJOY_FORMAT_ENDF_READ_THERMAL_CREATECOHERENTELASTICSCATTERING
#define NJOY_FORMAT_ENDF_READ_THERMAL_CREATECOHERENTELASTICSCATTERING

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/thermal/CoherentElasticScattering.hpp"
#include "njoy/format/endf/read/thermal/createBraggEdges.hpp"
#include "ENDFtk/section/7/2.hpp"
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace thermal {

  /**
   *  @brief Create a CoherentElasticScattering from a parsed coherent
   *         elastic thermal scattering component
   *
   *  @param[in] coherent   the coherent elastic thermal scattering component
   */
  inline dryad::thermal::CoherentElasticScattering
  createCoherentElasticScattering( const ENDFtk::section::Type< 7, 2 >::CoherentElastic& coherent ) {

    Log::info( "Reading coherent elastic scattering data" );
    return dryad::thermal::CoherentElasticScattering( createBraggEdges( coherent ) );
  }

} // thermal namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
