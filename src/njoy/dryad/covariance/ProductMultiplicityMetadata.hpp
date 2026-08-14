#ifndef NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYMETADATA
#define NJOY_DRYAD_COVARIANCE_PRODUCTMULTIPLICITYMETADATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/EnergyGroup.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/base/Metadata.hpp"

namespace njoy {
namespace dryad {
namespace covariance {

  /**
   *  @class
   *  @brief Covariance metadata for product multiplicities
   */
  class ProductMultiplicityMetadata :
    protected base::Metadata< id::ReactionID, id::EnergyGroup, id::ParticleID > {

    /* type aliases */

    using Parent = base::Metadata< id::ReactionID, id::EnergyGroup, id::ParticleID >;

    /* fields */

    std::vector< id::ReactionID > reactions_;
    std::vector< double > energies_;
    std::vector< id::ParticleID > products_;

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
                                            const std::vector< double >& energies,
                                            const std::vector< id::ParticleID >& products ) {

      if ( energies.size() < 2 || reactions.size() == 0 || products.size() == 0 ) {

        Log::error( "There should be at least 2 energy values, 1 reaction and 1 product identifier." );
        throw std::exception();
      }
      if ( ! std::is_sorted( energies.begin(), energies.end() ) ) {

        Log::error( "The energy group values do note appear to be sorted." );
        throw std::exception();
      }
      if ( ! std::is_sorted( products.begin(), products.end() ) ) {

        Log::error( "The product identifiers do not appear to be sorted." );
        throw std::exception();
      }

      std::vector< Key > keys;
      keys.reserve( reactions.size() * ( energies.size() - 1 ) * products.size() );
      for ( std::size_t i = 0; i < reactions.size(); ++i ) {

        for ( std::size_t j = 0; j < energies.size() - 1; ++j ) {

          for ( std::size_t k = 0; k < products.size(); ++k ) {

            keys.emplace_back( Key{ reactions[i],
                                    { energies[j], energies[j+1] },
                                    products[k] } );
          }
        }
      }
      return keys;
    }

    /**
     *  @brief Reconstruct metadata from keys
     *
     *  This method extracts the unique reactions, energy groups and products from the
     *  keys. This function relies on the fact that tuple keys are lexographically
     *  sorted (as implemented by the operator< on std::tuple).
     */
    void updateMetadata() {

      //! @todo once we move to c++23, use ranges instead of for loops

      // get all the products in the metadata
      auto product = std::get< 2 >( this->keys().front() );
      auto iter = std::find_if( this->keys().begin() + 1, this->keys().end(),
                                [&product] ( const auto& tuple )
                                           { return product == std::get< 2 >( tuple ); } );
      this->products_.resize( std::distance( this->keys().begin(), iter ) );
      std::transform( this->keys().begin(), iter, this->products_.begin(),
                      [] ( const auto& tuple ) { return std::get< 2 >( tuple ); } );

      // calculate stride on the energy dimension and loop
      auto stride = this->products_.size();
      auto group = std::get< 1 >( this->keys().front() );
      iter = std::find_if( this->keys().begin() + stride, this->keys().end(),
                           [&group] ( const auto& tuple )
                                    { return group == std::get< 1 >( tuple ); } );
      this->energies_.resize( std::distance( this->keys().begin(), iter ) / stride + 1 );
      this->energies_.front() = std::get< 1 >( this->keys().front() ).lowerEnergy();
      for ( unsigned int i = 0; i < std::distance( this->keys().begin(), iter ); i = i + stride ) {

        this->energies_[ i / stride + 1 ] = std::get< 1 >( this->keys()[i] ).upperEnergy();
      }

      // calculate stride on the reaction dimension and loop
      stride = ( this->energies_.size() - 1 ) * this->products_.size();
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
    ProductMultiplicityMetadata() = default;

    ProductMultiplicityMetadata( const ProductMultiplicityMetadata& ) = default;
    ProductMultiplicityMetadata( ProductMultiplicityMetadata&& ) = default;

    ProductMultiplicityMetadata& operator=( const ProductMultiplicityMetadata& ) = default;
    ProductMultiplicityMetadata& operator=( ProductMultiplicityMetadata&& ) = default;

    /**
     *  @brief Internal constructor
     *
     *  @param[in] keys   the keys associated with the covariance matrix
     */
    ProductMultiplicityMetadata( std::vector< Key > keys ) :
        Parent( std::move( keys ) ) {

      this->updateMetadata();
    }

    /**
     *  @brief Constructor
     *
     *  @param[in] reactions   the reaction identifiers
     *  @param[in] energies    the energy boundary values
     *  @param[in] products    the product identifiers
     */
    ProductMultiplicityMetadata( std::vector< id::ReactionID > reactions,
                                 std::vector< double > energies,
                                 std::vector< id::ParticleID > products ) :
        Parent( generateKeys( reactions, energies, products ) ),
        reactions_( std::move( reactions ) ),
        energies_( std::move( energies ) ),
        products_( std::move( products ) ) {}

    /* methods */

    /**
     *  @brief Return the reaction identifiers
     */
    const std::vector< id::ReactionID >& reactionIdentifiers() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the energy group boundaries
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the reaction product identifiers
     */
    const std::vector< id::ParticleID >& productIdentifiers() const {

      return this->products_;
    }

    using Parent::keys;
    using Parent::selection;

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ProductMultiplicityMetadata& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ProductMultiplicityMetadata& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
