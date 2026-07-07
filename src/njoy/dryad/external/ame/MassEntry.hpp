#ifndef NJOY_DRYAD_EXTERNAL_AME_MASSENTRY
#define NJOY_DRYAD_EXTERNAL_AME_MASSENTRY

// system includes
#include <optional>
#include <tuple>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace external {
namespace ame {

  /**
   *  @class
   *  @brief Mass entry information from the Atomic Mass Evaluation
   *
   *  The MassEntry class contains the following information from the atomic mass evaluations:
   *    - a particle identifier
   *    - mass excess and uncertainty (in eV)
   *    - binding energy per nucleon and uncertainty (in eV)
   *    - beta decay energy and uncertainty (in eV)
   *    - atomic mass and uncertainty (in amu)
   */
  class MassEntry {

    /* fields */

    id::ParticleID identifier_;
    std::optional< double > mass_excess_;
    std::optional< double > mass_excess_uncertainty_;
    std::optional< double > binding_energy_;
    std::optional< double > binding_energy_uncertainty_;
    std::optional< double > beta_decay_energy_;
    std::optional< double > beta_decay_energy_uncertainty_;
    std::optional< double > atomic_mass_;
    std::optional< double > atomic_mass_uncertainty_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MassEntry() = default;

    MassEntry( const MassEntry& ) = default;
    MassEntry( MassEntry&& ) = default;

    MassEntry& operator=( const MassEntry& ) = default;
    MassEntry& operator=( MassEntry&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] id                              the particle identifier
     *  @param[in] mass_excess                     the mass excess (default is none)
     *  @param[in] mass_excess_uncertainty         the mass excess uncertainty (default is none)
     *  @param[in] binding_energy                  the binding energy per nucleon (default is none)
     *  @param[in] binding_energy_uncertainty      the binding energy uncertainty (default is none)
     *  @param[in] beta_decay_energy               the beta decay energy (default is none)
     *  @param[in] beta_decay_energy_uncertainty   the beta decay energy uncertainty (default is none)
     *  @param[in] mass                            the atomic mass (default is none)
     *  @param[in] mass_uncertainty                the atomic mass uncertainty (default is none)
     */
    MassEntry( id::ParticleID id,
               std::optional< double > mass_excess = std::nullopt,
               std::optional< double > mass_excess_uncertainty = std::nullopt,
               std::optional< double > binding_energy = std::nullopt,
               std::optional< double > binding_energy_uncertainty = std::nullopt,
               std::optional< double > beta_decay_energy = std::nullopt,
               std::optional< double > beta_decay_energy_uncertainty = std::nullopt,
               std::optional< double > mass = std::nullopt,
               std::optional< double > mass_uncertainty = std::nullopt ) :
      identifier_( std::move( id ) ),
      mass_excess_( std::move( mass_excess ) ),
      mass_excess_uncertainty_( std::move( mass_excess_uncertainty ) ),
      binding_energy_( std::move( binding_energy ) ),
      binding_energy_uncertainty_( std::move( binding_energy_uncertainty ) ),
      beta_decay_energy_( std::move( beta_decay_energy ) ),
      beta_decay_energy_uncertainty_( std::move( beta_decay_energy_uncertainty ) ),
      atomic_mass_( std::move( mass ) ),
      atomic_mass_uncertainty_( std::move( mass_uncertainty ) ) {}

    /* methods */

    /**
     *  @brief Return the particle identifier
     */
    const id::ParticleID& identifier() const {

      return this->identifier_;
    }

    /**
     *  @brief Set the particle identifier
     *
     *  @param[in] id  the particle identifier
     */
    void identifier( id::ParticleID id ) {

      this->identifier_ = std::move( id );
    }

    /**
     *  @brief Return the mass excess
     */
    const std::optional< double >& massExcess() const {

      return this->mass_excess_;
    }

    /**
     *  @brief Set the mass excess
     *
     *  @param[in] mass_excess  the mass excess
     */
    void massExcess( std::optional< double > mass_excess ) {

      this->mass_excess_ = std::move( mass_excess );
    }

    /**
     *  @brief Return the mass excess uncertainty
     */
    const std::optional< double >& massExcessUncertainty() const {

      return this->mass_excess_uncertainty_;
    }

