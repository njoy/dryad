#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATECOMPOUNDSYSTEM
#define NJOY_FORMAT_ENDF_READ_RESONANCES_LRF7_CREATECOMPOUNDSYSTEM

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createBoundaryCondition.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createKinematics.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createFormalism.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createSpinGroups.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
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
  inline auto createCompoundSystem( const dryad::id::ParticleID& projectile,
                                    const dryad::id::ParticleID& target,
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
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
