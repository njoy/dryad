#ifndef NJOY_DRYAD_REACTION
#define NJOY_DRYAD_REACTION

// system includes
#include <optional>
#include <variant>
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/ReactionID.hpp"
#include "dryad/TabulatedCrossSection.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The data associated to a single reaction
   */
  class Reaction {

    /* fields */
    ReactionID id_;

    double mass_difference_qvalue_;
    double reaction_qvalue_;

    TabulatedCrossSection xs_;
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
     *  @brief Return the mass difference Q value
     *
     *  The mass difference Q value is defined as the energy equivalence of the
     *  difference in the initial atomic mass (the projectile and target mass)
     *  and the final atomic mass (the residual mass and all reactor product
     *  masses). All particles involved are supposed to be in the ground state.
     */
    const double& massDifferenceQValue() const noexcept {

      return this->mass_difference_qvalue_;
    }

    /**
     *  @brief Return the reaction Q value
     */
    double reactionQValue() const noexcept {

      return this->reaction_qvalue_;
    }

    /**
     *  @brief Return the cross section
     */
    const TabulatedCrossSection& crossSection() const noexcept {

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

      TabulatedCrossSection xs = this->crossSection().linearise( tolerance );

      return Reaction( this->identifier(), this->massDifferenceQValue(),
                       this->reactionQValue(), std::move( xs ) );
    }

    /**
     *  @brief Linearise the reaction data inplace
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    void lineariseInplace( ToleranceConvergence tolerance = {} ) noexcept {

      this->xs_ = this->xs_.linearise( tolerance );
      this->linearised_ = true;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
