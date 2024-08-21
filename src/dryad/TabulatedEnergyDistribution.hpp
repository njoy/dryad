#ifndef NJOY_DRYAD_TABULATEDENERGYDISTRIBUTION
#define NJOY_DRYAD_TABULATEDENERGYDISTRIBUTION

// system includes
#include <vector>
#include <optional>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/TabulatedEnergyDistributionFunction.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An energy distribution defined by a pdf and cdf using tabulated
   *         data
   */
  class TabulatedEnergyDistribution {

    /* fields */
    TabulatedEnergyDistributionFunction pdf_;
    std::optional< TabulatedEnergyDistributionFunction > cdf_;

  public:

    /* type aliases */

    using XType = TabulatedEnergyDistributionFunction::XType;
    using YType = TabulatedEnergyDistributionFunction::XType;

    /* constructor */

    #include "dryad/TabulatedEnergyDistribution/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the probability distribution function (pdf) of the distribution
     */
    const TabulatedEnergyDistributionFunction& pdf() const noexcept {

      return this->pdf_;
    }

    /**
     *  @brief Return the cumulative distribution function (cdf) of the distribution
     */
    const std::optional< TabulatedEnergyDistributionFunction >& cdf() const noexcept {

      return this->cdf_;
    }

    /**
     *  @brief Evaluate the pdf for a cosine value
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
//    TabulatedEnergyDistribution linearise( ToleranceConvergence tolerance = {} ) const {
//
//    }

//    /**
//     *  @brief Inplace scalar addition
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedEnergyDistributionFunction& operator+=( double right ) {
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
//    TabulatedEnergyDistributionFunction& operator-=( double right ) {
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
//    TabulatedEnergyDistributionFunction& operator*=( double right ) {
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
//    TabulatedEnergyDistributionFunction& operator/=( double right ) {
//
//      LegendreSeries::operator/=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief TabulatedEnergyDistributionFunction and scalar addition
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedEnergyDistributionFunction operator+( double right ) const {
//
//      return LegendreSeries::operator+( right );
//    }
//
//    /**
//     *  @brief TabulatedEnergyDistributionFunction and scalar subtraction
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedEnergyDistributionFunction operator-( double right ) const {
//
//      return LegendreSeries::operator-( right );
//    }
//
//    /**
//     *  @brief TabulatedEnergyDistributionFunction and scalar multiplication
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedEnergyDistributionFunction operator*( double right ) const {
//
//      return LegendreSeries::operator*( right );
//    }
//
//    /**
//     *  @brief TabulatedEnergyDistributionFunction and scalar division
//     *
//     *  @param[in] right    the scalar
//     */
//    TabulatedEnergyDistributionFunction operator/( double right ) const {
//
//      return LegendreSeries::operator/( right );
//    }
//
//    /**
//     *  @brief Unary minus
//     */
//    TabulatedEnergyDistributionFunction operator-() const {
//
//      return LegendreSeries::operator-();
//    }
//
//    /**
//     *  @brief Inplace TabulatedEnergyDistributionFunction addition
//     *
//     *  @param[in] right    the table
//     */
//    TabulatedEnergyDistributionFunction&
//    operator+=( const TabulatedEnergyDistributionFunction& right ) {
//
//      LegendreSeries::operator+=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief Inplace TabulatedEnergyDistributionFunction subtraction
//     *
//     *  @param[in] right    the table
//     */
//    TabulatedEnergyDistributionFunction&
//    operator-=( const TabulatedEnergyDistributionFunction& right ) {
//
//      LegendreSeries::operator-=( right );
//      return *this;
//    }
//
//    /**
//     *  @brief TabulatedEnergyDistributionFunction addition
//     *
//     *  @param[in] right    the table
//     */
//    TabulatedEnergyDistributionFunction
//    operator+( const TabulatedEnergyDistributionFunction& right ) const {
//
//      return LegendreSeries::operator+( right );
//    }
//
//    /**
//     *  @brief TabulatedEnergyDistributionFunction subtraction
//     *
//     *  @param[in] right    the table
//     */
//    TabulatedEnergyDistributionFunction
//    operator-( const TabulatedEnergyDistributionFunction& right ) const {
//
//      return LegendreSeries::operator-( right );
//    }
  };

//  /**
//   *  @brief Scalar and TabulatedEnergyDistributionFunction addition
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline TabulatedEnergyDistributionFunction
//  operator+( double left, const TabulatedEnergyDistributionFunction& right ) {
//
//    return right + left;
//  }
//
//  /**
//   *  @brief Scalar and TabulatedEnergyDistributionFunction subtraction
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline TabulatedEnergyDistributionFunction
//  operator-( double left, const TabulatedEnergyDistributionFunction& right ) {
//
//    auto result = -right;
//    result += left;
//    return result;
//  }
//
//  /**
//   *  @brief Scalar and TabulatedEnergyDistributionFunction multiplication
//   *
//   *  @param[in] left    the scalar
//   *  @param[in] right   the table
//   */
//  inline TabulatedEnergyDistributionFunction
//  operator*( double left, const TabulatedEnergyDistributionFunction& right ) {
//
//    return right * left;
//  }

} // dryad namespace
} // njoy namespace

#endif
