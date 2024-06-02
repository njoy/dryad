#ifndef NJOY_DRYAD_PROJECTILETARGET
#define NJOY_DRYAD_PROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/InteractionType.hpp"
#include "dryad/ParticleID.hpp"
#include "dryad/Reaction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The data associated to a given projectile and target
   */
  class ProjectileTarget {

    /* fields */
    ParticleID projectile_id_;
    ParticleID target_id_;

    InteractionType interaction_;

    std::vector< Reaction > reactions_;

    bool linearised_;

  public:

    /* constructor */
    #include "dryad/ProjectileTarget/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the projectile identifier
     */
    const ParticleID& projectileIdentifier() const noexcept {

      return this->projectile_id_;
    }

    /**
     *  @brief Return the target identifier
     */
    const ParticleID& targetIdentifier() const noexcept {

      return this->target_id_;
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
    bool hasReaction( const ReactionID& id ) const {

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
    const Reaction& reaction( const ReactionID& id ) const {

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
     *  @brief Linearise the data and return a new ProjectileTarget object
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    ProjectileTarget linearise( ToleranceConvergence tolerance = {} ) const noexcept {

      std::vector< Reaction > reactions;
      for ( auto&& reaction : this->reactions() ) {

        reactions.emplace_back( reaction.linearise( tolerance ) );
      }

      return ProjectileTarget( this->projectileIdentifier(), this->targetIdentifier(),
                               std::move( reactions ) );
    }

    /**
     *  @brief Linearise the data inplace
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    void lineariseInplace( ToleranceConvergence tolerance = {} ) noexcept {

      for ( auto&& reaction : this->reactions_ ) {

        reaction.lineariseInplace( tolerance );
      }
      this->linearised_ = true;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
