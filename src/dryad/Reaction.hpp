#ifndef NJOY_DRYAD_REACTION
#define NJOY_DRYAD_REACTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/ReactionID.hpp"
#include "dryad/CrossSection.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The data associated to a single reaction
   */
  class Reaction {

    /* fields */
    ReactionID id_;
    CrossSection xs_;
    bool linearised_;

  public:

    /* constructor */
    #include "dryad/Reaction/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the reaction identifier
     */
    const ReactionID& identifier() const noexcept {

      return this->id_;
    }

    /**
     *  @brief Return the cross section
     */
    const CrossSection& crossSection() const noexcept {

      return this->xs_;
    }

    /**
     *  @brief Return whether or not the reaction data is linearised
     */
    bool isLinearised() const noexcept {

      return this->linearised_;
    }

    /**
     *  @brief Linearise the reaction data and return a new reaction object
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    Reaction linearise( ToleranceConvergence tolerance = {} ) const noexcept {

      CrossSection xs = this->crossSection().linearise( tolerance );

      return Reaction( this->identifier(), std::move( xs ) );
    }

    /**
     *  @brief Linearise the reaction data inplace
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    void lineariseInplace( ToleranceConvergence convergence = {} ) noexcept {

      this->xs_ = this->xs_.linearise( convergence );
      this->linearised_ = true;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
