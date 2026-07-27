#ifndef NJOY_DRYAD_RESONANCES_TABULATEDWAVEFUNCTION
#define NJOY_DRYAD_RESONANCES_TABULATEDWAVEFUNCTION

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A tabulated function representing penetrability, shift or phase shift
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class TabulatedWaveFunction :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "njoy/dryad/resonances/TabulatedWaveFunction/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the ratio values
     */
    const std::vector< double >& ratios() const {

      return this->x();
    }

    /**
     *  @brief Return the wave function values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower ratio limit
     */
    double lowerRatioLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper ratio limit
     */
    double upperRatioLimit() const {

      return this->x().back();
    }

    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    /**
     *  @brief Return a linearised penetrability table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedWaveFunction linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedWaveFunction( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedWaveFunction& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedWaveFunction& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedWaveFunction& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedWaveFunction& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedWaveFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedWaveFunction operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedWaveFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedWaveFunction operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedWaveFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedWaveFunction operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedWaveFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedWaveFunction operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedWaveFunction operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedWaveFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedWaveFunction& operator+=( const TabulatedWaveFunction& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedWaveFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedWaveFunction& operator-=( const TabulatedWaveFunction& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedWaveFunction and TabulatedWaveFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedWaveFunction operator+( const TabulatedWaveFunction& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedWaveFunction and TabulatedWaveFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedWaveFunction operator-( const TabulatedWaveFunction& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedWaveFunction& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedWaveFunction& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedWaveFunction addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedWaveFunction operator+( double left, const TabulatedWaveFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedWaveFunction subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedWaveFunction operator-( double left, const TabulatedWaveFunction& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedWaveFunction multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedWaveFunction operator*( double left, const TabulatedWaveFunction& right ) {

    return right * left;
  }

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
