#ifndef NJOY_DRYAD_POLYNOMIALMULTIPLICITY
#define NJOY_DRYAD_POLYNOMIALMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "dryad/TabulatedMultiplicity.hpp"
#include "scion/math/PolynomialSeries.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A multiplicity given as a polynomial series
   */
  class PolynomialMultiplicity :
      protected scion::math::PolynomialSeries< double, double > {

  public:

    /* type aliases */
    using PolynomialSeries::XType;
    using PolynomialSeries::YType;

    /* constructor */

    #include "dryad/PolynomialMultiplicity/src/ctor.hpp"

    /* methods */

    using PolynomialSeries::coefficients;
    using PolynomialSeries::order;
    using PolynomialSeries::operator();

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return std::get< njoy::scion::math::IntervalDomain< double > >( this->domain() ).lowerLimit();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return std::get< njoy::scion::math::IntervalDomain< double > >( this->domain() ).upperLimit();
    }

    /**
     *  @brief Return a linearised multiplicity table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedMultiplicity linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedMultiplicity( PolynomialSeries::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    PolynomialMultiplicity& operator+=( double right ) {

      PolynomialSeries::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    PolynomialMultiplicity& operator-=( double right ) {

      PolynomialSeries::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    PolynomialMultiplicity& operator*=( double right ) {

      PolynomialSeries::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    PolynomialMultiplicity& operator/=( double right ) {

      PolynomialSeries::operator/=( right );
      return *this;
    }

    /**
     *  @brief PolynomialMultiplicity and scalar addition
     *
     *  @param[in] right    the scalar
     */
    PolynomialMultiplicity operator+( double right ) const {

      return PolynomialSeries::operator+( right );
    }

    /**
     *  @brief PolynomialMultiplicity and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    PolynomialMultiplicity operator-( double right ) const {

      return PolynomialSeries::operator-( right );
    }

    /**
     *  @brief PolynomialMultiplicity and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    PolynomialMultiplicity operator*( double right ) const {

      return PolynomialSeries::operator*( right );
    }

    /**
     *  @brief PolynomialMultiplicity and scalar division
     *
     *  @param[in] right    the scalar
     */
    PolynomialMultiplicity operator/( double right ) const {

      return PolynomialSeries::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    PolynomialMultiplicity operator-() const {

      return PolynomialSeries::operator-();
    }

    /**
     *  @brief Inplace PolynomialMultiplicity addition
     *
     *  @param[in] right    the table
     */
    PolynomialMultiplicity& operator+=( const PolynomialMultiplicity& right ) {

      PolynomialSeries::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace PolynomialMultiplicity subtraction
     *
     *  @param[in] right    the table
     */
    PolynomialMultiplicity& operator-=( const PolynomialMultiplicity& right ) {

      PolynomialSeries::operator-=( right );
      return *this;
    }

    /**
     *  @brief PolynomialMultiplicity and PolynomialMultiplicity addition
     *
     *  @param[in] right    the table
     */
    PolynomialMultiplicity operator+( const PolynomialMultiplicity& right ) const {

      return PolynomialSeries::operator+( right );
    }

    /**
     *  @brief PolynomialMultiplicity and PolynomialMultiplicity subtraction
     *
     *  @param[in] right    the table
     */
    PolynomialMultiplicity operator-( const PolynomialMultiplicity& right ) const {

      return PolynomialSeries::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const PolynomialMultiplicity& right ) const {

      return PolynomialSeries::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const PolynomialMultiplicity& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and PolynomialMultiplicity addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline PolynomialMultiplicity operator+( double left, const PolynomialMultiplicity& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and PolynomialMultiplicity subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline PolynomialMultiplicity operator-( double left, const PolynomialMultiplicity& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and PolynomialMultiplicity multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline PolynomialMultiplicity operator*( double left, const PolynomialMultiplicity& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
