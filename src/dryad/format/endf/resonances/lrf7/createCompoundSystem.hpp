#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATECOMPOUNDSYSTEM
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATECOMPOUNDSYSTEM

// system includes

// other includes
#include "tools/Log.hpp"
#include "dryad/resonances/CompoundSystem.hpp"
#include "dryad/format/endf/resonances/lrf7/createBoundaryCondition.hpp"
#include "dryad/format/endf/resonances/lrf7/createKinematics.hpp"
#include "dryad/format/endf/resonances/lrf7/createFormalism.hpp"
#include "dryad/format/endf/resonances/lrf7/createSpinGroups.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the compound system for LRF7 resonance parameters
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] lower        the lower energy limit
   *  @param[in] upper        the upper energy limit
   *  @param[in] endf         the parsed ENDF LRF7 data
   */
  auto createCompoundSystem( const id::ParticleID& projectile,
                             const id::ParticleID& target,
                             double lower,
                             double upper,
                             const ENDFtk::section::Type< 2, 151 >::RMatrixLimited& endf ) {

    auto formalism = lrf7::createFormalism( endf );
    auto kinematics = lrf7::createKinematics( endf );
    auto boundary = lrf7::createBoundaryCondition( endf.particlePairs() );
    auto groups = lrf7::createSpinGroups( projectile, target, formalism, boundary, kinematics, endf );

    return dryad::resonances::CompoundSystem( lower, upper, std::move( groups ) );
  }

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
