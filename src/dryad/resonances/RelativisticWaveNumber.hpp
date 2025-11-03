#ifndef NJOY_DRYAD_RESONANCES_RELATIVISTICWAVENUMBER
#define NJOY_DRYAD_RESONANCES_RELATIVISTICWAVENUMBER

// system includes

// other includes
#include "dryad/constants.hpp"
#include "dryad/resonances/ParticlePair.hpp"

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
     *  @brief Calculate the channel wave number (given in fm^-1) at a given energy
     */
    double operator()() const {

      throw std::runtime_error( "not implemented yet" );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
