#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/LegendreSeries.hpp"
#include "dryad/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution table
   */
  class LegendreAngularDistribution :
      protected scion::math::LegendreSeries< double, double > {

  public:

    /* constructor */
    #include "dryad/LegendreAngularDistribution/src/ctor.hpp"

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
    TabulatedAngularDistribution linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedAngularDistribution( LegendreSeries::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistribution& operator+=( double right ) {

      LegendreSeries::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistribution& operator-=( double right ) {

      LegendreSeries::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistribution& operator*=( double right ) {

      LegendreSeries::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistribution& operator/=( double right ) {

      LegendreSeries::operator/=( right );
      return *this;
    }

    /**
     *  @brief LegendreAngularDistribution and scalar addition
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistribution operator+( double right ) const {

      return LegendreSeries::operator+( right );
    }

    /**
     *  @brief LegendreAngularDistribution and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistribution operator-( double right ) const {

      return LegendreSeries::operator-( right );
    }

    /**
     *  @brief LegendreAngularDistribution and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistribution operator*( double right ) const {

      return LegendreSeries::operator*( right );
    }

    /**
     *  @brief LegendreAngularDistribution and scalar division
     *
     *  @param[in] right    the scalar
     */
    LegendreAngularDistribution operator/( double right ) const {

      return LegendreSeries::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    LegendreAngularDistribution operator-() const {

      return LegendreSeries::operator-();
    }

    /**
     *  @brief Inplace LegendreAngularDistribution addition
     *
     *  @param[in] right    the table
     */
    LegendreAngularDistribution& operator+=( const LegendreAngularDistribution& right ) {

      LegendreSeries::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace LegendreAngularDistribution subtraction
     *
     *  @param[in] right    the table
     */
    LegendreAngularDistribution& operator-=( const LegendreAngularDistribution& right ) {

      LegendreSeries::operator-=( right );
      return *this;
    }

    /**
     *  @brief LegendreAngularDistribution and LegendreAngularDistribution addition
     *
     *  @param[in] right    the table
     */
    LegendreAngularDistribution operator+( const LegendreAngularDistribution& right ) const {

      return LegendreSeries::operator+( right );
    }

    /**
     *  @brief LegendreAngularDistribution and LegendreAngularDistribution subtraction
     *
     *  @param[in] right    the table
     */
    LegendreAngularDistribution operator-( const LegendreAngularDistribution& right ) const {

      return LegendreSeries::operator-( right );
    }
  };

  /**
   *  @brief Scalar and LegendreAngularDistribution addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline LegendreAngularDistribution operator+( double left, const LegendreAngularDistribution& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and LegendreAngularDistribution subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline LegendreAngularDistribution operator-( double left, const LegendreAngularDistribution& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and LegendreAngularDistribution multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline LegendreAngularDistribution operator*( double left, const LegendreAngularDistribution& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
