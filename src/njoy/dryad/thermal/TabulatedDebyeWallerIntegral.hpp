#ifndef NJOY_DRYAD_THERMAL_TABULATEDDEBYEWALLERINTEGRAL
#define NJOY_DRYAD_THERMAL_TABULATEDDEBYEWALLERINTEGRAL

// system includes
#include <vector>

// other includes
#include "njoy/dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief A Debye-Waller integral table
   *
   *  Temperature is assumed to be in K, values are 1/eV.
   */
  class TabulatedDebyeWallerIntegral  :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "njoy/dryad/thermal/TabulatedDebyeWallerIntegral/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the temperature values
     */
    const std::vector< double >& temperatures() const {

      return this->x();
    }

    /**
     *  @brief Return the integral values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower temperature limit
     */
    double lowerTemperatureLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper temperature limit
     */
    double upperTemperatureLimit() const {

      return this->x().back();
    }

    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    /**
     *  @brief Return a linearised Debye-Waller integral table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedDebyeWallerIntegral linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedDebyeWallerIntegral( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedDebyeWallerIntegral& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedDebyeWallerIntegral& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedDebyeWallerIntegral& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedDebyeWallerIntegral& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedDebyeWallerIntegral and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedDebyeWallerIntegral operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedDebyeWallerIntegral and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedDebyeWallerIntegral operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedDebyeWallerIntegral and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedDebyeWallerIntegral operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedDebyeWallerIntegral and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedDebyeWallerIntegral operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedDebyeWallerIntegral operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedDebyeWallerIntegral addition
     *
     *  @param[in] right    the table
     */
    TabulatedDebyeWallerIntegral& operator+=( const TabulatedDebyeWallerIntegral& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedDebyeWallerIntegral subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedDebyeWallerIntegral& operator-=( const TabulatedDebyeWallerIntegral& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedDebyeWallerIntegral and TabulatedDebyeWallerIntegral addition
     *
     *  @param[in] right    the table
     */
    TabulatedDebyeWallerIntegral operator+( const TabulatedDebyeWallerIntegral& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedDebyeWallerIntegral and TabulatedDebyeWallerIntegral subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedDebyeWallerIntegral operator-( const TabulatedDebyeWallerIntegral& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedDebyeWallerIntegral& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedDebyeWallerIntegral& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedDebyeWallerIntegral addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedDebyeWallerIntegral operator+( double left, const TabulatedDebyeWallerIntegral& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedDebyeWallerIntegral subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedDebyeWallerIntegral operator-( double left, const TabulatedDebyeWallerIntegral& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedDebyeWallerIntegral multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedDebyeWallerIntegral operator*( double left, const TabulatedDebyeWallerIntegral& right ) {

    return right * left;
  }

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
