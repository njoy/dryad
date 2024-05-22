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

    double mass_difference_qvalue_;
    double reaction_qvalue_;

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
     *  @brief Return the mass difference Q value
     *
     *  The mass difference Q value is defined as the energy equivalence of the
     *  difference in the initial mass (the projectile and target mass) and the
     *  final mass (the residual nucleus mass and all reactor product masses).
     *  mass of the residual nucleus in the ground state and masses of all other
     *  reaction products. The masses used have to be the atomic mass values
     *  (not the nuclear masses).
     */
    double massDifferenceQValue() const noexcept {

      return this->mass_difference_qvalue_;
    }

    /**
     *  @brief Return the reaction Q value
     *
     *  The reaction Q value is defined as the mass difference Q value minus
     *  the difference in the excitation energy of the target and residual
     *  nucleus. When both the target and residual nucleus are in the ground
     *  state, the reaction Q value is equal to the mass difference Q value.
     */
    double reactionQValue() const noexcept {

      return this->reaction_qvalue_;
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
