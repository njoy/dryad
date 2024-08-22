#ifndef NJOY_DRYAD_TABULATEDANGULARDISTRIBUTION
#define NJOY_DRYAD_TABULATEDANGULARDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/TabulatedAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution defined by a pdf and cdf using tabulated
   *         data
   */
  class TabulatedAngularDistribution {

    /* fields */
    TabulatedAngularDistributionFunction pdf_;
    std::optional< TabulatedAngularDistributionFunction > cdf_;

  public:

    /* type aliases */

    using XType = TabulatedAngularDistributionFunction::XType;
    using YType = TabulatedAngularDistributionFunction::XType;

    /* constructor */

    #include "dryad/TabulatedAngularDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const TabulatedAngularDistributionFunction& pdf() const noexcept {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const std::optional< TabulatedAngularDistributionFunction >& cdf() const noexcept {

      return this->cdf_;
    }

    /**
     *  @brief Evaluate the pdf of the distribution for a cosine value
     *
     *  @param cosine   the value to be evaluated
     */
    double operator()( double cosine ) const {

      return this->pdf()( cosine );
    }

//    /**
//     *  @brief Return a linearised angular distribution table
//     *
//     *  @param[in] tolerance   the linearisation tolerance
//     */
//    TabulatedAngularDistribution linearise( ToleranceConvergence tolerance = {} ) const {
//
//    }

//    /**
//     *  @brief Inplace scalar addition
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedAngularDistributionFunction& operator+=( double right ) {
//
//      LegendreSeries::operator+=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief Inplace scalar subtraction
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedAngularDistributionFunction& operator-=( double right ) {
//
//      LegendreSeries::operator-=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief Inplace scalar multiplication
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedAngularDistributionFunction& operator*=( double right ) {
//
//      LegendreSeries::operator*=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief Inplace scalar division
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedAngularDistributionFunction& operator/=( double right ) {
//
//      LegendreSeries::operator/=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief TabulatedAngularDistributionFunction and scalar addition
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedAngularDistributionFunction operator+( double right ) const {
//
//      return LegendreSeries::operator+( right );
//    }
//
//    /**
//     *  @brief TabulatedAngularDistributionFunction and scalar subtraction
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedAngularDistributionFunction operator-( double right ) const {
//
//      return LegendreSeries::operator-( right );
//    }
//
//    /**
//     *  @brief TabulatedAngularDistributionFunction and scalar multiplication
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedAngularDistributionFunction operator*( double right ) const {
//
//      return LegendreSeries::operator*( right );
//    }
//
//    /**
//     *  @brief TabulatedAngularDistributionFunction and scalar division
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedAngularDistributionFunction operator/( double right ) const {
//
//      return LegendreSeries::operator/( right );
//    }
//
//    /**
//     *  @brief Unary minus
//     */
//    TabulatedAngularDistributionFunction operator-() const {
//
//      return LegendreSeries::operator-();
//    }
//
//    /**
//     *  @brief Inplace TabulatedAngularDistributionFunction addition
//     *
//     *  @param[in] right    the table
//     */
//    TabulatedAngularDistributionFunction&
//    operator+=( const TabulatedAngularDistributionFunction& right ) {
//
//      LegendreSeries::operator+=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief Inplace TabulatedAngularDistributionFunction subtraction
//     *
//     *  @param[in] right    the table
//     */
//    TabulatedAngularDistributionFunction&
//    operator-=( const TabulatedAngularDistributionFunction& right ) {
//
//      LegendreSeries::operator-=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief TabulatedAngularDistributionFunction addition
//     *
//     *  @param[in] right    the table
//     */
//    TabulatedAngularDistributionFunction
//    operator+( const TabulatedAngularDistributionFunction& right ) const {
//
//      return LegendreSeries::operator+( right );
//    }
//
//    /**
//     *  @brief TabulatedAngularDistributionFunction subtraction
//     *
//     *  @param[in] right    the table
//     */
//    TabulatedAngularDistributionFunction
//    operator-( const TabulatedAngularDistributionFunction& right ) const {
//
//      return LegendreSeries::operator-( right );
//    }
  };

//  /**
//   *  @brief Scalar and TabulatedAngularDistributionFunction addition
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline TabulatedAngularDistributionFunction
//  operator+( double left, const TabulatedAngularDistributionFunction& right ) {
//
//    return right + left;
//  }
//
//  /**
//   *  @brief Scalar and TabulatedAngularDistributionFunction subtraction
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline TabulatedAngularDistributionFunction
//  operator-( double left, const TabulatedAngularDistributionFunction& right ) {
//
//    auto result = -right;
//    result += left;
//    return result;
//  }
//
//  /**
//   *  @brief Scalar and TabulatedAngularDistributionFunction multiplication
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline TabulatedAngularDistributionFunction
//  operator*( double left, const TabulatedAngularDistributionFunction& right ) {
//
//    return right * left;
//  }

} // dryad namespace
} // njoy namespace

#endif
