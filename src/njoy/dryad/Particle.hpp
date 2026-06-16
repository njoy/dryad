#ifndef NJOY_DRYAD_PARTICLE
#define NJOY_DRYAD_PARTICLE

// system includes
#include <tuple>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/external/ripl3/Levels.hpp"
#include "njoy/dryad/external/ame/Masses.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Particle information
   *
   *  The Particle class contains specific information for a particle:
   *    - a particle identifier
   *    - an optional atomic mass value (always for the ground state) and an optional
   *      uncertainty
   *    - an optional nuclear mass value (always for the ground state) and an optional
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
    std::optional< double > mass_;
    std::optional< double > nuclear_mass_;
    std::optional< double > energy_;

    std::optional< double > mass_uncertainty_;
    std::optional< double > nuclear_mass_uncertainty_;
    std::optional< double > energy_uncertainty_;

    std::optional< double > spin_;
    std::optional< short > parity_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    Particle() = default;

    Particle( const Particle& ) = default;
    Particle( Particle&& ) = default;

    Particle& operator=( const Particle& ) = default;
    Particle& operator=( Particle&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] id                       the particle identifier
     *  @param[in] mass                     the atomic mass (default is none)
     *  @param[in] spin                     the particle spin (default is none)
     *  @param[in] parity                   the parity (default is none)
     *  @param[in] energy                   the excited state energy (default is none)
     *  @param[in] nuclearMass              the nuclear mass (default is none)
     *  @param[in] massUncertainty          the uncertainty on the atomic mass value (default is none)
     *  @param[in] nuclearMassUncertainty   the uncertainty on the nuclear mass value (default is none)
     *  @param[in] energyUncertainty        the uncertainty on the level energy value (default is none)
     */
    Particle( id::ParticleID id,
              std::optional< double > mass = std::nullopt,
              std::optional< double > spin = std::nullopt,
              std::optional< short > parity = std::nullopt,
              std::optional< double > energy = std::nullopt,
              std::optional< double > nuclearMass = std::nullopt,
              std::optional< double > massUncertainty = std::nullopt,
              std::optional< double > nuclearMassUncertainty = std::nullopt,
              std::optional< double > energyUncertainty = std::nullopt ) :
      identifier_( std::move( id ) ),
      mass_( std::move( mass ) ),
      nuclear_mass_( std::move( nuclearMass ) ),
      energy_( std::move( energy ) ),
      mass_uncertainty_( std::move( massUncertainty ) ),
      nuclear_mass_uncertainty_( std::move( nuclearMassUncertainty ) ),
      energy_uncertainty_( std::move( energyUncertainty ) ),
      spin_( std::move( spin ) ),
      parity_( std::move( parity ) ) {}

    /* predefined particles and static functions to create them */

    /**
     *  @brief The default particle instance for photons
     */
    static Particle photon() {

      return Particle( id::ParticleID::photon(), 0., 1.0, +1,
                       std::nullopt, std::nullopt, 0. );
    };

    /**
     *  @brief The default particle instance for electrons
     */
    static Particle electron() {

      return Particle( id::ParticleID::electron(), constants::electron_mass, 0.5, +1,
                       std::nullopt, std::nullopt, constants::electron_mass_uncertainty );
    };

    /**
     *  @brief The default particle instance for positrons
     */
    static Particle positron() {

      return Particle( id::ParticleID::positron(), constants::electron_mass, 0.5, -1,
                       std::nullopt, std::nullopt, constants::electron_mass_uncertainty );
    };

    /**
     *  @brief The default particle instance for neutrons
     */
    static Particle neutron() {

      return Particle( id::ParticleID::neutron(), constants::neutron_mass, 0.5, +1,
                       std::nullopt, std::nullopt, constants::neutron_mass_uncertainty );
    };

    /**
     *  @brief The default particle instance for protons
     */
    static Particle proton() {

      return Particle( id::ParticleID::proton(), constants::proton_mass, 0.5, +1,
                       std::nullopt, std::nullopt, constants::proton_mass_uncertainty );
    };

    /**
     *  @brief The default particle instance for deuterons
     */
    static Particle deuteron() {

      return Particle( id::ParticleID::deuteron(), constants::deuteron_mass, 1.0, +1,
                       std::nullopt, std::nullopt, constants::deuteron_mass_uncertainty );
    };

    /**
     *  @brief The default particle instance for tritons
     */
    static Particle triton() {

      return Particle( id::ParticleID::triton(), constants::triton_mass, 0.5, +1,
                       std::nullopt, std::nullopt, constants::triton_mass_uncertainty );
    };

    /**
     *  @brief The default particle instance for helions
     */
    static Particle helion() {

      return Particle( id::ParticleID::helion(), constants::helion_mass, 0.5, +1,
                       std::nullopt, std::nullopt, constants::helion_mass_uncertainty );
    };

    /**
     *  @brief The default particle instance for alphas
     */
    static Particle alpha() {

      return Particle( id::ParticleID::alpha(), constants::alpha_mass, 0.0, +1,
                       std::nullopt, std::nullopt, constants::alpha_mass_uncertainty );
    };

    /**
     *  @brief The default particle instance for a given particle identifier
     *
     *  This function creates a default particle instance for the given particle
     *  identifier. When relevant, the discrete level energies and spins-parity pairs
     *  from RIPL-3 and the atomic masses from AME-2020 are used.
     *
     *  When more sources for the particle data become available, this function will
     *  provide options to select data from.
     *
     *  When an atomic identifier (either with or without vacancies) is used, the
     *  elemental particle instance will be returned.
     */
    static Particle defaultParticle( const id::ParticleID& id ) {

      if      ( id == id::ParticleID::photon() )   { return Particle::photon(); }
      else if ( id == id::ParticleID::electron() ) { return Particle::electron(); }
      else if ( id == id::ParticleID::positron() ) { return Particle::positron(); }
      else if ( id == id::ParticleID::neutron() )  { return Particle::neutron(); }
      else if ( id == id::ParticleID::proton() )   { return Particle::proton(); }
      else if ( id == id::ParticleID::deuteron() ) { return Particle::deuteron(); }
      else if ( id == id::ParticleID::triton() )   { return Particle::triton(); }
      else if ( id == id::ParticleID::helion() )   { return Particle::helion(); }
      else if ( id == id::ParticleID::alpha() )    { return Particle::alpha(); }
      else {

        if ( id.a() != 0 ) {

          Particle particle( id );
          if ( external::ripl3::Levels::hasEntry( id ) ) {

            decltype(auto) entry = external::ripl3::Levels::entry( id );
            particle.energy( entry.energy() );
            particle.spin( entry.spin() );
            particle.parity( entry.parity() );
          }
          if ( external::ame::Masses::hasEntry( id ) ) {

            decltype(auto) entry = external::ame::Masses::entry( id );
            particle.mass( entry.atomicMass() );
            particle.massUncertainty( entry.atomicMassUncertainty() );
          }

          return particle;
        }
        else {

          Particle particle( id::ParticleID( id.z(), 0, 0 ) );
          return particle;
        }
      }
    };

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
    const std::optional< double >& mass() const {

      return this->mass_;
    }

    /**
     *  @brief Set the atomic mass of the particle in the ground state
     *
     *  @param mass  the atomic mass
     */
    void mass( std::optional< double > mass ) {

      this->mass_ = std::move( mass );
    }

    /**
     *  @brief Return the nuclear mass of the particle in the ground state
     */
    const std::optional< double >& nuclearMass() const {

      return this->nuclear_mass_;
    }

    /**
     *  @brief Set the nuclear mass of the particle in the ground state
     *
     *  @param mass  the nuclear mass
     */
    void nuclearMass( std::optional< double > mass ) {

      this->nuclear_mass_ = std::move( mass );
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
     *  @brief Return the nuclear mass uncertainty
     */
    const std::optional< double >& nuclearMassUncertainty() const {

      return this->nuclear_mass_uncertainty_;
    }

    /**
     *  @brief Set the nuclear mass uncertainty
     *
     *  @param massUncertainty  the nuclear mass uncertainty
     */
    void nuclearMassUncertainty( std::optional< double > massUncertainty ) {

      this->nuclear_mass_uncertainty_ = std::move( massUncertainty );
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

      return std::tie( left.identifier(), left.mass(), left.nuclearMass(), left.energy(),
                       left.massUncertainty(), left.nuclearMassUncertainty(),
                       left.energyUncertainty(), left.spin(), left.parity() ) ==
             std::tie( right.identifier(), right.mass(), right.nuclearMass(), right.energy(),
                       right.massUncertainty(), right.nuclearMassUncertainty(),
                       right.energyUncertainty(), right.spin(), right.parity() );
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
