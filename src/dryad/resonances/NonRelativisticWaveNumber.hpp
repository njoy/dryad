#ifndef NJOY_DRYAD_RESONANCES_NONRELATIVISTICWAVENUMBER
#define NJOY_DRYAD_RESONANCES_NONRELATIVISTICWAVENUMBER

// system includes

// other includes
#include "dryad/constants.hpp"
#include "dryad/resonances/ParticlePair.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The non-relativistic wave number
   */
  class NonRelativisticWaveNumber {

    /* fields */

    /* auxiliary functions */

  public:

    /* constructor */

    NonRelativisticWaveNumber() = default;

    NonRelativisticWaveNumber( const NonRelativisticWaveNumber& ) = default;
    NonRelativisticWaveNumber( NonRelativisticWaveNumber&& ) = default;

    NonRelativisticWaveNumber& operator=( const NonRelativisticWaveNumber& ) = default;
    NonRelativisticWaveNumber& operator=( NonRelativisticWaveNumber&& ) = default;

    /* methods */

    /**
     *  @brief Calculate the channel wave number (given in fm^-1) at a given energy
     *
     *  The wave number k is an energy dependent quantity defined as follows:
     *     hbar^2 k^2 = 2 * mu * ( energy * ratio + q )
     *  in which mu is the reduced mass of the channel's particle pair and ratio
     *  is the mass ratio M / ( m + M ) for the incident particle pair, q is the
     *  Q value associated to the transition of the incident particle pair to the
     *  channel's particle pair and hbar is the reduced Planck constant.
     *
     *  @param[in] energy     the energy (given in eV)
     *  @param[in] qValue     the Q value (given in eV)
     *  @param[in] incident   the incident particle pair information
     *  @param[in] outgoing   the outgoing particle pair information
     */
    double operator()( double energy, double qValue,
                       const ParticlePair& incident,
                       const ParticlePair& outgoing ) const {

      // see Sammy manual equation II C4.4 and ENDF manual equation D.82

      // conversion constant to convert the final value to fm^-1
      const double conversion = std::sqrt( constants::amu / constants::e ) * constants::femto;

      const auto mu = outgoing.reducedMass(); // amu
      const auto ratio = incident.massRatio(); // dimensionless
      const auto q = qValue;                   // eV
      return std::sqrt( 2. * mu * ( std::abs( energy * ratio + q ) ) )
             / constants::hbar * conversion;
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
