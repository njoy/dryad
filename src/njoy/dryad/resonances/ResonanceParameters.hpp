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

    std::vector< CompoundSystem > resolved_;
    std::optional< UnresolvedCompoundSystem > unresolved_;

    std::vector< id::ReactionID > reactions_;

    /* auxiliary functions */

    /**
     *  @brief Collect all reactions from the resonance parameters
     */
    void collectReactions() {

      this->reactions().clear();

      // go over the reactions in the resolved compund systems
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
     *  @param[in] unresolved   the unresolved resonance compound systems
     */
    ResonanceParameters( std::vector< CompoundSystem > resolved,
                         std::optional< UnresolvedCompoundSystem > unresolved=std::nullopt ) :
        resolved_( std::move( resolved ) ),
        unresolved_( std::move( unresolved ) )  {

      this->collectReactions();
    }

    /* methods */

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
      this->collectReactions();
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
      this->collectReactions();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const ResonanceParameters& left, const ResonanceParameters& right ) {

      return  std::tie( left.resolved(), left.unresolved() ) ==
              std::tie( right.resolved(), right.unresolved() );
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