    /**
     *  @brief Set the mass excess uncertainty
     *
     *  @param[in] mass_excess_uncertainty  the mass excess uncertainty
     */
    void massExcessUncertainty( std::optional< double > mass_excess_uncertainty ) {

      this->mass_excess_uncertainty_ = std::move( mass_excess_uncertainty );
    }

    /**
     *  @brief Return the binding energy per nucleon
     */
    const std::optional< double >& bindingEnergy() const {

      return this->binding_energy_;
    }

    /**
     *  @brief Set the binding energy per nucleon
     *
     *  @param[in] binding_energy  the binding energy per nucleon
     */
    void bindingEnergy( std::optional< double > binding_energy ) {

      this->binding_energy_ = std::move( binding_energy );
    }

    /**
     *  @brief Return the binding energy per nucleon uncertainty
     */
    const std::optional< double >& bindingEnergyUncertainty() const {

      return this->binding_energy_uncertainty_;
    }

    /**
     *  @brief Set the binding energy per nucleon uncertainty
     *
     *  @param[in] binding_energy_uncertainty  the binding energy per nucleon uncertainty
     */
    void bindingEnergyUncertainty( std::optional< double > binding_energy_uncertainty ) {

      this->binding_energy_uncertainty_ = std::move( binding_energy_uncertainty );
    }

    /**
     *  @brief Return the beta decay energy
     */
    const std::optional< double >& betaDecayEnergy() const {

      return this->beta_decay_energy_;
    }

    /**
     *  @brief Set the beta decay energy per nucleon
     *
     *  @param[in] decay_energy  the beta decay energy
     */
    void betaDecayEnergy( std::optional< double > decay_energy ) {

      this->beta_decay_energy_ = std::move( decay_energy );
    }

    /**
     *  @brief Return the beta decay energy uncertainty
     */
    const std::optional< double >& betaDecayEnergyUncertainty() const {

      return this->beta_decay_energy_uncertainty_;
    }

    /**
     *  @brief Set the beta decay energy per nucleon uncertainty
     *
     *  @param[in] decay_energy_uncertainty  the beta decay energy uncertainty
     */
    void betaDecayEnergyUncertainty( std::optional< double > decay_energy_uncertainty ) {

      this->beta_decay_energy_uncertainty_ = std::move( decay_energy_uncertainty );
    }

    /**
     *  @brief Return the atomic mass
     */
    const std::optional< double >& atomicMass() const {

      return this->atomic_mass_;
    }

    /**
     *  @brief Set the atomic mass
     *
     *  @param[in] mass  the atomic mass
     */
    void atomicMass( std::optional< double > mass ) {

      this->atomic_mass_ = std::move( mass );
    }

    /**
     *  @brief Return the atomic mass uncertainty
     */
    const std::optional< double >& atomicMassUncertainty() const {

      return this->atomic_mass_uncertainty_;
    }

    /**
     *  @brief Set the atomic mass uncertainty
     *
     *  @param[in] mass_uncertainty  the atomic mass uncertainty
     */
    void atomicMassUncertainty( std::optional< double > mass_uncertainty ) {

      this->atomic_mass_uncertainty_ = std::move( mass_uncertainty );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const MassEntry& left, const MassEntry& right ) {

      return std::tie( left.identifier(),
                       left.massExcess(), left.massExcessUncertainty(),
                       left.bindingEnergy(), left.bindingEnergyUncertainty(),
                       left.betaDecayEnergy(), left.betaDecayEnergyUncertainty(),
                       left.atomicMass(), left.atomicMassUncertainty() ) ==
             std::tie( right.identifier(),
                       right.massExcess(), right.massExcessUncertainty(),
                       right.bindingEnergy(), right.bindingEnergyUncertainty(),
                       right.betaDecayEnergy(), right.betaDecayEnergyUncertainty(),
                       right.atomicMass(), right.atomicMassUncertainty() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const MassEntry& left, const MassEntry& right ) {

      return ! ( left == right );
    }
  };

} // ame namespace
} // external namespace
} // dryad namespace
} // njoy namespace

#endif
