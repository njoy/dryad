#ifndef NJOY_DRYAD_TABULATEDMULTIPLICITY
#define NJOY_DRYAD_TABULATEDMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A multiplicity table
   */
  class TabulatedMultiplicity :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* constructor */
    #include "dryad/TabulatedMultiplicity/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const noexcept {

      return this->x();
    }

    /**
     *  @brief Return the multiplicity values
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
    TabulatedMultiplicity linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedMultiplicity( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedMultiplicity& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedMultiplicity& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedMultiplicity& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedMultiplicity& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedMultiplicity and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedMultiplicity operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedMultiplicity and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedMultiplicity operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedMultiplicity and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedMultiplicity operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedMultiplicity and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedMultiplicity operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedMultiplicity operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedMultiplicity addition
     *
     *  @param[in] right    the table
     */
    TabulatedMultiplicity& operator+=( const TabulatedMultiplicity& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedMultiplicity subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedMultiplicity& operator-=( const TabulatedMultiplicity& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedMultiplicity and TabulatedMultiplicity addition
     *
     *  @param[in] right    the table
     */
    TabulatedMultiplicity operator+( const TabulatedMultiplicity& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedMultiplicity and TabulatedMultiplicity subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedMultiplicity operator-( const TabulatedMultiplicity& right ) const {

      return InterpolationTable::operator-( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedMultiplicity addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedMultiplicity operator+( double left, const TabulatedMultiplicity& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedMultiplicity subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedMultiplicity operator-( double left, const TabulatedMultiplicity& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedMultiplicity multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedMultiplicity operator*( double left, const TabulatedMultiplicity& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
