#ifndef NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGKERNEL
#define NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGKERNEL

// system includes

// other includes
#include "scion/math/InterpolationTableFunction.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/thermal/TabulatedScatteringKernelFunction.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief An S(a,b) scattering kernel using tabulated scattering kernel functions
   */
  class TabulatedScatteringKernel :
      protected scion::math::InterpolationTableFunction< double, TabulatedScatteringKernelFunction > {

    /* type aliases */
    using Parent = scion::math::InterpolationTableFunction< double, TabulatedScatteringKernelFunction >;

    /* fields */

    double moderator_temperature_;
    double effective_temperature_;

  public:

    /* constructor */

    #include "njoy/dryad/thermal/TabulatedScatteringKernel/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the moderator temperature
     */
    double moderatorTemperature() const {

      return this->moderator_temperature_;
    }

    /**
     *  @brief Return the effective temperature used for the short collision time approximation
     */
    double effectiveTemperature() const {

      return this->effective_temperature_;
    }

    /**
     *  @brief Return the energy transfer values
     */
    const std::vector< double >& energyTransfers() const {

      return this->x();
    }

    /**
     *  @brief Return the energy transfer values
     */
    std::vector< double >& energyTransfers() {

      return this->x();
    }

    /**
     *  @brief Return the associated scattering functions
     */
    const std::vector< TabulatedScatteringKernelFunction >& functions() const {

      return this->f();
    }

    /**
     *  @brief Return the associated distributions
     */
    std::vector< TabulatedScatteringKernelFunction >& functions() {

      return this->f();
    }

    using Parent::boundaries;
    using Parent::interpolants;
    using Parent::numberPoints;
    using Parent::numberRegions;
    using Parent::operator();

    /**
     *  @brief Return linearised scattering functions
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedScatteringKernel linearise( double tolerance = constants::linearisation::tolerance ) const {

      std::vector< TabulatedScatteringKernelFunction > functions;
      functions.reserve( this->numberPoints() );
      std::transform( this->functions().begin(), this->functions().end(),
                      std::back_inserter( functions ),
                      [tolerance]
                        ( auto&& function )
                        { return function.linearise( std::move( tolerance ) ); } );
      return TabulatedScatteringKernel( this->moderatorTemperature(),
                                        this->effectiveTemperature(),
                                        this->energyTransfers(), std::move( functions ),
                                        this->boundaries(), this->interpolants() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedScatteringKernel& right ) const {

      return std::tie( this->moderator_temperature_, this->effective_temperature_ ) ==
             std::tie( right.moderator_temperature_, right.effective_temperature_ ) &&
             Parent::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedScatteringKernel& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
