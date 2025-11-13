#ifndef NJOY_DRYAD_RESONANCES_RELATIVISTICWAVENUMBER
#define NJOY_DRYAD_RESONANCES_RELATIVISTICWAVENUMBER

// system includes

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/resonances/ParticlePair.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The relativistic wave number
   */
  class RelativisticWaveNumber {

    /* fields */

    /* auxiliary functions */

  public:

    /* constructor */

    RelativisticWaveNumber() = default;

    RelativisticWaveNumber( const RelativisticWaveNumber& ) = default;
    RelativisticWaveNumber( RelativisticWaveNumber&& ) = default;

    RelativisticWaveNumber& operator=( const RelativisticWaveNumber& ) = default;
    RelativisticWaveNumber& operator=( RelativisticWaveNumber&& ) = default;

    /* methods */

    /**
     *  @brief Return the kinematics type
     */
    static constexpr Kinematics kinematicsType() { return Kinematics::Relativistic; }

    /**
     *  @brief Return the relativistic wave number at a given energy
     *
     *  The relativistic wave number k is an energy dependent quantity defined as
     *  follows:
     *     k^2 = ( s - ( ( ma + mb ) c^2 )^2 ) ( s - ( ( ma - mb ) c^2 )^2 ) / 4 / s
     *  in which s is the Mandelstam variable s, ma and mb are the atomic masses
     *  of the first and second particles in the particle pair and c is the light
     *  speed (converting the mass into energy).
     *
     *  The Mandelstam variable s is defined as:
     *     s = ( ( ma + mb ) c^2 )^2 + 2 mb c^2 energy
     *  in which ma and mb are the atomic masses of the first and second particles
     *  in the particle pair and c is the light speed (converting the mass into
     *  energy).
     *
     *  @param[in] energy     the energy (given in eV)
     *  @param[in] incident   the incident particle pair information
     */
    double operator()( double energy, const ParticlePair& incident ) const {

      // conversion constant to convert amu m^2 s^-2 into eV
      constexpr double conversion = constants::amu * constants::c * constants::c / constants::e;

      // conversion constant to convert the result to fm^-1
      constexpr double final = constants::c * constants::hbar * constants::peta;

      const auto particle = incident.lightParticle().mass();
      const auto residual = incident.heavyParticle().mass();
      const auto pair = ( particle + residual ) * conversion;  // eV
      const auto delta = ( particle - residual ) * conversion; // eV
      const auto mandelstam = pair * pair + 2. * residual * conversion * std::abs( energy ); // ev^2
      return 0.5 * sqrt( ( mandelstam - pair * pair ) * ( mandelstam - delta * delta ) / mandelstam ) / final;
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
