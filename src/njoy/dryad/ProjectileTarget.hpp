#ifndef NJOY_DRYAD_PROJECTILETARGET
#define NJOY_DRYAD_PROJECTILETARGET

// system includes
#include <algorithm>
#include <optional>
#include <vector>

// other includes
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/InteractionType.hpp"
#include "njoy/dryad/Documentation.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/covariance/CovarianceData.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"

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

    std::optional< ParticleDatabase > particles_;
    std::optional< resonances::ResonanceParameters > resonances_;
    std::vector< Reaction > reactions_;

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

    /* constructor */

    /**
     *  @brief Private constructor
     */
    ProjectileTarget( Documentation&& documentation,
                      id::ParticleID&& projectile,
                      id::ParticleID&& target,
                      InteractionType type,
                      std::optional< ParticleDatabase >&& particles,
                      std::optional< resonances::ResonanceParameters > resonances,
                      std::vector< Reaction >&& reactions,
                      std::optional< covariance::CovarianceData > covariances,
                      bool normalise ) :
        documentation_( std::move( documentation ) ),
        projectile_id_( std::move( projectile ) ),
        target_id_( std::move( target ) ),
        interaction_( type ),
        particles_( std::move( particles ) ),
        resonances_( std::move( resonances ) ),
        reactions_( std::move( reactions ) ),
        covariances_( std::move( covariances ) ) {

      this->resolvePartialIdentifiers();
      if ( normalise ) {

        this->normalise();
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ProjectileTarget() = default;

    ProjectileTarget( const ProjectileTarget& ) = default;
    ProjectileTarget( ProjectileTarget&& ) = default;

    ProjectileTarget& operator=( const ProjectileTarget& ) = default;
    ProjectileTarget& operator=( ProjectileTarget&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] documentation   the documentation
     *  @param[in] projectile      the projectile identifier
     *  @param[in] target          the target identifier
     *  @param[in] type            the interaction type
     *  @param[in] reactions       the reaction data
     *  @param[in] particles       the optional particle data (default: none)
     *  @param[in] resonances      the optional resonance parameters (default: none)
     *  @param[in] covariances     the optional covariance data (default: none)
     *  @param[in] normalise       option to indicate whether or not to normalise
     *                             all probability data (default: no normalisation)
     */
    ProjectileTarget( Documentation documentation,
                      id::ParticleID projectile,
                      id::ParticleID target,
                      InteractionType type,
                      std::vector< Reaction > reactions,
                      std::optional< ParticleDatabase > particles = std::nullopt,
                      std::optional< resonances::ResonanceParameters > resonances = std::nullopt,
                      std::optional< covariance::CovarianceData > covariances = std::nullopt,
                      bool normalise = false ) :
        ProjectileTarget( std::move( documentation ),
                          std::move( projectile ),
                          std::move( target ),
                          type,
                          std::move( particles ),
                          std::move( resonances ),
                          std::move( reactions ),
                          std::move( covariances ),
                          normalise ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] projectile    the projectile identifier
     *  @param[in] target        the target identifier
     *  @param[in] type          the interaction type
     *  @param[in] reactions     the reaction data
     *  @param[in] particles     the optional particle data (default: none)
     *  @param[in] resonances    the optional resonance parameters (default: none)
     *  @param[in] covariances   the optional covariance data (default: none)
     *  @param[in] normalise     option to indicate whether or not to normalise
     *                           all probability data (default: no normalisation)
     */
    ProjectileTarget( id::ParticleID projectile,
                      id::ParticleID target,
                      InteractionType type,
                      std::vector< Reaction > reactions,
                      std::optional< ParticleDatabase > particles = std::nullopt,
                      std::optional< resonances::ResonanceParameters > resonances = std::nullopt,
                      std::optional< covariance::CovarianceData > covariances = std::nullopt,
                      bool normalise = false ) :
        ProjectileTarget( {},
                          std::move( projectile ),
                          std::move( target ),
                          type,
                          std::move( particles ),
                          std::move( resonances ),
                          std::move( reactions ),
                          std::move( covariances ),
                          normalise ) {}

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
     *  @brief Return the particle data
     */
    const std::optional< ParticleDatabase >& particleData() const {

      return this->particles_;
    }

    /**
     *  @brief Return the particle data
     */
    std::optional< ParticleDatabase >& particleData() {

      return this->particles_;
    }

    /**
     *  @brief Set the particle data
     *
     *  @param[in] particles   the particle data
     */
    void particleData( std::optional< ParticleDatabase > particles ) {

      this->particles_ = std::move( particles );
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

        Log::error( "The requested reaction \'{}\' could not be found", id.symbol() );
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
     *  @brief Calculate average outgoing energies for all reaction products
     *  @param[in] tolerance   the integration tolerance (default: 1e-8)
     */
    void calculateAverageEnergy( double tolerance = constants::integration::tolerance ) {

      for ( auto& reaction : this->reactions() ) {

        reaction.calculateAverageEnergy( tolerance );
      }
    }

    /**
     *  @brief Unionise cross section data
     *
     *  This function takes all cross section data and unionises the cross section
     *  grids. It does not linearise the data but reevaluates the data using the
     *  proper interpolation types of the cross section data.
     *
     *  By default, summation cross sections are included in the unionisation process.
     *  unless explicitly excluded by the user. Switching on the exclusion of summation
     *  cross sections may be useful when the user is going to recalculate the summation
     *  cross sections after unionisation.
     *
     *  @param[in] exclude_summation   option to exclude summation reactions in the
     *                                 unionisation (default: false)
     */
    void unioniseCrossSections( bool exclude_summation = false ) {

      // generate the union grid for the cross section data
      scion::unionisation::Unioniser< std::vector< double > > unioniser;
      for ( const Reaction& reaction : this->reactions() ) {

        // exclude summation when requested
        if ( ! ( exclude_summation && reaction.isSummationReaction() ) ) {

          unioniser.addGrid( reaction.crossSection().energies(), reaction.crossSection().values() );
        }
      }
      std::vector< double > energies = unioniser.unionise();

      // reevaluate all cross section data on the new union grid
      for ( Reaction& reaction : this->reactions() ) {

        // exclude summation when requested
        if ( ! ( exclude_summation && reaction.isSummationReaction() ) ) {

          decltype(auto) xs = reaction.crossSection();
          std::vector< double > values = unioniser.evaluate( xs.energies(), xs.values(), xs.boundaries(), xs.interpolants() );
          std::vector< std::size_t > boundaries = { values.size() - 1 };
          std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };

          if ( ! xs.isLinearised() ) {

            auto pair = unioniser.updateBoundariesAndInterpolants( xs.energies(), xs.boundaries(), xs.interpolants() );
            boundaries = std::move( pair.first );
            interpolants = std::move( pair.second );
          }

          TabulatedCrossSection newxs( energies, std::move( values ),
                                       std::move( boundaries ), std::move( interpolants ) );

          reaction.crossSection( std::move( newxs ) );
        }
      }
    }

    /**
     *  @brief Calculate summation cross sections
     *
     *  This function recalculates the cross section of all summation reactions.
     *  It does so by linearising the cross sections of the partials (if required)
     *  and summing them together.
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1%)
     */
    void calculateSummationCrossSections( double tolerance = constants::linearisation::tolerance ) {

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

      //! @todo verify that there are no cyclical dependencies
      //!       an algorithm that finds cycles in a graph can be useful here

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
     *  @brief Normalise the distribution data
     */
    void normalise() {

      for ( auto&& reaction : this->reactions() ) {

        reaction.normalise();
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
