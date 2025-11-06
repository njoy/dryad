#ifndef NJOY_DRYAD_TABULATEDCROSSSECTION
#define NJOY_DRYAD_TABULATEDCROSSSECTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A cross section table
   */
  class TabulatedCrossSection :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/TabulatedCrossSection/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief Return the cross section values
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
    TabulatedCrossSection linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedCrossSection( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedCrossSection& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedCrossSection& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedCrossSection& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedCrossSection& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedCrossSection and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedCrossSection operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedCrossSection and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedCrossSection operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedCrossSection and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedCrossSection operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedCrossSection and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedCrossSection operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedCrossSection operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedCrossSection addition
     *
     *  @param[in] right    the table
     */
    TabulatedCrossSection& operator+=( const TabulatedCrossSection& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedCrossSection subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedCrossSection& operator-=( const TabulatedCrossSection& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedCrossSection and TabulatedCrossSection addition
     *
     *  @param[in] right    the table
     */
    TabulatedCrossSection operator+( const TabulatedCrossSection& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedCrossSection and TabulatedCrossSection subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedCrossSection operator-( const TabulatedCrossSection& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedCrossSection& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedCrossSection& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedCrossSection addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedCrossSection operator+( double left, const TabulatedCrossSection& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedCrossSection subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedCrossSection operator-( double left, const TabulatedCrossSection& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedCrossSection multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedCrossSection operator*( double left, const TabulatedCrossSection& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
