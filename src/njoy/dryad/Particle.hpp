#ifndef NJOY_DRYAD_PARTICLE
#define NJOY_DRYAD_PARTICLE

// system includes
#include <tuple>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Particle information
   *
   *  The Particle class contains specific information for a particle:
   *    - atomic mass
   *    - electrical charge
   *    - excited state number and energy value
   *    - spin and parity (which is either + or -)
   *    - optional half-life
   */
  class Particle {

    /* fields */

    id::ParticleID identifier_;
    double mass_;
    double spin_;
    short parity_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "njoy/dryad/resonances/Particle/src/ctor.hpp"

    /**
     *  @brief Return the particle identifier
     */
    const id::ParticleID& identifier() const { return this->identifier_; }

    /**
     *  @brief Return the atomic mass of the particle (in atomic mass units)
     */
    double mass() const { return this->mass_; }

    /**
     *  @brief Return the electrical charge of the particle (in units of the
     *         elementary charge)
     */
    int charge() const { return this->identifier().z(); }

    /**
     *  @brief Return the excited state number of the particle
     */
    int excitedState() const { return this->identifier().e(); }

    /**
     *  @brief Return the spin of the particle
     */
    double spin() const { return this->spin_; }

    /**
     *  @brief Return the particle parity
     */
    short parity() const { return this->parity_; }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const Particle& left, const Particle& right ) {

      return std::tie( left.identifier(), left.mass_,
                       left.spin_, left.parity_ ) ==
             std::tie( right.identifier(), right.mass_,
                       right.spin_, right.parity_ );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const Particle& left, const Particle& right ) {

      return ! ( left == right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
