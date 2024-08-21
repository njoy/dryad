#ifndef NJOY_DRYAD_TABULATEDANGULARDISTRIBUTIONFUNCTION
#define NJOY_DRYAD_TABULATEDANGULARDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  // forward declaration LegendreAngularDistribution
  class LegendreAngularDistributionFunction;

  /**
   *  @class
   *  @brief An angular distribution function using tabulated data
   */
  class TabulatedAngularDistributionFunction :
      protected scion::math::InterpolationTable< double, double > {

  friend LegendreAngularDistributionFunction;

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/TabulatedAngularDistributionFunction/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the cosine values
     */
    const std::vector< double >& cosines() const noexcept {

      return this->x();
    }

    /**
     *  @brief Return the probability values
     */
    const std::vector< double >& values() const noexcept {

      return this->y();
    }

    /**
     *  @brief Return the lower cosine limit
     */
    double lowerCosineLimit() const noexcept {

      return this->x().front();
    }

    /**
     *  @brief Return the upper cosine limit
     */
    double upperCosineLimit() const noexcept {

      return this->x().back();
    }

    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedAngularDistributionFunction linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedAngularDistributionFunction( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAngularDistributionFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAngularDistributionFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedAngularDistributionFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedAngularDistributionFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedAngularDistributionFunction operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedAngularDistributionFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistributionFunction&
    operator+=( const TabulatedAngularDistributionFunction& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedAngularDistributionFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistributionFunction&
    operator-=( const TabulatedAngularDistributionFunction& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAngularDistributionFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistributionFunction
    operator+( const TabulatedAngularDistributionFunction& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAngularDistributionFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistributionFunction
    operator-( const TabulatedAngularDistributionFunction& right ) const {

      return InterpolationTable::operator-( right );
    }
  };

  /**
   *  @brief Scalar addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAngularDistributionFunction
  operator+( double left, const TabulatedAngularDistributionFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAngularDistributionFunction
  operator-( double left, const TabulatedAngularDistributionFunction& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAngularDistributionFunction
  operator*( double left, const TabulatedAngularDistributionFunction& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
