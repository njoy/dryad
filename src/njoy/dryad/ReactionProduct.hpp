#ifndef NJOY_DRYAD_REACTIONPRODUCT
#define NJOY_DRYAD_REACTIONPRODUCT

// system includes
#include <optional>
#include <tuple>
#include <variant>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/PolynomialMultiplicity.hpp"
#include "njoy/dryad/TabulatedMultiplicity.hpp"
#include "njoy/dryad/TabulatedAverageCosine.hpp"
#include "njoy/dryad/TabulatedAverageEnergy.hpp"
#include "njoy/dryad/TwoBodyDistributionData.hpp"
#include "njoy/dryad/UncorrelatedDistributionData.hpp"
#include "njoy/dryad/CoherentDistributionData.hpp"
#include "njoy/dryad/IncoherentDistributionData.hpp"
#include "tools/overload.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The data associated to a single reaction product
   */
  class ReactionProduct {

  public:

    /* type aliases */
    using Multiplicity = std::variant< int, TabulatedMultiplicity, PolynomialMultiplicity >;
    using DistributionData = std::variant< TwoBodyDistributionData,
                                           UncorrelatedDistributionData,
                                           CoherentDistributionData,
                                           IncoherentDistributionData >;

  private:

    /* fields */
    id::ParticleID product_;

    std::optional< id::ParticleID > parent_;
    std::size_t chain_index_;

    Multiplicity multiplicity_;
    std::optional< DistributionData > distribution_;

    std::optional< TabulatedAverageCosine > average_cosine_;
    std::optional< TabulatedAverageEnergy > average_energy_;

  public:

    /* constructor */
    #include "njoy/dryad/ReactionProduct/src/ctor.hpp"

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
     *  @param product   the reaction product identifier
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
     *  @param parent   the parent product identifier
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
     *  @param index   the chain index
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
     *  @param multiplicity   the multiplicity of the reaction product
     */
    void multiplicity( Multiplicity multiplicity ) {

      this->multiplicity_ = std::move( multiplicity );
    }

    /**
     *  @brief Return the average reaction product cosine
     */
    const std::optional< TabulatedAverageCosine >& averageCosine() const {

      return this->average_cosine_;
    }

    /**
     *  @brief Set the average reaction product cosine
     *
     *  @param averageCosine   the average reaction product cosine
     */
    void averageCosine( std::optional< TabulatedAverageCosine > averageCosine ) {

      this->average_cosine_ = std::move( averageCosine );
    }

    /**
     *  @brief Return the average reaction product energy
     */
    const std::optional< TabulatedAverageEnergy >& averageEnergy() const {

      return this->average_energy_;
    }

    /**
     *  @brief Set the average reaction product energy
     *
     *  @param averageEnergy   the average reaction product energy
     */
    void averageEnergy( std::optional< TabulatedAverageEnergy > averageEnergy ) {

      this->average_energy_ = std::move( averageEnergy );
    }

    /**
     *  @brief Return the reaction product distribution data
     */
    const std::optional< DistributionData >& distributionData() const {

      return this->distribution_;
    }

    /**
     *  @brief Return the reaction product distribution data
     */
    std::optional< DistributionData >& distributionData() {

      return this->distribution_;
    }

    /**
     *  @brief Set the reaction product distribution data
     *
     *  @param distribution   the reaction product distribution data
     */
    void distributionData( std::optional< DistributionData > distribution ) {

      this->distribution_ = std::move( distribution );
    }

    /**
     *  @brief Normalise the distribution data
     */
    void normalise() {

      if ( this->hasDistributionData() ) {

        std::visit( tools::overload{

                      [] ( CoherentDistributionData& ) {},
                      [] ( IncoherentDistributionData& ) {},
                      [] ( auto&& data ) { data.normalise(); }
                    },
                    this->distributionData().value() );
      }
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
     *  @brief Return whether or not the reaction product has distribution data
     */
    bool hasDistributionData() const {

      return this->distribution_.has_value();
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ReactionProduct& right ) const {

      return std::tie( this->productIdentifier(), this->parentIdentifier(),
                       this->chain_index_, this->multiplicity(),
                       this->distributionData(), this->averageCosine(),
                       this->averageEnergy() ) ==
             std::tie( right.productIdentifier(), right.parentIdentifier(),
                       right.chain_index_, right.multiplicity(),
                       right.distributionData(), right.averageCosine(),
                       right.averageEnergy() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ReactionProduct& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
