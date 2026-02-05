#ifndef NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGFUNCTION
#define NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGFUNCTION

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief A tabulated scattering function S(alpha)
   */
  class TabulatedScatteringFunction  :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "njoy/dryad/thermal/TabulatedScatteringFunction/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the momentum transfer values
     */
    const std::vector< double >& momentumTransfers() const {

      return this->x();
    }

    /**
     *  @brief Return the scattering function values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower momentum transfer limit
     */
    double lowerMomentumTransferLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper momentum transfer limit
     */
    double upperMomentumTransferLimit() const {

      return this->x().back();
    }

    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    /**
     *  @brief Return a linearised effective temperature table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedScatteringFunction linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedScatteringFunction( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringFunction& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringFunction& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringFunction& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringFunction& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedScatteringFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringFunction operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedScatteringFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringFunction operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedScatteringFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringFunction operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedScatteringFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringFunction operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedScatteringFunction operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedScatteringFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedScatteringFunction& operator+=( const TabulatedScatteringFunction& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedScatteringFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedScatteringFunction& operator-=( const TabulatedScatteringFunction& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedScatteringFunction and TabulatedScatteringFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedScatteringFunction operator+( const TabulatedScatteringFunction& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedScatteringFunction and TabulatedScatteringFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedScatteringFunction operator-( const TabulatedScatteringFunction& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedScatteringFunction& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedScatteringFunction& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedScatteringFunction addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedScatteringFunction operator+( double left, const TabulatedScatteringFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedScatteringFunction subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedScatteringFunction operator-( double left, const TabulatedScatteringFunction& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedScatteringFunction multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedScatteringFunction operator*( double left, const TabulatedScatteringFunction& right ) {

    return right * left;
  }

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
