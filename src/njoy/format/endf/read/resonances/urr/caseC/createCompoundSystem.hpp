#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CREATECOMPOUNDSYSTEM
#define NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CREATECOMPOUNDSYSTEM

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/UnresolvedCompoundSystem.hpp"
#include "njoy/format/endf/read/resonances/urr/caseC/createSpinGroups.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace urr {
namespace caseC {

  /**
   *  @brief Create the unresolved compound system for fully energy-dependent
   *         unresolved resonance parameters (Case C)
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] lower        the lower energy limit
   *  @param[in] upper        the upper energy limit
   *  @param[in] naps         the channel radius option as given in the ENDF file
   *  @param[in] nro          the energy dependent scattering radius (if defined, given in fm)
   *  @param[in] endf         the parsed ENDF fully energy-dependent unresolved data
   */
  inline auto createCompoundSystem( const dryad::id::ParticleID& projectile,
                                    const dryad::id::ParticleID& target,
                                    double lower,
                                    double upper,
                                    int naps,
                                    const std::optional< dryad::resonances::TabulatedRadius >& nro,
                                    const ENDFtk::section::Type< 2, 151 >::UnresolvedEnergyDependent& endf ) {

    auto groups = caseC::createSpinGroups( projectile, target, naps, nro, lower, upper, endf );
    return dryad::resonances::UnresolvedCompoundSystem( lower, upper, std::move( groups ) );
  }

} // caseC namespace
} // urr namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace


#endif
