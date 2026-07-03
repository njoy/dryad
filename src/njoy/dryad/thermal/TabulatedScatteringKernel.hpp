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

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedScatteringKernel() = default;

    TabulatedScatteringKernel( const TabulatedScatteringKernel& ) = default;
    TabulatedScatteringKernel( TabulatedScatteringKernel&& ) = default;

    TabulatedScatteringKernel& operator=( const TabulatedScatteringKernel& ) = default;
    TabulatedScatteringKernel& operator=( TabulatedScatteringKernel&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] temperature            the moderator temperature
     *  @param[in] energyTransfers        the energy transfer values
     *  @param[in] functions              the associated scattering functions
     *  @param[in] boundaries             the boundaries of the interpolation regions
     *  @param[in] interpolants           the interpolation types of the interpolation regions
     */
    TabulatedScatteringKernel( double temperature,
                               std::vector< double > energyTransfers,
                               std::vector< TabulatedScatteringKernelFunction > functions,
                               std::vector< std::size_t > boundaries,
                               std::vector< InterpolationType > interpolants ) :
      Parent( std::move( energyTransfers ), std::move( functions ),
              std::move( boundaries ), std::move( interpolants ) ),
      moderator_temperature_( temperature ) {}

    /**
     *  @brief Constructor for scattering functions using a single interpolation zone
     *
     *  @param[in] temperature            the moderator temperature
     *  @param[in] energyTransfers        the energy transfer values
     *  @param[in] functions              the associated functions
     *  @param[in] interpolant            the interpolation type of the data (default lin-lin)
     */
    TabulatedScatteringKernel( double temperature,
                               std::vector< double > energyTransfers,
                               std::vector< TabulatedScatteringKernelFunction > functions,
                               InterpolationType interpolant = InterpolationType::LinearLinear ) :
      Parent( std::move( energyTransfers ), std::move( functions ), interpolant ),
      moderator_temperature_( temperature ) {}

    /* methods */

    /**
     *  @brief Return the moderator temperature
     */
    double moderatorTemperature() const {

      return this->moderator_temperature_;
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
                                        this->energyTransfers(), std::move( functions ),
                                        this->boundaries(), this->interpolants() );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedScatteringKernel& right ) const {

      return this->moderatorTemperature() == right.moderatorTemperature() &&
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
