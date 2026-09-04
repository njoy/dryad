#ifndef NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS
#define NJOY_DRYAD_RESONANCES_RESONANCEPARAMETERS

// system includes
#include <variant>
#include <vector>

// other includes
#include "njoy/dryad/resonances/CompoundSystem.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The resonance parameter data
   *
   *  Note: this is currently a placeholder
   */
  class ResonanceParameters {

    /* fields */

    std::vector< CompoundSystem > resolved_;

    std::vector< id::ReactionID > reactions_;

    /* auxiliary functions */

    /**
     *  @brief Collect all reactions from the resonance parameters
     */
    void collectReactions() {

      for ( auto&& compound : this->resolved() ) {

        for ( auto&& id : compound.reactions() ) {

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
     *  @param[in] resolved   the resolved resonance compound systems
     */
    ResonanceParameters( std::vector< CompoundSystem > resolved ) :
        resolved_( std::move( resolved ) ) {

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
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const ResonanceParameters& left, const ResonanceParameters& right ) {

      return left.resolved() == right.resolved();
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
