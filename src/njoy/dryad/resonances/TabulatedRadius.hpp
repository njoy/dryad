#ifndef NJOY_DRYAD_RESONANCES_TABULATEDRADIUS
#define NJOY_DRYAD_RESONANCES_TABULATEDRADIUS

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
   *  @brief A radius table
   *
   *  The radius is given in femto meters (fm).
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class TabulatedRadius :
      protected scion::math::InterpolationTable< double, double > {

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] table   the interpolation table
     */
    TabulatedRadius( InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ) {}

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedRadius() = default;

    TabulatedRadius( const TabulatedRadius& ) = default;
    TabulatedRadius( TabulatedRadius&& ) = default;

    TabulatedRadius& operator=( const TabulatedRadius& ) = default;
    TabulatedRadius& operator=( TabulatedRadius&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] energies       the energy values
     *  @param[in] values         the radius values
     *  @param[in] boundaries     the boundaries of the interpolation regions
     *  @param[in] interpolants   the interpolation types of the interpolation regions
     */
    TabulatedRadius( std::vector< double > energies,
                     std::vector< double > values,
                     std::vector< std::size_t > boundaries,
                     std::vector< InterpolationType > interpolants ) :
      InterpolationTable( std::move( energies ), std::move( values ),
                          std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for a radius using a single interpolation zone
     *
     *  @param[in] energies       the energy values
     *  @param[in] values         the radius values
     *  @param[in] interpolant    the interpolation type of the data (default lin-lin)
     */
    TabulatedRadius( std::vector< double > energies,
                     std::vector< double > values,
                     InterpolationType interpolant = InterpolationType::LinearLinear ) :
      InterpolationTable( std::move( energies ), std::move( values ), interpolant ) {}

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief Return the radius values
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
     *  @brief Return a linearised radius table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedRadius linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedRadius( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedRadius and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedRadius and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedRadius and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedRadius and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedRadius operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedRadius operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedRadius addition
     *
     *  @param[in] right    the table
     */
    TabulatedRadius& operator+=( const TabulatedRadius& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedRadius subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedRadius& operator-=( const TabulatedRadius& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedRadius and TabulatedRadius addition
     *
     *  @param[in] right    the table
     */
    TabulatedRadius operator+( const TabulatedRadius& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedRadius and TabulatedRadius subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedRadius operator-( const TabulatedRadius& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedRadius& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedRadius& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedRadius addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedRadius operator+( double left, const TabulatedRadius& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedRadius subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedRadius operator-( double left, const TabulatedRadius& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedRadius multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedRadius operator*( double left, const TabulatedRadius& right ) {

    return right * left;
  }

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
