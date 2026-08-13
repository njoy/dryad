#ifndef NJOY_DRYAD_MULTIGROUPREACTIONPRODUCT
#define NJOY_DRYAD_MULTIGROUPREACTIONPRODUCT

// system includes
#include <optional>
#include <tuple>
#include <variant>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/MultigroupMultiplicity.hpp"
#include "njoy/dryad/MultigroupAverageCosine.hpp"
#include "njoy/dryad/MultigroupAverageEnergy.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The multigroup data associated to a single reaction product
   */
  class MultigroupReactionProduct {

  public:

    /* type aliases */
    using Multiplicity = std::variant< int, MultigroupMultiplicity >;

  private:

    /* fields */

    id::ParticleID product_;

    std::optional< id::ParticleID > parent_;
    std::size_t chain_index_;

    Multiplicity multiplicity_;

    std::optional< MultigroupAverageCosine > average_cosine_;
    std::optional< MultigroupAverageEnergy > average_energy_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    MultigroupReactionProduct() = default;

    MultigroupReactionProduct( const MultigroupReactionProduct& ) = default;
    MultigroupReactionProduct( MultigroupReactionProduct&& ) = default;

    MultigroupReactionProduct& operator=( const MultigroupReactionProduct& ) = default;
    MultigroupReactionProduct& operator=( MultigroupReactionProduct&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] product         the reaction product identifier
     *  @param[in] multiplicity    the multiplicity of the reaction product
     *  @param[in] averageCosine   the optional average reaction product cosine
     *  @param[in] averageEnergy   the optional average reaction product energy
     *  @param[in] parent          the parent reaction product (default: none)
     *  @param[in] chain           the chain index of the reaction product (default: 0)
     */
    MultigroupReactionProduct( id::ParticleID product,
                               Multiplicity multiplicity,
                               std::optional< MultigroupAverageCosine > averageCosine = std::nullopt,
                               std::optional< MultigroupAverageEnergy > averageEnergy = std::nullopt,
                               std::optional< id::ParticleID > parent = std::nullopt,
                               std::size_t chain = 0 ) :
        product_( std::move( product ) ),
        parent_( std::move( parent ) ),
        chain_index_( chain ),
        multiplicity_( std::move( multiplicity ) ),
        average_cosine_( std::move( averageCosine ) ),
        average_energy_( std::move( averageEnergy ) ) {}

    /**
     *  @brief Convenience constructor
     *
     *  @param[in] product         the reaction product identifier
     *  @param[in] multiplicity    the reaction product multiplicity
     *  @param[in] averageEnergy   the average reaction product energy
     */
    MultigroupReactionProduct( id::ParticleID product,
                              Multiplicity multiplicity,
                              MultigroupAverageEnergy averageEnergy ) :
        MultigroupReactionProduct( std::move( product ),
                                   std::move( multiplicity ),
                                   std::nullopt,
                                   std::move( averageEnergy ),
                                   std::nullopt,
                                   0 ) {}

    /* methods */

    /**
     *  @brief Return the particle identifier for the reaction product
     */
    const id::ParticleID& productIdentifier() const {

      return this->product_;
    }

    /**
     *  @brief Set the particle identifier for the reaction product
     *
     *  @param[in] product   the reaction product identifier
     */
    void productIdentifier( id::ParticleID product ) {

      this->product_ = std::move( product );
    }

    /**
     *  @brief Return the particle identifier for the parent product
     */
    const std::optional< id::ParticleID >& parentIdentifier() const {

      return this->parent_;
    }

    /**
     *  @brief Set the particle identifier for the parent product
     *
     *  @param[in] parent   the parent product identifier
     */
    void parentIdentifier( std::optional< id::ParticleID > parent ) {

      this->parent_ = std::move( parent );
    }

    /**
     *  @brief Return the chain index of the reaction product
     */
    std::size_t chainIndex() const {

      return this->chain_index_;
    }

    /**
     *  @brief Set the chain index of the reaction product
     *
     *  @param[in] index   the chain index
     */
    void chainIndex( std::size_t index ) {

      this->chain_index_ = index;
    }

    /**
     *  @brief Return the reaction product multiplicity
     */
    const Multiplicity& multiplicity() const {

      return this->multiplicity_;
    }

    /**
     *  @brief Set the reaction product multiplicity
     *
     *  @param[in] multiplicity   the multiplicity of the reaction product
     */
    void multiplicity( Multiplicity multiplicity ) {

      this->multiplicity_ = std::move( multiplicity );
    }

    /**
     *  @brief Return the average reaction product cosine
     */
    const std::optional< MultigroupAverageCosine >& averageCosine() const {

      return this->average_cosine_;
    }

    /**
     *  @brief Set the average reaction product cosine
     *
     *  @param[in] averageCosine   the average reaction product cosine
     */
    void averageCosine( std::optional< MultigroupAverageCosine > averageCosine ) {

      this->average_cosine_ = std::move( averageCosine );
    }

    /**
     *  @brief Return the average reaction product energy
     */
    const std::optional< MultigroupAverageEnergy >& averageEnergy() const {

      return this->average_energy_;
    }

    /**
     *  @brief Set the average reaction product energy
     *
     *  @param[in] averageEnergy   the average reaction product energy
     */
    void averageEnergy( std::optional< MultigroupAverageEnergy > averageEnergy ) {

      this->average_energy_ = std::move( averageEnergy );
    }

    /**
     *  @brief Return whether or not the reaction product has average reaction
     *         product cosine data
     */
    bool hasAverageCosine() const {

      return this->average_cosine_.has_value();
    }

    /**
     *  @brief Return whether or not the reaction product has average reaction
     *         product energy data
     */
    bool hasAverageEnergy() const {

      return this->average_energy_.has_value();
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const MultigroupReactionProduct& right ) const {

      return std::tie( this->productIdentifier(), this->parentIdentifier(),
                       this->chain_index_, this->multiplicity(),
                       this->averageCosine(), this->averageEnergy() ) ==
             std::tie( right.productIdentifier(), right.parentIdentifier(),
                       right.chain_index_, right.multiplicity(),
                       right.averageCosine(), right.averageEnergy() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const MultigroupReactionProduct& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
