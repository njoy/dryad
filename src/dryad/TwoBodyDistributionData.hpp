#ifndef NJOY_DRYAD_TWOBODYDISTRIBUTIONDATA
#define NJOY_DRYAD_TWOBODYDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "dryad/DistributionDataType.hpp"
#include "dryad/ReferenceFrame.hpp"
#include "dryad/IsotropicAngularDistributions.hpp"
#include "dryad/LegendreAngularDistributions.hpp"
#include "dryad/TabulatedAngularDistributions.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The energy-angle distribution data for a two-body output channel
   *
   *  In this representation, only the angular distributions as a function of
   *  incident energy is given and the outgoing particle's energy can be derived
   *  through kinematics.
   *
   *  For incident neutron data, this corresponds with elastic and inelastic
   *  scattering data given in MF4 (none of these will have corresponding MF5
   *  data). In the more general MF6 representation, this corresponds with
   *  LAW = 2 (discrete two-body scattering). This is also the representation for
   *  elastic scattering data in MF26 for electro-atomic interactions.
   */
  class TwoBodyDistributionData {

  public:

    /* type aliases */
    using AngularDistributions = std::variant< IsotropicAngularDistributions,
                                               LegendreAngularDistributions,
                                               TabulatedAngularDistributions >;

  private:

    /* fields */
    ReferenceFrame frame_;
    AngularDistributions angle_;

  public:

    /* constructor */

    #include "dryad/TwoBodyDistributionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() noexcept {

      return DistributionDataType::TwoBody;
    }

    /**
     *  @brief Return the reference frame
     */
    const ReferenceFrame& frame() const noexcept {

      return this->frame_;
    }

    /**
     *  @brief Return the angular distributions
     */
    const AngularDistributions& angle() const noexcept {

      return this->angle_;
    }

    //! @todo implement kinematics formulas to retrieve outgoing energy
    //!       from an incident energy and outgoing cosine

  };

} // dryad namespace
} // njoy namespace

#endif
