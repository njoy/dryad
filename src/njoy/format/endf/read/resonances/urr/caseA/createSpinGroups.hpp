#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEA_CREATESPINGROUPS
#define NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEA_CREATESPINGROUPS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/resonances/UnresolvedSpinGroup.hpp"
#include "njoy/format/endf/read/resonances/createChannelRadii.hpp"
#include "njoy/format/endf/read/resonances/retrieveQuantumNumber.hpp"
#include "njoy/format/endf/read/resonances/urr/caseA/createChannelData.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace urr {
namespace caseA {

  /**
   *  @brief Create the spin groups for energy-independent unresolved
   *         resonance parameters (Case A)
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] naps         the channel radius option as given in the ENDF file
   *  @param[in] nro          the energy dependent scattering radius (if defined, given in fm)
   *  @param[in] lower        the lower energy limit of the range (eV)
   *  @param[in] upper        the upper energy limit of the range (eV)
   *  @param[in] endf         the parsed ENDF energy-independent unresolved data
   */
  inline auto createSpinGroups( const dryad::id::ParticleID& projectile,
                                const dryad::id::ParticleID& target,
                                int naps,
                                const std::optional< dryad::resonances::TabulatedRadius >& nro,
                                double lower, double upper,
                                const ENDFtk::section::Type< 2, 151 >::UnresolvedEnergyIndependent& urr_endf ) {

    std::vector< dryad::resonances::UnresolvedSpinGroup > groups;

    // create all possible channel quantum numbers
    auto spin = urr_endf.spin();
    auto lmax = urr_endf.lValues().back().orbitalMomentum();
    auto available = dryad::resonances::ChannelQuantumNumbers::allowedChannelQuantumNumbers( 0.5, spin, lmax );

    // the incident particle pair
    auto awri = urr_endf.lValues().front().atomicWeightRatio();
    dryad::resonances::ParticlePair incident( dryad::Particle( projectile, constants::neutron_mass, 0.5, +1 ),
                                              dryad::Particle( target, awri * constants::neutron_mass, spin, +1 ) );

    // channel radii - URR has no l-dependent scattering radius, so one value serves every spin group
    auto ap = urr_endf.scatteringRadius() * constants::deca;
    dryad::resonances::ChannelRadii radii = createChannelRadii( naps, nro, ap, awri );

    // go over each l value and each j value - one spin group per (l,J)
    for ( const auto& lvalue : urr_endf.lValues() ) {

      unsigned int l = lvalue.orbitalMomentum();

      for ( const auto& jvalue : lvalue.jValues() ) {

        // resolve the elastic channel's quantum numbers
        auto numbers = retrieveQuantumNumber( l, jvalue.AJ(), available );

        auto [ channels, table ] = caseA::createChannelData(
            projectile, target, incident, radii, numbers, lower, upper,
            jvalue.AMUN(), jvalue.GN(), jvalue.GG(), jvalue.D() );

        groups.emplace_back( std::move( channels ), std::move( table ) );
      }
    }

    return groups;
  }

} // caseA namespace
} // urr namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
