#ifndef NJOY_DRYAD_TABULATEDMULTIPLICITY
#define NJOY_DRYAD_TABULATEDMULTIPLICITY

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  class PolynomialMultiplicity;

  /**
   *  @class
   *  @brief A multiplicity table
   */
  class TabulatedMultiplicity :
      protected scion::math::InterpolationTable< double, double > {

    friend PolynomialMultiplicity;

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param table   the interpolation table
     */
    TabulatedMultiplicity( InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ) {}

  public:

    /* type aliases */

    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedMultiplicity() = default;

    TabulatedMultiplicity( const TabulatedMultiplicity& ) = default;
    TabulatedMultiplicity( TabulatedMultiplicity&& ) = default;

    TabulatedMultiplicity& operator=( const TabulatedMultiplicity& ) = default;
    TabulatedMultiplicity& operator=( TabulatedMultiplicity&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param energies       the energy values
     *  @param values         the multiplicity values
     *  @param boundaries     the boundaries of the interpolation regions
     *  @param interpolants   the interpolation types of the interpolation regions
     */
    TabulatedMultiplicity( std::vector< double > energies,
                           std::vector< double > values,
                           std::vector< std::size_t > boundaries,
                           std::vector< InterpolationType > interpolants ) :
      InterpolationTable( std::move( energies ), std::move( values ),
                          std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for a multiplicity using a single interpolation zone
     *
     *  @param energies       the energy values
     *  @param values         the multiplicity values
     *  @param interpolant    the interpolation type of the data (default lin-lin)
     */
    TabulatedMultiplicity( std::vector< double > energies,
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
     *  @brief Return the multiplicity values
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
     *  @brief Return a linearised multiplicity table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedMultiplicity linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedMultiplicity( std::move( table ) );
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

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedMultiplicity& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedMultiplicity& right ) const {

      return ! this->operator==( right );
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
