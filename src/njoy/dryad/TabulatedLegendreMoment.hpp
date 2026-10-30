#ifndef NJOY_DRYAD_TABULATEDLEGENDREMOMENT
#define NJOY_DRYAD_TABULATEDLEGENDREMOMENT

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A Legendre moment table
   */
  class TabulatedLegendreMoment :
      protected scion::math::InterpolationTable< double, double > {

    /* fields */

    std::size_t order_;

    /* auxiliary functions */

    static void verifyOrder( std::size_t left, std::size_t right ) {

      if ( left != right ) {

        Log::error( "Cannot perform operation on tabulated Legendre moments of different orders" );
        throw std::exception();
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] table   the interpolation table
     */
    TabulatedLegendreMoment( std::size_t order, InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ),
      order_( std::move( order ) ) {}

  public:

    /* type aliases */

    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedLegendreMoment() = default;

    TabulatedLegendreMoment( const TabulatedLegendreMoment& ) = default;
    TabulatedLegendreMoment( TabulatedLegendreMoment&& ) = default;

    TabulatedLegendreMoment& operator=( const TabulatedLegendreMoment& ) = default;
    TabulatedLegendreMoment& operator=( TabulatedLegendreMoment&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] order          the order of the Legendre moment
     *  @param[in] energies       the energy values
     *  @param[in] values         the Legendre moment values
     *  @param[in] boundaries     the boundaries of the interpolation regions
     *  @param[in] interpolants   the interpolation types of the interpolation regions
     *  @param[in] curate         flag to indicate whether or not to curate the data (default: false)
     */
    TabulatedLegendreMoment( std::size_t order,
                             std::vector< double > energies,
                             std::vector< double > values,
                             std::vector< std::size_t > boundaries,
                             std::vector< InterpolationType > interpolants,
                             bool curate = false ) :
      InterpolationTable( std::move( energies ), std::move( values ),
                          std::move( boundaries ), std::move( interpolants ),
                          curate ),
      order_( std::move( order ) ) {}

    /**
     *  @brief Constructor using a single interpolation zone
     *
     *  @param[in] order          the order of the Legendre moment
     *  @param[in] energies       the energy values
     *  @param[in] values         the Legendre moment values
     *  @param[in] interpolant    the interpolation type of the data (default lin-lin)
     *  @param[in] curate         flag to indicate whether or not to curate the data (default: false)
     */
    TabulatedLegendreMoment( std::size_t order,
                             std::vector< double > energies,
                             std::vector< double > values,
                             InterpolationType interpolant = InterpolationType::LinearLinear,
                             bool curate = false ) :
      InterpolationTable( std::move( energies ), std::move( values ), interpolant, curate ),
      order_( std::move( order ) ) {}

    /* methods */

    /**
     *  @brief Return the order of the Legendre moment
     */
    std::size_t order() const {

      return this->order_;
    }

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief Return the Legendre moment values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->lowerLimit();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const {

      return this->upperLimit();
    }

    using InterpolationTable::x;
    using InterpolationTable::y;
    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;
    using InterpolationTable::isCurated;
    using InterpolationTable::curate;

    using InterpolationTable::operator();
    using InterpolationTable::lowerLimit;
    using InterpolationTable::upperLimit;

    /**
     *  @brief Return a linearised Legendre moment table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedLegendreMoment linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedLegendreMoment( this->order(), std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedLegendreMoment& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedLegendreMoment& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedLegendreMoment& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedLegendreMoment& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedLegendreMoment and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedLegendreMoment operator+( double right ) const {

      return TabulatedLegendreMoment( this->order(), InterpolationTable::operator+( right ) );
    }

    /**
     *  @brief TabulatedLegendreMoment and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedLegendreMoment operator-( double right ) const {

      return TabulatedLegendreMoment( this->order(), InterpolationTable::operator-( right ) );
    }

    /**
     *  @brief TabulatedLegendreMoment and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedLegendreMoment operator*( double right ) const {

      return TabulatedLegendreMoment( this->order(), InterpolationTable::operator*( right ) );
    }

    /**
     *  @brief TabulatedLegendreMoment and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedLegendreMoment operator/( double right ) const {

      return TabulatedLegendreMoment( this->order(), InterpolationTable::operator/( right ) );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedLegendreMoment operator-() const {

      return TabulatedLegendreMoment( this->order(), InterpolationTable::operator-() );
    }

    /**
     *  @brief Inplace TabulatedLegendreMoment addition
     *
     *  @param[in] right    the table
     */
    TabulatedLegendreMoment& operator+=( const TabulatedLegendreMoment& right ) {

      verifyOrder( this->order(), right.order() );

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedLegendreMoment subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedLegendreMoment& operator-=( const TabulatedLegendreMoment& right ) {

      verifyOrder( this->order(), right.order() );

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedLegendreMoment and TabulatedLegendreMoment addition
     *
     *  @param[in] right    the table
     */
    TabulatedLegendreMoment operator+( const TabulatedLegendreMoment& right ) const {

      verifyOrder( this->order(), right.order() );

      return TabulatedLegendreMoment( this->order(), InterpolationTable::operator+( right ) );
    }

    /**
     *  @brief TabulatedLegendreMoment and TabulatedLegendreMoment subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedLegendreMoment operator-( const TabulatedLegendreMoment& right ) const {

      verifyOrder( this->order(), right.order() );

      return TabulatedLegendreMoment( this->order(), InterpolationTable::operator-( right ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedLegendreMoment& right ) const {

      return this->order() == right.order() && InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedLegendreMoment& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedLegendreMoment addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedLegendreMoment operator+( double left, const TabulatedLegendreMoment& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedLegendreMoment subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedLegendreMoment operator-( double left, const TabulatedLegendreMoment& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedLegendreMoment multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedLegendreMoment operator*( double left, const TabulatedLegendreMoment& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
