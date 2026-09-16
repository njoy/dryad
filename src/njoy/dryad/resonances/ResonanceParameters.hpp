#ifndef NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS
#define NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS

// system includes
#include <variant>
#include <vector>
#include <optional>
#include <tuple>

// other includes
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/dryad/resonances/UnresolvedCompoundSystem.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The resonance parameter data
   */
  class ResonanceParameters {

    /* fields */

    double lower_;
    double upper_;
    std::optional< double > scattering_radius_;

    std::vector< CompoundSystem > resolved_;
    std::optional< UnresolvedCompoundSystem > unresolved_;

    std::vector< id::ReactionID > reactions_;

    /* auxiliary functions */

    /**
     *  @brief Collect all reactions from the resonance parameters
     */
    void collectReactions() {

      this->reactions().clear();

      // go over the reactions in the resolved compound systems
      for ( auto&& compound : this->resolved() ) {

        for ( auto&& id : compound.reactions() ) {

          auto iter = std::lower_bound( this->reactions().begin(), this->reactions().end(), id );
          if ( iter == this->reactions().end() || *iter != id ) {

            this->reactions().insert( iter, id );
          }
        }
      }

      // go over the reactions in the unresolved compound system
      if ( this->unresolved().has_value() ) {

        for ( auto&& id : this->unresolved()->reactions() ) {

          auto iter = std::lower_bound( this->reactions().begin(), this->reactions().end(), id );
          if ( iter == this->reactions().end() || *iter != id ) {

            this->reactions().insert( iter, id );
          }
        }
      }
    }

    /**
     *  @brief Set the energy limits for the resonance parameters
     */
    void setEnergyLimits() {

      if ( this->resolved().size() != 0 ) {

        this->lowerEnergyLimit() = this->resolved().front().lowerEnergyLimit();
        this->upperEnergyLimit() = this->resolved().front().upperEnergyLimit();
      }

      if ( this->unresolved().has_value() ) {

        if ( this->resolved().size() == 0 ) {

          this->lowerEnergyLimit() = this->unresolved()->lowerEnergyLimit();
          this->upperEnergyLimit() = this->unresolved()->upperEnergyLimit();
        }
        else {

          this->upperEnergyLimit() = this->unresolved()->upperEnergyLimit();
        }
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ResonanceParameters() = default;

    ResonanceParameters( const ResonanceParameters& ) = default;
    ResonanceParameters( ResonanceParameters&& ) = default;

    ResonanceParameters& operator=( const ResonanceParameters& ) = default;
    ResonanceParameters& operator=( ResonanceParameters&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] resolved     the resolved resonance compound systems
     *  @param[in] unresolved   the optional unresolved resonance compound system
     */
    ResonanceParameters( std::vector< CompoundSystem > resolved,
                         std::optional< UnresolvedCompoundSystem > unresolved = std::nullopt ) :
        scattering_radius_( std::nullopt ),
        resolved_( std::move( resolved ) ),
        unresolved_( std::move( unresolved ) )  {

      this->collectReactions();
      this->setEnergyLimits();
    }

    /**
     *  @brief Constructor
     *
     *  @param[in] lowerEnergy   the lower energy limit
     *  @param[in] upperEnergy   the upper energy limit
     *  @param[in] radius        the scattering radius
     */
    ResonanceParameters( double lowerEnergy, double upperEnergy, double radius ) :
        lower_( lowerEnergy ),
        upper_( upperEnergy ),
        scattering_radius_( radius ),
        resolved_(),
        unresolved_( std::nullopt ) {}

    /* methods */

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->lower_;
    }

    /**
     *  @brief Return the lower energy limit
     */
    double& lowerEnergyLimit() {

      return this->lower_;
    }

    /**
     *  @brief Set the lower energy limit
     *
     *  @param[in] lowerEnergy   the lower energy limit for the compound system
     */
    void lowerEnergyLimit( double lowerEnergy ) {

      this->lower_ = lowerEnergy;
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->upper_;
    }

    /**
     *  @brief Return the upper energy limit
     */
    double& upperEnergyLimit() {

      return this->upper_;
    }

    /**
     *  @brief Set the upper energy limit
     *
     *  @param[in] upperEnergy   the upper energy limit for the compound system
     */
    void upperEnergyLimit( double upperEnergy ) {

      this->upper_ = upperEnergy;
    }

    /**
     *  @brief Return the scattering radius
     */
    const std::optional< double >& scatteringRadius() const {

      return this->scattering_radius_;
    }

    /**
     *  @brief Return the scattering radius
     */
    std::optional< double >& scatteringRadius() {

      return this->scattering_radius_;
    }

    /**
     *  @brief Set the scattering radius
     *
     *  @param[in] radius  the scattering radius
     */
    void scatteringRadius( std::optional< double > radius ) {

      this->scattering_radius_ = std::move( radius );
    }

    /**
     *  @brief Return the reactions to which the resonance parameters contribute
     */
    const std::vector< id::ReactionID >& reactions() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the reactions to which the resonance parameters contribute
     */
    std::vector< id::ReactionID >& reactions() {

      return this->reactions_;
    }

    /**
     *  @brief Return whether or not a given reaction is present in the resonance parameters
     *
     *  @param[in] id   the reaction identifier
     */
    bool hasReaction( const id::ReactionID& id ) const {

      auto iter = std::lower_bound( this->reactions().begin(), this->reactions().end(), id );
      return iter != this->reactions().end() && *iter == id;
    }

    /**
     *  @brief Return the compound systems that make up the resolved resonance data
     */
    const std::vector< CompoundSystem >& resolved() const {

      return this->resolved_;
    }

    /**
     *  @brief Return the compound systems that make up the resolved resonance data
     */
    std::vector< CompoundSystem >& resolved() {

      return this->resolved_;
    }

    /**
     *  @brief Set the compound systems that make up resolved resonance data
     *
     *  @param[in] resolved   the resolved resonance compound systems
     */
    void resolved( std::vector< CompoundSystem > resolved ) {

      this->resolved_ = std::move( resolved );
      this->scatteringRadius( std::nullopt );
      this->collectReactions();
      this->setEnergyLimits();
    }

    /**
     *  @brief Return the compound systems that make up the unresolved resonance data
     */
    const std::optional< UnresolvedCompoundSystem >& unresolved() const {

      return this->unresolved_;
    }

    /**
     *  @brief Return the compound systems that make up the unresolved resonance data
     */
    std::optional< UnresolvedCompoundSystem >& unresolved() {

      return this->unresolved_;
    }

    /**
     *  @brief Set the compound systems that make up unresolved resonance data
     *
     *  @param[in] unresolved   the unresolved resonance compound systems
     */
    void unresolved(  UnresolvedCompoundSystem unresolved ) {

      this->unresolved_ = std::move( unresolved );
      this->scatteringRadius( std::nullopt );
      this->collectReactions();
      this->setEnergyLimits();
    }

    /**
     *  @brief Return whether or not resonance parameters are given
     */
    bool hasParameters() const {

      return this->resolved().size() > 0 || this->unresolved().has_value();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const ResonanceParameters& left, const ResonanceParameters& right ) {

      return  std::tie( left.lower_, left.upper_, left.scatteringRadius(), left.resolved(), left.unresolved() ) ==
              std::tie( right.lower_, right.upper_, right.scatteringRadius(), right.resolved(), right.unresolved() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const ResonanceParameters& left, const ResonanceParameters& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
