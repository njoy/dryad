#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEB_CREATESPINGROUPS
#define NJOY_FORMAT_ENDF_READ_RESONANCES_URR_CASEB_CREATESPINGROUPS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/resonances/UnresolvedSpinGroup.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/endf/read/resonances/createChannelRadii.hpp"
#include "njoy/format/endf/read/resonances/retrieveQuantumNumber.hpp"
#include "njoy/format/endf/read/resonances/urr/caseB/createChannelData.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {
namespace urr {
namespace caseB {

  /**
   *  @brief Create the spin groups for energy-dependent-fission-width
   *         unresolved resonance parameters (Case B)
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] naps         the channel radius option as given in the ENDF file
   *  @param[in] nro          the energy dependent scattering radius (if defined, given in fm)
   *  @param[in] lower        the lower energy limit of the range (eV)
   *  @param[in] upper        the upper energy limit of the range (eV)
   *  @param[in] endf         the parsed ENDF energy-dependent-fission-width unresolved data
   */
  inline auto createSpinGroups( const dryad::id::ParticleID& projectile,
                                const dryad::id::ParticleID& target,
                                int naps,
                                const std::optional< dryad::resonances::TabulatedRadius >& nro,
                                double lower, double upper,
                                const ENDFtk::section::Type< 2, 151 >::UnresolvedEnergyDependentFissionWidths& endf ) {

    std::vector< dryad::resonances::UnresolvedSpinGroup > groups;

    // create all possible channel quantum numbers
    auto spin = endf.spin();
    auto lmax = endf.lValues().back().orbitalMomentum();
    auto available = dryad::resonances::ChannelQuantumNumbers::allowedChannelQuantumNumbers( 0.5, spin, lmax );

    // the incident particle pair
    auto awri = endf.lValues().front().atomicWeightRatio();
    dryad::resonances::ParticlePair incident( dryad::Particle( projectile, constants::neutron_mass, 0.5, +1 ),
                                              dryad::Particle( target, awri * constants::neutron_mass, spin, +1 ) );

    // channel radii - URR has no l-dependent scattering radius, so one value serves every spin group
    auto ap = endf.scatteringRadius() * constants::deca;
    dryad::resonances::ChannelRadii radii = createChannelRadii( naps, nro, ap, awri );

    // the fission width energy grid is shared by every (l,J) in the range
    auto fissionEnergies = format::createVector( endf.energies() );

    // go over each l value and each j value - one spin group per (l,J)
    for ( const auto& lvalue : endf.lValues() ) {

      unsigned int l = lvalue.orbitalMomentum();

      for ( const auto& jvalue : lvalue.jValues() ) {

        // resolve the elastic channel's quantum numbers
        auto numbers = retrieveQuantumNumber( l, jvalue.AJ(), available );

        auto [ channels, table ] = caseB::createChannelData(
            projectile, target, incident, radii, numbers, lower, upper,
            jvalue, fissionEnergies );

        groups.emplace_back( std::move( channels ), std::move( table ) );
      }
    }

    return groups;
  }

} // caseB namespace
} // urr namespace
} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
