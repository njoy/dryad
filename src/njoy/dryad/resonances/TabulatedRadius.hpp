#ifndef NJOY_DRYAD_RESONANCES_TABULATEDRADIUS
#define NJOY_DRYAD_RESONANCES_TABULATEDRADIUS

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A radius table
   *
   *  The radius is given in femto meters (fm).
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class TabulatedRadius :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/resonances/TabulatedRadius/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief Return the radius values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->x().back();
    }

    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    /**
     *  @brief Return a linearised radius table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedRadius linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedRadius( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedRadius and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedRadius and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedRadius and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedRadius and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedRadius operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedRadius addition
     *
     *  @param[in] right    the table
     */
    TabulatedRadius& operator+=( const TabulatedRadius& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedRadius subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedRadius& operator-=( const TabulatedRadius& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedRadius and TabulatedRadius addition
     *
     *  @param[in] right    the table
     */
    TabulatedRadius operator+( const TabulatedRadius& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedRadius and TabulatedRadius subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedRadius operator-( const TabulatedRadius& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedRadius& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedRadius& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedRadius addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedRadius operator+( double left, const TabulatedRadius& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedRadius subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedRadius operator-( double left, const TabulatedRadius& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedRadius multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedRadius operator*( double left, const TabulatedRadius& right ) {

    return right * left;
  }

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
