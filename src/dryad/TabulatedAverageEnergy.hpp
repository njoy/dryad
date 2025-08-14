#ifndef NJOY_DRYAD_TABULATEDAVERAGEENERGY
#define NJOY_DRYAD_TABULATEDAVERAGEENERGY

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An average reaction product energy table
   */
  class TabulatedAverageEnergy :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/TabulatedAverageEnergy/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief Return the average energy values
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
     *  @brief Return a linearised cross section table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedAverageEnergy linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedAverageEnergy( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageEnergy& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageEnergy& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageEnergy& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageEnergy& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAverageEnergy and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageEnergy operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAverageEnergy and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageEnergy operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedAverageEnergy and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageEnergy operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedAverageEnergy and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageEnergy operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedAverageEnergy operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedAverageEnergy addition
     *
     *  @param[in] right    the table
     */
    TabulatedAverageEnergy& operator+=( const TabulatedAverageEnergy& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedAverageEnergy subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAverageEnergy& operator-=( const TabulatedAverageEnergy& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAverageEnergy and TabulatedAverageEnergy addition
     *
     *  @param[in] right    the table
     */
    TabulatedAverageEnergy operator+( const TabulatedAverageEnergy& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAverageEnergy and TabulatedAverageEnergy subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAverageEnergy operator-( const TabulatedAverageEnergy& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedAverageEnergy& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedAverageEnergy& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedAverageEnergy addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageEnergy operator+( double left, const TabulatedAverageEnergy& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedAverageEnergy subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageEnergy operator-( double left, const TabulatedAverageEnergy& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedAverageEnergy multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageEnergy operator*( double left, const TabulatedAverageEnergy& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
