#ifndef NJOY_DRYAD_REACTIONPRODUCT
#define NJOY_DRYAD_REACTIONPRODUCT

// system includes
#include <optional>
#include <variant>
#include <vector>

// other includes
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

    /* type aliases */
    using Multiplicity = std::variant< int, TabulatedMultiplicity >;

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
  };

} // dryad namespace
} // njoy namespace

#endif
