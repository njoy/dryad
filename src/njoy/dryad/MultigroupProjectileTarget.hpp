#ifndef NJOY_DRYAD_MULTIGROUPPROJECTILETARGET
#define NJOY_DRYAD_MULTIGROUPPROJECTILETARGET

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/dryad/InteractionType.hpp"
#include "njoy/dryad/Documentation.hpp"
#include "njoy/dryad/MultigroupReaction.hpp"
#include "njoy/dryad/covariance/CovarianceData.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The multigroup data associated to a given projectile and target
   */
  class MultigroupProjectileTarget {

    /* fields */

    Documentation documentation_;

    id::ParticleID projectile_id_;
    id::ParticleID target_id_;

    InteractionType interaction_;

    std::vector< MultigroupReaction > reactions_;

    std::optional< covariance::CovarianceData > covariances_;

    /* auxiliary functions */

    /**
     *  @brief Return an iterator for a given reaction (using find_if)
     *
     *  @param[in] id   the reaction identifier
     */
    auto iterator( const id::ReactionID& id ) const {

      return std::find_if( this->reactions().begin(), this->reactions().end(),
                           [&id] ( auto&& reaction )
                                 { return reaction.identifier() == id; } );
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MultigroupProjectileTarget() = default;

    MultigroupProjectileTarget( const MultigroupProjectileTarget& ) = default;
    MultigroupProjectileTarget( MultigroupProjectileTarget&& ) = default;

    MultigroupProjectileTarget& operator=( const MultigroupProjectileTarget& ) = default;
    MultigroupProjectileTarget& operator=( MultigroupProjectileTarget&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] documentation   the documentation
     *  @param[in] projectile      the projectile identifier
     *  @param[in] target          the target identifier
     *  @param[in] type            the interaction type
     *  @param[in] reactions       the reaction data
     *  @param[in] covariances     the optional covariance data (default: none)
     */
    MultigroupProjectileTarget( Documentation documentation,
                                id::ParticleID projectile,
                                id::ParticleID target,
                                InteractionType type,
                                std::vector< MultigroupReaction > reactions,
                                std::optional< covariance::CovarianceData > covariances = std::nullopt ) :
        documentation_( std::move( documentation ) ),
        projectile_id_( std::move( projectile ) ),
        target_id_( std::move( target ) ),
        interaction_( type ),
        reactions_( std::move( reactions ) ),
        covariances_( std::move( covariances ) ) {

      this->resolvePartialIdentifiers();
    }

    /**
     *  @brief Constructor
     *
     *  @param[in] projectile    the projectile identifier
     *  @param[in] target        the target identifier
     *  @param[in] type          the interaction type
     *  @param[in] reactions     the reaction data
     *  @param[in] covariances   the optional covariance data (default: none)
     */
    MultigroupProjectileTarget( id::ParticleID projectile,
                                id::ParticleID target,
                                InteractionType type,
                                std::vector< MultigroupReaction > reactions,
                                std::optional< covariance::CovarianceData > covariances = std::nullopt ) :
        MultigroupProjectileTarget( {},
                                    std::move( projectile ),
                                    std::move( target ),
                                    type,
                                    std::move( reactions ),
                                    std::move( covariances ) ) {}

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
     *  @param[in] projectile   the projectile identifier
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
     *  @param[in] target   the target identifier
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
     *  @param[in] type   the interaction type
     */
    void interactionType( InteractionType type ) {

      this->interaction_ = std::move( type );
    }

    /**
     *  @brief Return the reactions
     */
    const std::vector< MultigroupReaction >& reactions() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the reactions
     */
    std::vector< MultigroupReaction >& reactions() {

      return this->reactions_;
    }

    /**
     *  @brief Set the reactions
     *
     *  @param[in] reactions   the reactions
     */
    void reactions( std::vector< MultigroupReaction > reactions ) {

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
    const MultigroupReaction& reaction( const id::ReactionID& id ) const {

      auto iter = this->iterator( id );
      if ( iter != this->reactions().end() ) {

        return *iter;
      }
      else {

        Log::error( "The requested reaction \'{}\' could not be found", id.symbol() );
        throw std::exception();
      }
    }

    /**
     *  @brief Return the requested reaction
     *
     *  @param[in] id   the reaction identifier
     */
    MultigroupReaction& reaction( const id::ReactionID& id ) {

      return const_cast< MultigroupReaction& >(
                 const_cast< const MultigroupProjectileTarget& >( *this ).reaction( id ) );
    }

    /**
     *  @brief Return the covariance data
     */
    const std::optional< covariance::CovarianceData >& covarianceData() const {

      return this->covariances_;
    }

    /**
     *  @brief Return the covariance data
     */
    std::optional< covariance::CovarianceData >& covarianceData() {

      return this->covariances_;
    }

    /**
     *  @brief Set the covariance data
     *
     *  @param[in] covariances   the covariance data
     */
    void covarianceData( std::optional< covariance::CovarianceData > covariances ) {

      this->covariances_ = std::move( covariances );
    }

    /**
     *  @brief Calculate summation cross sections
     *
     *  This function recalculates the cross section of all summation reactions
     *  by summing the cross sections of the partials together. The partials are
     *  assumed to share the same group structure as the summation reaction.
     */
    void calculateSummationCrossSections() {

      for ( auto& reaction : this->reactions() ) {

        if ( reaction.isSummationReaction() ) {

          MultigroupCrossSection total;
          for ( std::size_t index = 0; index < reaction.numberPartialReactions(); ++index ) {

            decltype(auto) partial = this->reaction( reaction.partialReactionIdentifiers().value()[index] );
            if ( index == 0 ) {

              total = partial.crossSection();
            }
            else {

              total += partial.crossSection();
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

      //! @todo verify that there are no cyclical dependencies
      //!       an algorithm that finds cycles in a graph can be useful here

      for ( auto& reaction : this->reactions() ) {

        if ( reaction.isSummationReaction() ) {

          std::vector< id::ReactionID > partials = reaction.partialReactionIdentifiers().value();

          auto iter = partials.begin();
          while ( iter != partials.end() ) {

            if ( this->hasReaction( *iter ) ) {

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
    bool operator==( const MultigroupProjectileTarget& right ) const {

      return this->projectileIdentifier() == right.projectileIdentifier() &&
             this->targetIdentifier() == right.targetIdentifier() &&
             this->interactionType() == right.interactionType() &&
             this->reactions() == right.reactions();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const MultigroupProjectileTarget& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
