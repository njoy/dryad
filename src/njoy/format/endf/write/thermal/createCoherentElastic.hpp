#ifndef NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATEENDFCOHERENTELASTIC
#define NJOY_DRYAD_FORMAT_ENDF_THERMAL_CREATEENDFCOHERENTELASTIC

// system includes
#include <vector>

// other includes
#include "njoy/dryad/thermal/CoherentElasticScattering.hpp"
#include "njoy/dryad/format/endf/createEndfInterpolants.hpp"
#include "njoy/dryad/format/endf/createEndfBoundaries.hpp"
#include "ENDFtk/section/7/2.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace thermal {

  /**
   *  @brief Create an ENDF MF7 MT2 CoherentElastic object from an
   *         CoherentElasticScattering object
   *
   *  @param[in] coherent   the coherent elastic data
   */
  inline ENDFtk::section::Type< 7, 2 >::CoherentElastic
  createEndfCoherentElastic( const dryad::thermal::CoherentElasticScattering& coherent ) {

    //! @todo verify that all temperatures have the same Bragg edge energies

    std::vector< double > temperatures = coherent.moderatorTemperatures();
    std::vector< double > energies = coherent.braggEdges().front().energies();
    std::vector< std::vector< double > > s( temperatures.size() );
    std::transform( coherent.braggEdges().begin(), coherent.braggEdges().end(),
                    s.begin(),
                    [] ( auto&& data ) { return data.values(); } );
    std::vector< long > boundaries = { static_cast< long >( energies.size() ) };
    std::vector< long > interpolants = { 1 };
    std::vector< long > li( temperatures.size() - 1, 2 );

    return ENDFtk::section::Type< 7, 2 >::CoherentElastic(
             std::move( boundaries ),
             std::move( interpolants ),
             std::move( temperatures ),
             std::move( li ),
             std::move( energies ),
             std::move( s ) );
  }

} // thermal namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
