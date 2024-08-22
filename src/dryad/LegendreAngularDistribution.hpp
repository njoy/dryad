#ifndef NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION
#define NJOY_DRYAD_LEGENDREANGULARDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/LegendreAngularDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An angular distribution defined by a pdf and cdf using Legendre
   *         expansions
   */
  class LegendreAngularDistribution {

    /* fields */
    LegendreAngularDistributionFunction pdf_;
    std::optional< LegendreAngularDistributionFunction > cdf_;

  public:

    /* type aliases */

    using XType = LegendreAngularDistributionFunction::XType;
    using YType = LegendreAngularDistributionFunction::XType;

    /* constructor */

    #include "dryad/LegendreAngularDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const LegendreAngularDistributionFunction& pdf() const noexcept {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const std::optional< LegendreAngularDistributionFunction >& cdf() const noexcept {

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

    /**
     *  @brief Calculate the associated cdf for the distribution
     */
    void calculateCdf() {

      this->cdf_ = this->pdf().primitive( -1. );
      this->cdf_.value() /= this->cdf_.value()( 1. );
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
//    LegendreAngularDistributionFunction& operator+=( double right ) {
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
//    LegendreAngularDistributionFunction& operator-=( double right ) {
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
//    LegendreAngularDistributionFunction& operator*=( double right ) {
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
//    LegendreAngularDistributionFunction& operator/=( double right ) {
//
//      LegendreSeries::operator/=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief LegendreAngularDistributionFunction and scalar addition
//     *
//     *  @param[in] right    the scalar
//     */
//    LegendreAngularDistributionFunction operator+( double right ) const {
//
//      return LegendreSeries::operator+( right );
//    }
//
//    /**
//     *  @brief LegendreAngularDistributionFunction and scalar subtraction
//     *
//     *  @param[in] right    the scalar
//     */
//    LegendreAngularDistributionFunction operator-( double right ) const {
//
//      return LegendreSeries::operator-( right );
//    }
//
//    /**
//     *  @brief LegendreAngularDistributionFunction and scalar multiplication
//     *
//     *  @param[in] right    the scalar
//     */
//    LegendreAngularDistributionFunction operator*( double right ) const {
//
//      return LegendreSeries::operator*( right );
//    }
//
//    /**
//     *  @brief LegendreAngularDistributionFunction and scalar division
//     *
//     *  @param[in] right    the scalar
//     */
//    LegendreAngularDistributionFunction operator/( double right ) const {
//
//      return LegendreSeries::operator/( right );
//    }
//
//    /**
//     *  @brief Unary minus
//     */
//    LegendreAngularDistributionFunction operator-() const {
//
//      return LegendreSeries::operator-();
//    }
//
//    /**
//     *  @brief Inplace LegendreAngularDistributionFunction addition
//     *
//     *  @param[in] right    the table
//     */
//    LegendreAngularDistributionFunction&
//    operator+=( const LegendreAngularDistributionFunction& right ) {
//
//      LegendreSeries::operator+=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief Inplace LegendreAngularDistributionFunction subtraction
//     *
//     *  @param[in] right    the table
//     */
//    LegendreAngularDistributionFunction&
//    operator-=( const LegendreAngularDistributionFunction& right ) {
//
//      LegendreSeries::operator-=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief LegendreAngularDistributionFunction addition
//     *
//     *  @param[in] right    the table
//     */
//    LegendreAngularDistributionFunction
//    operator+( const LegendreAngularDistributionFunction& right ) const {
//
//      return LegendreSeries::operator+( right );
//    }
//
//    /**
//     *  @brief LegendreAngularDistributionFunction subtraction
//     *
//     *  @param[in] right    the table
//     */
//    LegendreAngularDistributionFunction
//    operator-( const LegendreAngularDistributionFunction& right ) const {
//
//      return LegendreSeries::operator-( right );
//    }
  };

//  /**
//   *  @brief Scalar and LegendreAngularDistributionFunction addition
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline LegendreAngularDistributionFunction
//  operator+( double left, const LegendreAngularDistributionFunction& right ) {
//
//    return right + left;
//  }
//
//  /**
//   *  @brief Scalar and LegendreAngularDistributionFunction subtraction
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline LegendreAngularDistributionFunction
//  operator-( double left, const LegendreAngularDistributionFunction& right ) {
//
//    auto result = -right;
//    result += left;
//    return result;
//  }
//
//  /**
//   *  @brief Scalar and LegendreAngularDistributionFunction multiplication
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline LegendreAngularDistributionFunction
//  operator*( double left, const LegendreAngularDistributionFunction& right ) {
//
//    return right * left;
//  }

} // dryad namespace
} // njoy namespace

#endif
