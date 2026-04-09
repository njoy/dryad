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
   *    - the atomic mass value (always for the ground state) and an optional
   *      uncertainty
   *    - an optional excited state energy value and an optional uncertainty
   *    - an optional spin and parity (which is either + or -)
   *
   *  The data is stored in the following units:
   *    - atomic mass values are in atomic mass units
   *    - energy values are in eV
   */
  class Particle {

    /* fields */

    id::ParticleID identifier_;
    double mass_;
    std::optional< double > energy_;
    std::optional< double > mass_uncertainty_;
    std::optional< double > energy_uncertainty_;

    std::optional< double > spin_;
    std::optional< short > parity_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "njoy/dryad/Particle/src/ctor.hpp"

    /**
     *  @brief Return the particle identifier
     */
    const id::ParticleID& identifier() const {

      return this->identifier_;
    }

    /**
     *  @brief Set the particle identifier
     *
     *  @param id  the particle identifier
     */
    void identifier( id::ParticleID id ) {

      this->identifier_ = std::move( id );
    }

    /**
     *  @brief Return the electrical charge of the particle
     */
    int charge() const { return this->identifier().z(); }

    /**
     *  @brief Return the excited state number of the particle
     */
    int excitedState() const { return this->identifier().e(); }

    /**
     *  @brief Return the atomic mass of the particle in the ground state
     */
    double mass() const {

      return this->mass_;
    }

    /**
     *  @brief Set the atomic mass of the particle in the ground state
     *
     *  @param mass  the atomic mass
     */
    void mass( double mass ) {

      this->mass_ = std::move( mass );
    }

    /**
     *  @brief Return the excited state energy value of the particle
     */
    const std::optional< double >& energy() const {

      return this->energy_;
    }

    /**
     *  @brief Set the excited state energy value of the particle
     *
     *  @param energy  the excited state energy
     */
    void energy( std::optional< double > energy ) {

      this->energy_ = std::move( energy );
    }

    /**
     *  @brief Return the atomic mass uncertainty
     */
    const std::optional< double >& massUncertainty() const {

      return this->mass_uncertainty_;
    }

    /**
     *  @brief Set the atomic mass uncertainty
     *
     *  @param massUncertainty  the atomic mass uncertainty
     */
    void massUncertainty( std::optional< double > massUncertainty ) {

      this->mass_uncertainty_ = std::move( massUncertainty );
    }

    /**
     *  @brief Return the excited state energy uncertainty
     */
    const std::optional< double >& energyUncertainty() const {

      return this->energy_uncertainty_;
    }

    /**
     *  @brief Set the excited state energy uncertainty
     *
     *  @param energyUncertainty  the excited state energy uncertainty
     */
    void energyUncertainty( std::optional< double > energyUncertainty ) {

      this->energy_uncertainty_ = std::move( energyUncertainty );
    }

    /**
     *  @brief Return the spin of the particle
     */
    const std::optional< double >& spin() const {

      return this->spin_;
    }

    /**
     *  @brief Set the spin of the particle
     *
     *  @param spin  the particle spin
     */
    void spin( std::optional< double > spin ) {

      this->spin_ = std::move( spin );
    }

    /**
     *  @brief Return the particle spin parity
     */
    const std::optional< short >& parity() const {

      return this->parity_;
    }

    /**
     *  @brief Set the particle spin parity
     *
     *  @param parity  the particle spin
     */
    void parity( std::optional< short > parity ) {

      this->parity_ = std::move( parity );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const Particle& left, const Particle& right ) {

      return std::tie( left.identifier(), left.mass_, left.energy_,
                       left.massUncertainty(), left.energyUncertainty(),
                       left.spin(), left.parity() ) ==
             std::tie( right.identifier(), right.mass_, right.energy_,
                       right.massUncertainty(), right.energyUncertainty(),
                       right.spin(), right.parity() );
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
