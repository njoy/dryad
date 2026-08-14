#ifndef NJOY_DRYAD_COVARIANCE_CROSSSECTIONMETADATA
#define NJOY_DRYAD_COVARIANCE_CROSSSECTIONMETADATA

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
   *  @brief Covariance metadata for cross sections
   */
  class CrossSectionMetadata :
    protected base::Metadata< id::ReactionID, id::EnergyGroup > {

    /* type aliases */

    using Parent = base::Metadata< id::ReactionID, id::EnergyGroup >;

    /* fields */

    std::vector< id::ReactionID > reactions_;
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
                                            const std::vector< double >& energies ) {

      if ( energies.size() < 2 || reactions.size() == 0 ) {

        Log::error( "There should be at least 2 energy values and 1 reaction identifier." );
        throw std::exception();
      }
      if ( ! std::is_sorted( energies.begin(), energies.end() ) ) {

        Log::error( "The energy group values do not appear to be sorted." );
        throw std::exception();
      }

      std::vector< Key > keys;
      keys.reserve( reactions.size() * ( energies.size() - 1 ) );
      for ( std::size_t i = 0; i < reactions.size(); ++i ) {

        for ( std::size_t j = 0; j < energies.size() - 1; ++j ) {

          keys.emplace_back( Key{ reactions[i],
                                  { energies[j], energies[j+1] } } );
        }
      }
      return keys;
    }

    /**
     *  @brief Reconstruct metadata from keys
     *
     *  This method extracts the unique reactions and energy groups from the keys.
     *  This function relies on the fact that tuple keys are lexographically sorted
     *  (as implemented by the operator< on std::tuple).
     */
    void updateMetadata() {

      //! @todo once we move to c++23, use ranges instead of for loops

      // get all the energy groups in the metadata
      auto group = std::get< 1 >( this->keys().front() );
      auto iter = std::find_if( this->keys().begin() + 1, this->keys().end(),
                                [&group] ( const auto& tuple )
                                         { return group == std::get< 1 >( tuple ); } );
      this->energies_.resize( std::distance( this->keys().begin(), iter ) + 1 );
      this->energies_.front() = group.lowerEnergy();
      std::transform( this->keys().begin(), iter, this->energies_.begin() + 1,
                      [] ( const auto& tuple ) { return std::get< 1 >( tuple ).upperEnergy(); } );

      // calculate stride on the reaction dimension and loop
      auto stride = this->energies_.size() - 1;
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
    CrossSectionMetadata() = default;

    CrossSectionMetadata( const CrossSectionMetadata& ) = default;
    CrossSectionMetadata( CrossSectionMetadata&& ) = default;

    CrossSectionMetadata& operator=( const CrossSectionMetadata& ) = default;
    CrossSectionMetadata& operator=( CrossSectionMetadata&& ) = default;

    /**
     *  @brief Internal constructor
     *
     *  @param[in] keys   the keys associated with the covariance matrix
     */
    CrossSectionMetadata( std::vector< Key > keys ) :
        Parent( std::move( keys ) ) {

      this->updateMetadata();
    }

    /**
     *  @brief Constructor
     *
     *  @param[in] reactions   the reaction identifiers
     *  @param[in] energies    the energy boundary values
     */
    CrossSectionMetadata( std::vector< id::ReactionID > reactions,
                          std::vector< double > energies ) :
        Parent( generateKeys( reactions, energies ) ),
        reactions_( std::move( reactions ) ),
        energies_( std::move( energies ) ) {}

    /**
     *  @brief Constructor for a single reaction
     *
     *  @param[in] reaction   the reaction identifier
     *  @param[in] energies   the energy boundary values
     */
    CrossSectionMetadata( id::ReactionID reaction,
                          std::vector< double > energies ) :
        CrossSectionMetadata( std::vector< id::ReactionID >{ std::move( reaction ) },
                              std::move( energies ) ) {}

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

    using Parent::keys;
    using Parent::selection;

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CrossSectionMetadata& right ) const {

      return Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CrossSectionMetadata& right ) const {

      return ! this->operator==( right );
    }
  };

} // covariance namespace
} // dryad namespace
} // njoy namespace

#endif
