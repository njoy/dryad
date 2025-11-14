#ifndef NJOY_DRYAD_TABULATEDCOMPTONPROFILE
#define NJOY_DRYAD_TABULATEDCOMPTONPROFILE

// system includes
#include <vector>

// other includes
#include "njoy/dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An tabulated Compton profile for photoatomic data
   */
  class TabulatedComptonProfile :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "njoy/dryad/TabulatedComptonProfile/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the momentum values
     */
    const std::vector< double >& momentum() const {

      return this->x();
    }

    /**
     *  @brief Return the probability values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower momentum limit
     */
    double lowerMomentumLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper momentum limit
     */
    double upperMomentumLimit() const {

      return this->x().back();
    }

    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    using InterpolationTable::integral;
    using InterpolationTable::cumulativeIntegral;

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedComptonProfile linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedComptonProfile( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfile& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfile& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfile& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfile& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedComptonProfile and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfile operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedComptonProfile and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfile operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedComptonProfile and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfile operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedComptonProfile and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfile operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedComptonProfile operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedComptonProfile addition
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfile&
    operator+=( const TabulatedComptonProfile& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedComptonProfile subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfile&
    operator-=( const TabulatedComptonProfile& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedComptonProfile addition
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfile
    operator+( const TabulatedComptonProfile& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedComptonProfile subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfile
    operator-( const TabulatedComptonProfile& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedComptonProfile& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedComptonProfile& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedComptonProfile
  operator+( double left, const TabulatedComptonProfile& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedComptonProfile
  operator-( double left, const TabulatedComptonProfile& right ) {

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
  inline TabulatedComptonProfile
  operator*( double left, const TabulatedComptonProfile& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
