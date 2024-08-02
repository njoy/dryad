#ifndef NJOY_DRYAD_UNCORRELATEDDISTRIBUTIONDATA
#define NJOY_DRYAD_UNCORRELATEDDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "dryad/DistributionDataType.hpp"
#include "dryad/ReferenceFrame.hpp"
#include "dryad/IsotropicAngularDistributions.hpp"
#include "dryad/LegendreAngularDistributions.hpp"
#include "dryad/TabulatedAngularDistributions.hpp"
#include "dryad/MultiEnergyDistributions.hpp"
#include "dryad/TabulatedEnergyDistributions.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief Uncorrelated energy and angle distribution data for a reaction product
   *
   *  In this representation, there is no correlation given between the outgoing
   *  angle and energy of the reaction product. As a result, the angular and energy
   *  distributions of the reaction product only depend on the incident energy of the
   *  projectile.
   *
   *  For incident neutron data, this is used for reactions that have both MF4 and MF5
   *  data. For reaction products given in MF6, this corresponds to LAW = 1 (continuum
   *  energy-angle distributions) in which the angular dependence is fully isotropic.
   *  This is also the representation for Brehmstrahlung and excitation data in MF26
   *  for electro-atomic interactions.
   */
  class UncorrelatedDistributionData {

  public:

    /* type aliases */
    using AngularDistributions = std::variant< IsotropicAngularDistributions,
                                               LegendreAngularDistributions,
                                               TabulatedAngularDistributions >;
    using EnergyDistributions = std::variant< MultiEnergyDistributions,
                                              TabulatedEnergyDistributions >;

  private:

    /* fields */
    ReferenceFrame frame_;
    AngularDistributions angle_;
    EnergyDistributions energy_;

  public:

    /* constructor */

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() noexcept {

      return DistributionDataType::Uncorrelated;
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

    /**
     *  @brief Return the energy distributions
     */
    const EnergyDistributions& energy() const noexcept {

      return this->energy_;
    }

  };

} // dryad namespace
} // njoy namespace

#endif
