#ifndef NJOY_DRYAD_REACTIONPRODUCT
#define NJOY_DRYAD_REACTIONPRODUCT

// system includes
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "dryad/type-aliases.hpp"
#include "dryad/ParticleID.hpp"
#include "dryad/TabulatedMultiplicity.hpp"

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

  private:

    /* fields */
    ParticleID id_;

    Multiplicity multiplicity_;
    bool linearised_;

  public:

    /* constructor */
    #include "dryad/ReactionProduct/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the particle identifier for the reaction product
     */
    const ParticleID& identifier() const noexcept {

      return this->id_;
    }

    /**
     *  @brief Return the reaction product multiplicity
     */
    const Multiplicity& multiplicity() const noexcept {

      return this->multiplicity_;
    }

    /**
     *  @brief Return whether or not the reaction product data is linearised
     */
    bool isLinearised() const noexcept {

      return this->linearised_;
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

      Multiplicity multiplicity = std::visit( linearise, this->multiplicity() );

      return ReactionProduct( this->identifier(), std::move( multiplicity ) );
    }

    /**
     *  @brief Linearise the reaction data inplace
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
