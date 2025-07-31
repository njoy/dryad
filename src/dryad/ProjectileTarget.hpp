#ifndef NJOY_DRYAD_PROJECTILETARGET
#define NJOY_DRYAD_PROJECTILETARGET

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/InteractionType.hpp"
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
    id::ParticleID projectile_id_;
    id::ParticleID target_id_;

    InteractionType interaction_;

    std::optional< resonances::ResonanceParameters > resonances_;
    std::vector< Reaction > reactions_;

    bool linearised_;

  public:

    /* constructor */
    #include "dryad/ProjectileTarget/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the projectile identifier
     */
    const id::ParticleID& projectileIdentifier() const noexcept {

      return this->projectile_id_;
    }

    /**
     *  @brief Return the target identifier
     */
    const id::ParticleID& targetIdentifier() const noexcept {

      return this->target_id_;
    }

    /**
     *  @brief Return the interaction type
     */
    const InteractionType& interactionType() const noexcept {

      return this->interaction_;
    }

    /**
     *  @brief Return the resonance parameter data
     */
    const std::optional< resonances::ResonanceParameters >& resonances() const noexcept {

      return this->resonances_;
    }

    /**
     *  @brief Return the reactions
     */
    const std::vector< Reaction >& reactions() const noexcept {

      return this->reactions_;
    }

    /**
     *  @brief Return whether or not a given reaction is present
     *
     *  @param[in] id   the reaction identifier
     */
    bool hasReaction( const id::ReactionID& id ) const {

      auto iter = std::find_if( this->reactions().begin(),
                                this->reactions().end(),
                                [&id] ( auto&& reaction )
                                      { return reaction.identifier() == id; } );
      return iter != this->reactions().end();
    }

    /**
     *  @brief Return the requested reaction
     *
     *  @param[in] id   the reaction identifier
     */
    const Reaction& reaction( const id::ReactionID& id ) const {

      auto iter = std::find_if( this->reactions().begin(),
                                this->reactions().end(),
                                [&id] ( auto&& reaction )
                                      { return reaction.identifier() == id; } );
      if ( iter != this->reactions().end() ) {

        return *iter;
      }
      else {

        Log::error( "The requested reaction \'{}\' could not be found", id );
        throw std::exception();
      }
    }

    /**
     *  @brief Return whether or not the data is linearised
     */
    bool isLinearised() const noexcept {

      return this->linearised_;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ProjectileTarget& right ) const noexcept {

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
    bool operator!=( const ProjectileTarget& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
