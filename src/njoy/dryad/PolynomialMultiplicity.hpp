#ifndef NJOY_DRYAD_POLYNOMIALMULTIPLICITY
#define NJOY_DRYAD_POLYNOMIALMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "njoy/dryad/TabulatedMultiplicity.hpp"
#include "scion/math/PolynomialSeries.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A multiplicity given as a polynomial series
   */
  class PolynomialMultiplicity :
      protected scion::math::PolynomialSeries< double, double > {

    /* constructor */

    private:

    /**
     *  @brief Private constructor
     *
     *  @param[in] series   the polynomial series
     */
    PolynomialMultiplicity( PolynomialSeries< double, double > series ) :
      PolynomialSeries( std::move( series ) ) {}

  public:

    /* type aliases */

    using PolynomialSeries::XType;
    using PolynomialSeries::YType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    PolynomialMultiplicity() = default;

    PolynomialMultiplicity( const PolynomialMultiplicity& ) = default;
    PolynomialMultiplicity( PolynomialMultiplicity&& ) = default;

    PolynomialMultiplicity& operator=( const PolynomialMultiplicity& ) = default;
    PolynomialMultiplicity& operator=( PolynomialMultiplicity&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] lower          the lower energy limit
     *  @param[in] upper          the upper energy limit
     *  @param[in] coefficients   the coefficients of the polynomial series (from
     *                            lowest to highest order coefficient)
     */
    PolynomialMultiplicity( double lower, double upper, std::vector< double > coefficients ) :
      PolynomialSeries( std::move( lower ), std::move( upper ), std::move( coefficients ) ) {}

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
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedMultiplicity linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = PolynomialSeries::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedMultiplicity( std::move( table ) );
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
