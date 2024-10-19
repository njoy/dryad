#ifndef NJOY_DRYAD_TABULATEDANGULARDISTRIBUTION
#define NJOY_DRYAD_TABULATEDANGULARDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  // forward declaration LegendreAngularDistribution
  class LegendreAngularDistribution;

  /**
   *  @class
   *  @brief An angular distribution table
   */
  class TabulatedAngularDistribution :
      protected scion::math::InterpolationTable< double, double > {

  friend LegendreAngularDistribution;

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/TabulatedAngularDistribution/src/ctor.hpp"

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
    TabulatedAngularDistribution linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedAngularDistribution( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistribution& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistribution& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistribution& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistribution& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAngularDistribution and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistribution operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAngularDistribution and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistribution operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedAngularDistribution and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistribution operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedAngularDistribution and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistribution operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedAngularDistribution operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedAngularDistribution addition
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistribution& operator+=( const TabulatedAngularDistribution& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedAngularDistribution subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistribution& operator-=( const TabulatedAngularDistribution& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAngularDistribution and TabulatedAngularDistribution addition
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistribution operator+( const TabulatedAngularDistribution& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAngularDistribution and TabulatedAngularDistribution subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistribution operator-( const TabulatedAngularDistribution& right ) const {

      return InterpolationTable::operator-( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedAngularDistribution addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAngularDistribution operator+( double left, const TabulatedAngularDistribution& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedAngularDistribution subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAngularDistribution operator-( double left, const TabulatedAngularDistribution& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedAngularDistribution multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAngularDistribution operator*( double left, const TabulatedAngularDistribution& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
