#ifndef NJOY_DRYAD_THERMAL_SCATTERINGKERNEL
#define NJOY_DRYAD_THERMAL_SCATTERINGKERNEL

// system includes
#include <tuple>

// other includes
#include "njoy/dryad/thermal/ShortCollisionTimeScatteringKernel.hpp"
#include "njoy/dryad/thermal/TabulatedScatteringKernel.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief An S(a,b) scattering kernel for incoherent inelastic thermal scattering
   */
  class ScatteringKernel {

    /* fields */

    ShortCollisionTimeScatteringKernel sct_;
    TabulatedScatteringKernel sab_;

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ScatteringKernel() = default;

    ScatteringKernel( const ScatteringKernel& ) = default;
    ScatteringKernel( ScatteringKernel&& ) = default;

    ScatteringKernel& operator=( const ScatteringKernel& ) = default;
    ScatteringKernel& operator=( ScatteringKernel&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] moderatorTemperature   the moderator temperature
     *  @param[in] effectiveTemperature   the effective temperature used in the SCT approximation
     *  @param[in] table                  the tabulated S(a,b) scattering kernel
     */
    ScatteringKernel( double moderatorTemperature, double effectiveTemperature,
                      TabulatedScatteringKernel table ) :
        sct_( moderatorTemperature, effectiveTemperature ),
        sab_( std::move( table ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] moderatorTemperature   the moderator temperature
     *  @param[in] effectiveTemperature   the effective temperature used in the SCT approximation
     *  @param[in] energyTransfers        the energy transfer values
     *  @param[in] functions              the associated scattering functions
     *  @param[in] boundaries             the boundaries of the interpolation regions
     *  @param[in] interpolants           the interpolation types of the interpolation regions
     */
    ScatteringKernel( double moderatorTemperature,
                      double effectiveTemperature,
                      std::vector< double > energyTransfers,
                      std::vector< TabulatedScatteringKernelFunction > functions,
                      std::vector< std::size_t > boundaries,
                      std::vector< InterpolationType > interpolants ) :
        ScatteringKernel(
            moderatorTemperature, effectiveTemperature,
            TabulatedScatteringKernel( std::move( energyTransfers ), std::move( functions ),
                                       std::move( boundaries ), std::move( interpolants ) ) ) {}

    /**
     *  @brief Constructor using a single interpolation zone
     *
     *  @param[in] moderatorTemperature   the moderator temperature
     *  @param[in] effectiveTemperature   the effective temperature used in the SCT approximation
     *  @param[in] energyTransfers        the energy transfer values
     *  @param[in] functions              the associated functions
     *  @param[in] interpolant            the interpolation type of the data (default lin-lin)
     */
    ScatteringKernel( double moderatorTemperature,
                      double effectiveTemperature,
                      std::vector< double > energyTransfers,
                      std::vector< TabulatedScatteringKernelFunction > functions,
                      InterpolationType interpolant = InterpolationType::LinearLinear ) :
        ScatteringKernel(
            moderatorTemperature, effectiveTemperature,
            TabulatedScatteringKernel( std::move( energyTransfers ), std::move( functions ),
                                       interpolant ) ) {}

    /* methods */

    /**
     *  @brief Return the moderator temperature
     */
    double moderatorTemperature() const {

      return this->shortCollisionTime().moderatorTemperature();
    }

    /**
     *  @brief Return the effective temperature used for the short collision time approximation
     */
    double effectiveTemperature() const {

      return this->shortCollisionTime().effectiveTemperature();
    }

    /**
     *  @brief Return the short collision time approximation
     */
    const ShortCollisionTimeScatteringKernel& shortCollisionTime() const {

      return this->sct_;
    }

    /**
     *  @brief Return the short collision time approximation
     */
    ShortCollisionTimeScatteringKernel& shortCollisionTime() {

      return this->sct_;
    }

    /**
     *  @brief Return the tabulated scattering kernel
     */
    const TabulatedScatteringKernel& tabulatedScatteringKernel() const {

      return this->sab_;
    }

    /**
     *  @brief Return the short collision time approximation
     */
    TabulatedScatteringKernel& tabulatedScatteringKernel() {

      return this->sab_;
    }

    /**
     *  @brief Return whether or not the scattering kernel is symmetric along the
     *         energy transfer axis
     */
    bool isEnergyTransferSymmetric() const {

      return ! ( this->tabulatedScatteringKernel().energyTransfers().front() < 0. );
    }

    /**
     *  @brief Evaluate the scattering kernel for a given momentum and energy transfer value
     *
     *  @param[in] a   the momentum transfer value
     *  @param[in] b   the energy transfer value
     */
    double operator()( double a, double b ) const {

      if ( this->isEnergyTransferSymmetric() && b < 0. ) {

        b = -b;
      }

      if ( a < this->tabulatedScatteringKernel().lowerMomentumTransferLimit() ) {

        a = this->tabulatedScatteringKernel().lowerMomentumTransferLimit();
      }

      if ( b < this->tabulatedScatteringKernel().lowerEnergyTransferLimit() ||
           b > this->tabulatedScatteringKernel().upperEnergyTransferLimit() ||
           a > this->tabulatedScatteringKernel().upperMomentumTransferLimit() ) {

        return this->shortCollisionTime()( a, b );
      }
      else {

        return this->tabulatedScatteringKernel()( a, b );
      }
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ScatteringKernel& right ) const {

      return std::tie( this->shortCollisionTime(), this->tabulatedScatteringKernel()  ) ==
             std::tie( right.shortCollisionTime(), right.tabulatedScatteringKernel() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ScatteringKernel& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
