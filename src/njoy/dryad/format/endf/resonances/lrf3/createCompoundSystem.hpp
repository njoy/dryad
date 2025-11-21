#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF3_CREATECOMPOUNDSYSTEM
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF3_CREATECOMPOUNDSYSTEM

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/dryad/format/endf/resonances/lrf3/createSpinGroups.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf3 {

  /**
   *  @brief Create the compound system for LRF3 resonance parameters
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] lower        the lower energy limit
   *  @param[in] upper        the upper energy limit
   *  @param[in] naps         the channel radius option as given in the ENDF file
   *  @param[in] nro          the energy dependent scattering radius (if defined, given in fm)
   *  @param[in] endf         the parsed ENDF LRF3 data
   */
  inline auto createCompoundSystem( const id::ParticleID& projectile,
                                    const id::ParticleID& target,
                                    double lower,
                                    double upper,
                                    int naps,
                                    const std::optional< dryad::resonances::TabulatedRadius >& nro,
                                    const ENDFtk::section::Type< 2, 151 >::ReichMoore& endf ) {

    auto groups = lrf3::createSpinGroups( projectile, target, naps, nro, endf );

    return dryad::resonances::CompoundSystem( lower, upper, std::move( groups ) );
  }

} // lrf3 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
