#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTIONFUNCTION
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/LegendreSeries.hpp"
#include "dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  // forward declaration LegendreAngularDistribution
  class LegendreAngularDistribution;

  /**
   *  @class
   *  @brief An angular distribution function using a Legendre expansion defined
   *         by a set of coefficients
   *
   *  Note: ENDF and GNDS Legendre expansions use Legendre moments for the angular
   *  distributions in MF4 and MF6 LAW=1 & LAW=2 so an additional ( 2 * n + 1 ) / 2
   *  factor for the coefficient of order n needs to be applied to obtain the series
   *  coefficients. This distribution function assumes those factors are already
   *  integrated in the coefficients.
   *
   *  A distribution function does not have to normalised as this class can be used
   *  to represent both a pdf and cdf. Proper normalisation should be applied after
   *  construction using the normalise() function if required.
   */
  class LegendreAngularDistributionFunction :
      protected scion::math::LegendreSeries< double, double > {

    /* friend declarations */

    // LegendreAngularDistribution needs access to protected functions
    friend LegendreAngularDistribution;

  protected:

    /**
     *  @brief Calculate the roots of the function so that f(x) = a
     *
     *  @param[in] a   the value of a (default is zero)
     */
    std::vector< double > roots( double a = 0. ) const {

      std::vector< double > roots = LegendreSeries::roots( a );
      roots.erase( roots.begin(), std::lower_bound( roots.begin(), roots.end(), -1. ) );
      roots.erase( std::upper_bound( roots.begin(), roots.end(), +1. ), roots.end() );
      return roots;
    }

    /**
     *  @brief Return the derivative
     */
    LegendreAngularDistributionFunction derivative() const {

      return LegendreSeries::derivative();
    }

    /**
     *  @brief Return the primitive (or antiderivative)
     *
     *  @param[in] left    the left bound of the integral (default = 0)
     */
    LegendreAngularDistributionFunction primitive( double left = 0. ) const {

      return LegendreSeries::primitive( left );
    }

  public:

    /* type aliases */
    using LegendreSeries::XType;
    using LegendreSeries::YType;

    /* constructor */

    #include "dryad/LegendreAngularDistributionFunction/src/ctor.hpp"

    /* methods */

    using LegendreSeries::coefficients;

    /**
     *  @brief Return the lower cosine limit
     */
    static constexpr double lowerCosineLimit() { return -1.0; }

    /**
     *  @brief Return the upper cosine limit
     */
    static constexpr double upperCosineLimit() { return 1.0; }

    using LegendreSeries::operator();
    using LegendreSeries::order;

    using LegendreSeries::integral;
    using LegendreSeries::mean;

    /**
     *  @brief Normalise the distribution function
     */
    void normalise() {

      this->operator/=( this->integral() );
    }

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedAngularDistributionFunction linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedAngularDistributionFunction( LegendreSeries::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistributionFunction& operator+=( double right ) {

      LegendreSeries::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistributionFunction& operator-=( double right ) {

      LegendreSeries::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistributionFunction& operator*=( double right ) {

      LegendreSeries::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistributionFunction& operator/=( double right ) {

      LegendreSeries::operator/=( right );
      return *this;
    }

    /**
     *  @brief LegendreAngularDistributionFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistributionFunction operator+( double right ) const {

      return LegendreSeries::operator+( right );
    }

    /**
     *  @brief LegendreAngularDistributionFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistributionFunction operator-( double right ) const {

      return LegendreSeries::operator-( right );
    }

    /**
     *  @brief LegendreAngularDistributionFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistributionFunction operator*( double right ) const {

      return LegendreSeries::operator*( right );
    }

    /**
     *  @brief LegendreAngularDistributionFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistributionFunction operator/( double right ) const {

      return LegendreSeries::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    LegendreAngularDistributionFunction operator-() const {

      return LegendreSeries::operator-();
    }

    /**
     *  @brief Inplace LegendreAngularDistributionFunction addition
     *
     *  @param[in] right    the table
     */
    LegendreAngularDistributionFunction&
    operator+=( const LegendreAngularDistributionFunction& right ) {

      LegendreSeries::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace LegendreAngularDistributionFunction subtraction
     *
     *  @param[in] right    the table
     */
    LegendreAngularDistributionFunction&
    operator-=( const LegendreAngularDistributionFunction& right ) {

      LegendreSeries::operator-=( right );
      return *this;
    }

    /**
     *  @brief LegendreAngularDistributionFunction addition
     *
     *  @param[in] right    the table
     */
    LegendreAngularDistributionFunction
    operator+( const LegendreAngularDistributionFunction& right ) const {

      return LegendreSeries::operator+( right );
    }

    /**
     *  @brief LegendreAngularDistributionFunction subtraction
     *
     *  @param[in] right    the table
     */
    LegendreAngularDistributionFunction
    operator-( const LegendreAngularDistributionFunction& right ) const {

      return LegendreSeries::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const LegendreAngularDistributionFunction& right ) const {

      return LegendreSeries::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const LegendreAngularDistributionFunction& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and LegendreAngularDistributionFunction addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline LegendreAngularDistributionFunction
  operator+( double left, const LegendreAngularDistributionFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and LegendreAngularDistributionFunction subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline LegendreAngularDistributionFunction
  operator-( double left, const LegendreAngularDistributionFunction& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and LegendreAngularDistributionFunction multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline LegendreAngularDistributionFunction
  operator*( double left, const LegendreAngularDistributionFunction& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
