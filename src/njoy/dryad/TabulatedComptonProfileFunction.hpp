#ifndef NJOY_DRYAD_TABULATEDCOMPTONPROFILEFUNCTION
#define NJOY_DRYAD_TABULATEDCOMPTONPROFILEFUNCTION

// system includes
#include <vector>

// other includes
#include "njoy/dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A tabulated Compton profile distribution for photoatomic data
   */
  class TabulatedComptonProfileFunction :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "njoy/dryad/TabulatedComptonProfileFunction/src/ctor.hpp"

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
     *  @brief Return a linearised Compton profile table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedComptonProfileFunction linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedComptonProfileFunction( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedComptonProfileFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedComptonProfileFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedComptonProfileFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedComptonProfileFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedComptonProfileFunction operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedComptonProfileFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfileFunction&
    operator+=( const TabulatedComptonProfileFunction& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedComptonProfileFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfileFunction&
    operator-=( const TabulatedComptonProfileFunction& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedComptonProfileFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfileFunction
    operator+( const TabulatedComptonProfileFunction& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedComptonProfileFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfileFunction
    operator-( const TabulatedComptonProfileFunction& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedComptonProfileFunction& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedComptonProfileFunction& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedComptonProfileFunction
  operator+( double left, const TabulatedComptonProfileFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedComptonProfileFunction
  operator-( double left, const TabulatedComptonProfileFunction& right ) {

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
  inline TabulatedComptonProfileFunction
  operator*( double left, const TabulatedComptonProfileFunction& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
