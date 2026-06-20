#ifndef NJOY_DRYAD_ISOTROPICANGULARDISTRIBUTIONFUNCTION
#define NJOY_DRYAD_ISOTROPICANGULARDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "scion/math/OneDimensionalFunctionBase.hpp"
#include "njoy/dryad/LegendreAngularDistributionFunction.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An isotropic angular distribution function
   *
   *  In this distribution, all cosines are equally probable. The
   *  equivalent tabulated distribution is 0.5 on the -1,1 domain and
   *  the equivalent Legendre distribution uses 0.5 as the P0 coefficient.
   */
  class IsotropicAngularDistributionFunction :
      protected scion::math::OneDimensionalFunctionBase<
          IsotropicAngularDistributionFunction, double, double > {

    /* friend declarations */

    friend class scion::math::OneDimensionalFunctionBase<
        IsotropicAngularDistributionFunction, double, double >;

    /* type aliases */

    using Parent = scion::math::OneDimensionalFunctionBase<
        IsotropicAngularDistributionFunction, double, double >;

    /**
     *  @brief Evaluate the function
     *
     *  @param[in] cosine   the cosine value
     */
    double evaluate( double cosine ) const {

      return this->isInside( cosine ) ? 0.5 : 0.0;
    }

  public:

    /* type aliases */

    using Parent::XType;
    using Parent::YType;

    /* constructor */

    /**
     *  @brief Default constructor
     */
    IsotropicAngularDistributionFunction() :
      Parent( scion::math::IntervalDomain< double >( -1.0, 1.0 ) ) {}

    IsotropicAngularDistributionFunction( const IsotropicAngularDistributionFunction& ) = default;
    IsotropicAngularDistributionFunction( IsotropicAngularDistributionFunction&& ) = default;

    IsotropicAngularDistributionFunction& operator=( const IsotropicAngularDistributionFunction& ) = default;
    IsotropicAngularDistributionFunction& operator=( IsotropicAngularDistributionFunction&& ) = default;

    /* methods */

    /**
     *  @brief Return the lower cosine limit
     */
    static constexpr double lowerCosineLimit() { return -1.0; }

    /**
     *  @brief Return the upper cosine limit
     */
    static constexpr double upperCosineLimit() { return 1.0; }

    using Parent::operator();

    /**
     *  @brief Return the integral of the distribution function over its domain
     */
    constexpr double integral() const {

      return 1.0;
    }

    /**
     *  @brief Return the mean value of the distribution function over its domain
     */
    constexpr double mean() const {

      return 0.0;
    }

    /**
     *  @brief Normalise the distribution
     */
    void normalise() {

      // isotropic distributions are always normalized
    }

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     *  @param[in] normalise   option to indicate whether or not to normalise
     *                         all probability data (default: no normalisation)
     */
    TabulatedAngularDistributionFunction linearise( double = constants::linearisation::tolerance,
                                                    bool = false ) const {

      return this->toTabulatedDistribution();
    }

    /**
     *  @brief Convert to the equivalent Legendre distribution
     */
    LegendreAngularDistributionFunction toLegendreDistribution() const {

      return LegendreAngularDistributionFunction( { 0.5 } );
    }

    /**
     *  @brief Convert to the equivalent tabulated distribution
     */
    TabulatedAngularDistributionFunction toTabulatedDistribution() const {

      return TabulatedAngularDistributionFunction( { -1., 1. }, { 0.5, 0.5 } );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    constexpr bool operator==( const IsotropicAngularDistributionFunction& ) const {

      return true;
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    constexpr bool operator!=( const IsotropicAngularDistributionFunction& right ) const {

      return false;
    }
  };

} // dryad namespace
} // njoy namespace

#endif
