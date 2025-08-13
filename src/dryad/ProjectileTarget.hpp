#ifndef NJOY_DRYAD_PROJECTILETARGET
#define NJOY_DRYAD_PROJECTILETARGET

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/InteractionType.hpp"
#include "dryad/Documentation.hpp"
#include "dryad/Reaction.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/resonances/ResonanceParameters.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The data associated to a given projectile and target
   */
  class ProjectileTarget {

    /* fields */
    Documentation documentation_;

    id::ParticleID projectile_id_;
    id::ParticleID target_id_;

    InteractionType interaction_;

    std::optional< resonances::ResonanceParameters > resonances_;
    std::vector< Reaction > reactions_;

    /* auxiliary functions */

    #include "dryad/ProjectileTarget/src/iterator.hpp"

  public:

    /* constructor */
    #include "dryad/ProjectileTarget/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the documentation
     */
    const Documentation& documentation() const {

      return this->documentation_;
    }

    /**
     *  @brief Return the documentation
     */
    Documentation& documentation() {

      return this->documentation_;
    }

    /**
     *  @brief Set the documentation
     *
     *  @param[in] documentation   the documentation
     */
    void documentation( Documentation documentation ) {

      this->documentation_ = std::move( documentation );
    }

    /**
     *  @brief Return the projectile identifier
     */
    const id::ParticleID& projectileIdentifier() const {

      return this->projectile_id_;
    }

    /**
     *  @brief Set the projectile identifier
     *
     *  @param projectile   the projectile identifier
     */
    void projectileIdentifier( id::ParticleID projectile ) {

      this->projectile_id_ = std::move( projectile );
    }

    /**
     *  @brief Return the target identifier
     */
    const id::ParticleID& targetIdentifier() const {

      return this->target_id_;
    }

    /**
     *  @brief Set the target identifier
     *
     *  @param target   the target identifier
     */
    void targetIdentifier( id::ParticleID target ) {

      this->target_id_ = std::move( target );
    }

    /**
     *  @brief Return the interaction type
     */
    const InteractionType& interactionType() const {

      return this->interaction_;
    }

    /**
     *  @brief Set the interaction type
     *
     *  @param type   the interaction type
     */
    void interactionType( InteractionType type ) {

      this->interaction_ = std::move( type );
    }

    /**
     *  @brief Return the resonance parameter data
     */
    const std::optional< resonances::ResonanceParameters >& resonances() const {

      return this->resonances_;
    }

    /**
     *  @brief Return the resonance parameter data
     */
    std::optional< resonances::ResonanceParameters >& resonances() {

      return this->resonances_;
    }

    /**
     *  @brief Set the resonance parameters
     *
     *  @param[in] resonances   the resonance parameters
     */
    void resonances( std::optional< resonances::ResonanceParameters > resonances ) {

      this->resonances_ = std::move( resonances );
    }

    /**
     *  @brief Return the reactions
     */
    const std::vector< Reaction >& reactions() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the reactions
     */
    std::vector< Reaction >& reactions() {

      return this->reactions_;
    }

    /**
     *  @brief Set the reactions
     *
     *  @param[in] reactions   the reactions
     */
    void reactions( std::vector< Reaction > reactions ) {

      this->reactions_ = std::move( reactions );
      this->resolvePartialIdentifiers();
    }

    /**
     *  @brief Return the number of reactions
     */
    std::size_t numberReactions() const {

      return this->reactions().size();
    }

    /**
     *  @brief Return whether or not a given reaction is present
     *
     *  @param[in] id   the reaction identifier
     */
    bool hasReaction( const id::ReactionID& id ) const {

      auto iter = this->iterator( id );
      return iter != this->reactions().end();
    }

    /**
     *  @brief Return the requested reaction
     *
     *  @param[in] id   the reaction identifier
     */
    const Reaction& reaction( const id::ReactionID& id ) const {

      auto iter = this->iterator( id );
      if ( iter != this->reactions().end() ) {

        return *iter;
      }
      else {

        Log::error( "The requested reaction \'{}\' could not be found", id );
        throw std::exception();
      }
    }

    /**
     *  @brief Return the requested reaction
     *
     *  @param[in] id   the reaction identifier
     */
    Reaction& reaction( const id::ReactionID& id ) {

      return const_cast< Reaction& >( const_cast< const ProjectileTarget& >( *this ).reaction( id ) );
    }

    /**
     *  @brief Calculate summation cross sections
     *
     *  This function recalculates the cross section of all summation reactions.
     *  It does so by linearising the cross sections of the partials (if required)
     *  and summing them together.
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    void calculateSummationCrossSections( ToleranceConvergence tolerance = {} ) {

      for ( auto& reaction : this->reactions() ) {

        if ( reaction.isSummationReaction() ) {

          TabulatedCrossSection total;
          for ( std::size_t index = 0; index < reaction.numberPartialReactions(); ++index ) {

            decltype(auto) partial = this->reaction( reaction.partialReactionIdentifiers().value()[index] );
            if ( index == 0 ) {

              total = partial.crossSection().linearise( tolerance );
            }
            else {

              if ( partial.crossSection().isLinearised() ) {

                // operator+= passes the table by reference so no copy this way
                total += partial.crossSection();
              }
              else {

                // linearise makes a new temporary object
                total += partial.crossSection().linearise( tolerance );
              }
            }
          }

          reaction.crossSection( std::move( total ) );
        }
      }
    }

    /**
     *  @brief Resolve all partial reaction identifiers
     *
     *  This function goes through all summation reactions and ensures that
     *  the partial identifiers for each only point to primary reactions.
     */
    void resolvePartialIdentifiers() {

      for ( auto& reaction : this->reactions() ) {

        if ( reaction.isSummationReaction() ) {

          std::vector< id::ReactionID > partials = reaction.partialReactionIdentifiers().value();

          auto iter = partials.begin();
          while ( iter != partials.end() ) {

            decltype(auto) partial = this->reaction( *iter );
            if ( partial.isSummationReaction() ) {

              iter = partials.erase( iter );
              iter = partials.insert( iter, partial.partialReactionIdentifiers()->begin(),
                                            partial.partialReactionIdentifiers()->end() );
            }
            else {

              ++iter;
            }
          }

          reaction.partialReactionIdentifiers( partials );
        }
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ProjectileTarget& right ) const {

      return this->projectileIdentifier() == right.projectileIdentifier() &&
             this->targetIdentifier() == right.targetIdentifier() &&
             this->interactionType() == right.interactionType() &&
             this->resonances() == right.resonances() &&
             this->reactions() == right.reactions();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ProjectileTarget& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
