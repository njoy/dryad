#ifndef NJOY_DRYAD_COVARIANCE_ANGULARDISTRIBUTIONMETADATA
#define NJOY_DRYAD_COVARIANCE_ANGULARDISTRIBUTIONMETADATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/EnergyGroup.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/base/Metadata.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Covariance metadata for angular distributions
   */
  class AngularDistributionMetadata :
    protected base::Metadata< id::ReactionID, std::size_t, id::EnergyGroup > {

    /* type aliases */

    using Parent = base::Metadata< id::ReactionID, std::size_t, id::EnergyGroup >;

    /* fields */

    std::vector< id::ReactionID > reactions_;
    std::vector< std::size_t > moments_;
    std::vector< double > energies_;

    /* auxiliary functions */

    static std::vector< id::EnergyGroup >
    generateEnergyGroups( const std::vector< double >& energies ) {

      std::vector< id::EnergyGroup > groups;
      groups.reserve( energies.size() );
      for ( std::size_t i = 0; i < energies.size() - 1; ++i ) {

        groups.emplace_back( energies[i], energies[i+1] );
      }
      return groups;
    }

    static std::vector< Key > generateKeys( const std::vector< id::ReactionID >& reactions,
                                            const std::vector< std::size_t >& moments,
                                            const std::vector< double >& energies ) {

      if ( moments.size() == 0 || energies.size() < 2 || reactions.size() == 0 ) {

        Log::error( "There should be at least 1 Legendre moment, 2 energy values and 1 reaction identifier." );
        throw std::exception();
      }
      if ( ! std::is_sorted( energies.begin(), energies.end() ) ) {

        Log::error( "The energy group values do not appear to be sorted." );
        throw std::exception();
      }

      std::vector< Key > keys;
      keys.reserve( reactions.size() * moments.size() * ( energies.size() - 1 ) );
      for ( std::size_t i = 0; i < reactions.size(); ++i ) {

        for ( std::size_t j = 0; j < moments.size(); ++j ) {

          for ( std::size_t k = 0; k < energies.size() - 1; ++k ) {

            keys.emplace_back( Key{ reactions[i],
                                    moments[j],
                                    { energies[k], energies[k+1] } } );
          }
        }
      }
      return keys;
    }

    /**
     *  @brief Reconstruct metadata from keys
     *
     *  This method extracts the unique reactions, Legendre moment orders, and energy groups
     *  from the keys. This function relies on the fact that tuple keys are lexographically
     *  sorted (as implemented by the operator< on std::tuple).
     */
    void updateMetadata() {

      //! @todo once we move to c++23, use ranges instead of for loops

      // get all the energy groups in the metadata
      auto group = std::get< 2 >( this->keys().front() );
      auto iter = std::find_if( this->keys().begin() + 1, this->keys().end(),
                                [&group] ( const auto& tuple )
                                         { return group == std::get< 2 >( tuple ); } );
      this->energies_.resize( std::distance( this->keys().begin(), iter ) + 1 );
      this->energies_.front() = group.lowerEnergy();
      std::transform( this->keys().begin(), iter, this->energies_.begin() + 1,
                      [] ( const auto& tuple ) { return std::get< 2 >( tuple ).upperEnergy(); } );

      // calculate stride on the moment dimension and loop
      auto stride = this->energies_.size() - 1;
      auto moment = std::get< 1 >( this->keys().front() );
      iter = std::find_if( this->keys().begin() + stride, this->keys().end(),
                           [&moment] ( const auto& tuple )
                                      { return moment == std::get< 1 >( tuple ); } );
      this->moments_.resize( std::distance( this->keys().begin(), iter ) / stride );
      for ( unsigned int i = 0; i < std::distance( this->keys().begin(), iter ); i = i + stride ) {

        this->moments_[ i / stride] = std::get< 1 >( this->keys()[i] );
      }

      // calculate stride on the reaction dimension and loop
      stride = ( this->energies_.size() - 1 ) * this->moments_.size();
      this->reactions_.resize( this->keys().size() / stride );
      for ( unsigned int i = 0; i < this->keys().size(); i = i + stride ) {

        this->reactions_[ i / stride ] = std::get< 0 >( this->keys()[i] );
      }
    }

  public:

    /* constructor */
    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    AngularDistributionMetadata() = default;

    AngularDistributionMetadata( const AngularDistributionMetadata& ) = default;
    AngularDistributionMetadata( AngularDistributionMetadata&& ) = default;

    AngularDistributionMetadata& operator=( const AngularDistributionMetadata& ) = default;
    AngularDistributionMetadata& operator=( AngularDistributionMetadata&& ) = default;

    /**
     *  @brief Internal constructor
     *
     *  @param[in] keys   the keys associated with the covariance matrix
     */
    AngularDistributionMetadata( std::vector< Key > keys ) :
        Parent( std::move( keys ) ) {

      this->updateMetadata();
    }

    /**
     *  @brief Constructor
     *
     *  @param[in] reactions   the reaction identifiers
     *  @param[in] moments     the Legendre moment values
     *  @param[in] energies    the energy boundary values
     */
    AngularDistributionMetadata( std::vector< id::ReactionID > reactions,
                                 std::vector< std::size_t > moments,
                                 std::vector< double > energies ) :
        Parent( generateKeys( reactions, moments, energies ) ),
        reactions_( std::move( reactions ) ),
        moments_( std::move( moments ) ),
        energies_( std::move( energies ) ) {}

    /**
     *  @brief Constructor for a single reaction and moment
     *
     *  @param[in] reaction   the reaction identifier
     *  @param[in] moment     the Legendre moment value
     *  @param[in] energies   the energy boundary values
     */
    AngularDistributionMetadata( id::ReactionID reaction,
                                 std::size_t moment,
                                 std::vector< double > energies ) :
        AngularDistributionMetadata( std::vector< id::ReactionID >{ std::move( reaction ) },
                                     std::vector< std::size_t >{ std::move( moment ) },
                                     std::move( energies ) ) {}

    /* methods */

    /**
     *  @brief Return the reaction identifiers
     */
    const std::vector< id::ReactionID >& reactionIdentifiers() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the Legendre moment orders
     */
    const std::vector< std::size_t >& moments() const {

      return this->moments_;
    }

    /**
     *  @brief Return the energy group boundaries
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    using Parent::keys;
    using Parent::selection;

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const AngularDistributionMetadata& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const AngularDistributionMetadata& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
