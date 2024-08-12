#ifndef NJOY_DRYAD_INCOHERENTDISTRIBUTIONDATA
#define NJOY_DRYAD_INCOHERENTDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "dryad/DistributionDataType.hpp"
#include "dryad/ReferenceFrame.hpp"
#include "dryad/TabulatedScatteringFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The distribution data for incoherent scattering in photoatomic interactions
   *
   *  This representation is only available for a photoatomic ProjectileTarget.
   *
   *  In this representation, a scattering function S(x,Z) is defined that
   *  together with the Klein-Nishina cross section determines the double
   *  differential cross section.
   *
   *  This corresponds with the incoherent scattering function data given in
   *  MF27 MT504.
   */
  class IncoherentDistributionData {

    /* fields */
    ReferenceFrame frame_;
    TabulatedScatteringFunction scattering_;

  public:

    /* constructor */

    #include "dryad/IncoherentDistributionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() noexcept {

      return DistributionDataType::Incoherent;
    }

    /**
     *  @brief Return the reference frame
     */
    const ReferenceFrame& frame() const noexcept {

      return this->frame_;
    }

    /**
     *  @brief Return the scattering function
     */
    const TabulatedScatteringFunction& scatteringFunction() const noexcept {

      return this->scattering_;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
