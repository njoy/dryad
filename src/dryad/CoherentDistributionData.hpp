#ifndef NJOY_DRYAD_COHERENTDISTRIBUTIONDATA
#define NJOY_DRYAD_COHERENTDISTRIBUTIONDATA

// system includes
#include <optional>

// other includes
#include "dryad/DistributionDataType.hpp"
#include "dryad/ReferenceFrame.hpp"
#include "dryad/TabulatedScatteringFunction.hpp"
#include "dryad/TabulatedFormFactor.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief The distribution data for coherent scattering in photoatomic interactions
   *
   *  This representation is only available for a photoatomic ProjectileTarget.
   *
   *  In this representation, a scattering function S(x,Z) and two optional form factor
   *  functions are defined which together with the Thompson cross section determine the
   *  double differential cross section. The optional form factors are the real and 
   *  complex part of the anomolous form factor. These are defined as optional because
   *  photoatomic MCNP data files produced in 2024 or earlier do not contain these form 
   *  factors even though the photoatomic ENDF evaluations define them.
   *
   *  This corresponds with the coherent scattering function data given in
   *  MF27 MT502 and the form factors in MF27 MT505 and MT506.
   */
  class CoherentDistributionData {

    /* fields */
    ReferenceFrame frame_;
    TabulatedScatteringFunction scattering_;
    std::optional< TabulatedFormFactor > real_;
    std::optional< TabulatedFormFactor > imaginary_;

  public:

    /* constructor */

    #include "dryad/CoherentDistributionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() noexcept {

      return DistributionDataType::Coherent;
    }

    /**
     *  @brief Return the reference frame
     */
    const ReferenceFrame& frame() const noexcept {

      return this->frame_;
    }

    /**
     *  @brief Return whether or not the coherent distribution data has an anomolous
     *         form factor
     */
    bool hasAnomolousFormFactor() const noexcept {

      return this->real_.has_value() || this->imaginary_.has_value();
    }

    /**
     *  @brief Return the scattering function
     */
    const TabulatedScatteringFunction& scatteringFunction() const noexcept {

      return this->scattering_;
    }

    /**
     *  @brief Return the real part of the anomolous form factor
     */
    const std::optional< TabulatedFormFactor >& realAnomolousFormFactor() const noexcept {

      return this->real_;
    }

    /**
     *  @brief Return the imaginary part of the anomolous form factor
     */
    const std::optional< TabulatedFormFactor >& imaginaryAnomolousFormFactor() const noexcept {

      return this->imaginary_;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
