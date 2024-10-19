#ifndef NJOY_DRYAD_REACTIONPRODUCT
#define NJOY_DRYAD_REACTIONPRODUCT

// system includes
#include <optional>
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "dryad/type-aliases.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/TabulatedMultiplicity.hpp"
#include "dryad/TwoBodyDistributionData.hpp"
#include "dryad/UncorrelatedDistributionData.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The data associated to a single reaction product
   */
  class ReactionProduct {

  public:

    /* type aliases */
    using Multiplicity = std::variant< int, TabulatedMultiplicity >;
    using DistributionData = std::variant< TwoBodyDistributionData,
                                           UncorrelatedDistributionData >;

  private:

    /* fields */
    id::ParticleID id_;

    Multiplicity multiplicity_;
    std::optional< DistributionData > distribution_;
    bool linearised_;

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
     *  @brief Return the reaction product multiplicity
     */
    const Multiplicity& multiplicity() const noexcept {

      return this->multiplicity_;
    }

    /**
     *  @brief Return the reaction product distribution data
     */
    const std::optional< DistributionData >& distributionData() const noexcept {

      return this->distribution_;
    }

    /**
     *  @brief Return whether or not the reaction product data is linearised
     */
    bool isLinearised() const noexcept {

      return this->linearised_;
    }

    /**
     *  @brief Return whether or not the reaction product has distribution data
     */
    bool hasDistributionData() const noexcept {

      return this->distribution_.has_value();
    }

    /**
     *  @brief Linearise the reaction product data and return a new reaction product
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    ReactionProduct linearise( ToleranceConvergence tolerance = {} ) const noexcept {

      auto linearise = tools::overload{

        [] ( int multiplicity ) -> Multiplicity
           { return Multiplicity( multiplicity ); },
        [&tolerance] ( const TabulatedMultiplicity& multiplicity ) -> Multiplicity
                     { return Multiplicity( multiplicity.linearise( tolerance ) ); }
      };

      id::ParticleID id = this->identifier();
      Multiplicity multiplicity = std::visit( linearise, this->multiplicity() );
      std::optional< DistributionData > distribution = this->distributionData();

      return ReactionProduct( std::move( id ), std::move( multiplicity ),
                              std::move( distribution ), true );
    }

    /**
     *  @brief Linearise the reaction product data inplace
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    void lineariseInplace( ToleranceConvergence tolerance = {} ) noexcept {

      auto linearise = tools::overload{

        [] ( int multiplicity ) -> Multiplicity
           { return Multiplicity( multiplicity ); },
        [&tolerance] ( const TabulatedMultiplicity& multiplicity ) -> Multiplicity
                     { return Multiplicity( multiplicity.linearise( tolerance ) ); }
      };

      this->multiplicity_ = std::visit( linearise, this->multiplicity() );
      this->linearised_ = true;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
