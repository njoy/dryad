#ifndef NJOY_DRYAD_TABULATEDFORMFACTOR
#define NJOY_DRYAD_TABULATEDFORMFACTOR

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A form factor table
   */
  class TabulatedFormFactor :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/TabulatedFormFactor/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief Return the form factor values
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
     *  @brief Return a linearised form factor table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedFormFactor linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedFormFactor( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedFormFactor& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedFormFactor& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedFormFactor& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedFormFactor& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedFormFactor and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedFormFactor operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedFormFactor and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedFormFactor operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedFormFactor and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedFormFactor operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedFormFactor and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedFormFactor operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedFormFactor operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedFormFactor addition
     *
     *  @param[in] right    the table
     */
    TabulatedFormFactor& operator+=( const TabulatedFormFactor& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedFormFactor subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedFormFactor& operator-=( const TabulatedFormFactor& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedFormFactor and TabulatedFormFactor addition
     *
     *  @param[in] right    the table
     */
    TabulatedFormFactor operator+( const TabulatedFormFactor& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedFormFactor and TabulatedFormFactor subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedFormFactor operator-( const TabulatedFormFactor& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedFormFactor& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedFormFactor& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedFormFactor addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedFormFactor operator+( double left, const TabulatedFormFactor& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedFormFactor subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedFormFactor operator-( double left, const TabulatedFormFactor& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedFormFactor multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedFormFactor operator*( double left, const TabulatedFormFactor& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
