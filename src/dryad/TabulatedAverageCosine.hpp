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
   *  @brief An average cosine table
   */
  class TabulatedAverageCosine :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/TabulatedAverageCosine/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const noexcept {

      return this->x();
    }

    /**
     *  @brief Return the average cosine values
     */
    const std::vector< double >& values() const noexcept {

      return this->y();
    }

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const noexcept {

      return this->x().front();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const noexcept {

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
    TabulatedAverageCosine linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedAverageCosine( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageCosine& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageCosine& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageCosine& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageCosine& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAverageCosine and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageCosine operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAverageCosine and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageCosine operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedAverageCosine and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageCosine operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedAverageCosine and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageCosine operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedAverageCosine operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedAverageCosine addition
     *
     *  @param[in] right    the table
     */
    TabulatedAverageCosine& operator+=( const TabulatedAverageCosine& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedAverageCosine subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAverageCosine& operator-=( const TabulatedAverageCosine& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAverageCosine and TabulatedAverageCosine addition
     *
     *  @param[in] right    the table
     */
    TabulatedAverageCosine operator+( const TabulatedAverageCosine& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAverageCosine and TabulatedAverageCosine subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAverageCosine operator-( const TabulatedAverageCosine& right ) const {

      return InterpolationTable::operator-( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedAverageCosine addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageCosine operator+( double left, const TabulatedAverageCosine& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedAverageCosine subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageCosine operator-( double left, const TabulatedAverageCosine& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedAverageCosine multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageCosine operator*( double left, const TabulatedAverageCosine& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
