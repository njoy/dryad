#ifndef NJOY_DRYAD_COHERENTDISTRIBUTIONDATA
#define NJOY_DRYAD_COHERENTDISTRIBUTIONDATA

// system includes
#include <optional>

// other includes
#include "njoy/dryad/DistributionDataType.hpp"
#include "njoy/dryad/ReferenceFrame.hpp"
#include "njoy/dryad/TabulatedScatteringFunction.hpp"
#include "njoy/dryad/TabulatedFormFactor.hpp"

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
   *  complex part of the anomalous form factor. These are defined as optional because
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

    #include "njoy/dryad/CoherentDistributionData/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the distribution data type
     */
    static constexpr DistributionDataType type() {

      return DistributionDataType::Coherent;
    }

    /**
     *  @brief Return the reference frame
     */
    const ReferenceFrame& frame() const {

      return this->frame_;
    }

    /**
     *  @brief Set the reference frame
     *
     *  @param frame   the reference frame of the distribution data
     */
    void frame( ReferenceFrame frame ) {

      this->frame_ = std::move( frame );
    }

    /**
     *  @brief Return whether or not the coherent distribution data has an Anomalous
     *         form factor
     */
    bool hasAnomalousFormFactor() const {

      return this->real_.has_value() || this->imaginary_.has_value();
    }

    /**
     *  @brief Return the scattering function
     */
    const TabulatedScatteringFunction& scatteringFunction() const {

      return this->scattering_;
    }

    /**
     *  @brief Set the scattering function
     *
     *  @param scattering   the scattering function
     */
    void scatteringFunction( TabulatedScatteringFunction scattering ) {

      this->scattering_ = scattering;
    }

    /**
     *  @brief Return the real part of the Anomalous form factor
     */
    const std::optional< TabulatedFormFactor >& realAnomalousFormFactor() const {

      return this->real_;
    }

    /**
     *  @brief Set the real part of the Anomalous form factor
     *
     *  @param real   the real part of the anamolous form factor
     */
    void realAnomalousFormFactor( std::optional< TabulatedFormFactor > real ) {

      this->real_ = real;
    }

    /**
     *  @brief Return the imaginary part of the Anomalous form factor
     */
    const std::optional< TabulatedFormFactor >& imaginaryAnomalousFormFactor() const {

      return this->imaginary_;
    }

    /**
     *  @brief Set the imaginary part of the Anomalous form factor
     *
     *  @param real   the imaginary part of the anamolous form factor
     */
    void imaginaryAnomalousFormFactor( std::optional< TabulatedFormFactor > imaginary ) {

      this->imaginary_ = imaginary;
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const CoherentDistributionData& right ) const {

      return this->frame() == right.frame() &&
             this->scatteringFunction() == right.scatteringFunction() &&
             this->realAnomalousFormFactor() == right.realAnomalousFormFactor()&&
             this->imaginaryAnomalousFormFactor() == right.imaginaryAnomalousFormFactor();
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const CoherentDistributionData& right ) const {

      return ! this->operator==( right );
    }
  };

} // dryad namespace
} // njoy namespace

#endif
