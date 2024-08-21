#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/LegendreSeries.hpp"
#include "dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution table
   */
  class LegendreAngularDistributionFunction :
      protected scion::math::LegendreSeries< double, double > {

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
    static constexpr double lowerCosineLimit() noexcept { return -1.0; }

    /**
     *  @brief Return the upper cosine limit
     */
    static constexpr double upperCosineLimit() noexcept { return 1.0; }

    using LegendreSeries::operator();
    using LegendreSeries::order;

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
