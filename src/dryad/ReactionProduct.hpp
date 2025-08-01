#ifndef NJOY_DRYAD_REACTIONPRODUCT
#define NJOY_DRYAD_REACTIONPRODUCT

// system includes
#include <optional>
#include <variant>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/PolynomialMultiplicity.hpp"
#include "dryad/TabulatedMultiplicity.hpp"
#include "dryad/TabulatedAverageEnergy.hpp"
#include "dryad/TwoBodyDistributionData.hpp"
#include "dryad/UncorrelatedDistributionData.hpp"
#include "dryad/CoherentDistributionData.hpp"
#include "dryad/IncoherentDistributionData.hpp"

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
    id::ParticleID id_;

    Multiplicity multiplicity_;
    std::optional< DistributionData > distribution_;
    std::optional< TabulatedAverageEnergy > average_energy_;

  public:

    /* constructor */
    #include "dryad/ReactionProduct/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the particle identifier for the reaction product
     */
    const id::ParticleID& identifier() const noexcept {

      return this->id_;
    }

    /**
     *  @brief Set the particle identifier for the reaction product
     *
     *  @param id.  the reaction product identifier
     */
    void identifier( id::ParticleID id ) noexcept {

      this->id_ = std::move( id );
    }

    /**
     *  @brief Return the reaction product multiplicity
     */
    const Multiplicity& multiplicity() const noexcept {

      return this->multiplicity_;
    }

    /**
     *  @brief Set the reaction product multiplicity
     *
     *  @param multiplicity   the multiplicity of the reaction product
     */
    void multiplicity( Multiplicity multiplicity ) noexcept {

      this->multiplicity_ = std::move( multiplicity );
    }

    /**
     *  @brief Return the average reaction product energy
     */
    const std::optional< TabulatedAverageEnergy >& averageEnergy() const noexcept {

      return this->average_energy_;
    }

    /**
     *  @brief Set the average reaction product energy
     *
     *  @param averageEnergy   the average reaction product energy
     */
    void averageEnergy( std::optional< TabulatedAverageEnergy > averageEnergy ) noexcept {

      this->average_energy_ = std::move( averageEnergy );
    }

    /**
     *  @brief Return the reaction product distribution data
     */
    const std::optional< DistributionData >& distributionData() const noexcept {

      return this->distribution_;
    }

    /**
     *  @brief Return the reaction product distribution data
     */
    std::optional< DistributionData >& distributionData() noexcept {

      return this->distribution_;
    }

    /**
     *  @brief Set the reaction product distribution data
     *
     *  @param distribution   the reaction product distribution data
     */
    void distributionData( std::optional< DistributionData > distribution ) noexcept {

      this->distribution_ = std::move( distribution );
    }

    /**
     *  @brief Return whether or not the reaction product has average reaction
     *         product energy data
     */
    bool hasAverageEnergy() const noexcept {

      return this->average_energy_.has_value();
    }

    /**
     *  @brief Return whether or not the reaction product has distribution data
     */
    bool hasDistributionData() const noexcept {

      return this->distribution_.has_value();
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ReactionProduct& right ) const noexcept {

      return this->identifier() == right.identifier() &&
             this->multiplicity() == right.multiplicity() &&
             this->averageEnergy() == right.averageEnergy() &&
             this->distributionData() == right.distributionData();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ReactionProduct& right ) const noexcept {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
