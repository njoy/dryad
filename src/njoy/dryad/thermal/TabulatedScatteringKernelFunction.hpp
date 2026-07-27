#ifndef NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGKERNELFUNCTION
#define NJOY_DRYAD_THERMAL_TABULATEDSCATTERINGKERNELFUNCTION

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
  class TabulatedScatteringKernelFunction  :
      protected scion::math::InterpolationTable< double, double > {

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] table   the interpolation table
     */
    TabulatedScatteringKernelFunction( InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ) {}

  public:

    /* type aliases */

    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedScatteringKernelFunction() = default;

    TabulatedScatteringKernelFunction( const TabulatedScatteringKernelFunction& ) = default;
    TabulatedScatteringKernelFunction( TabulatedScatteringKernelFunction&& ) = default;

    TabulatedScatteringKernelFunction& operator=( const TabulatedScatteringKernelFunction& ) = default;
    TabulatedScatteringKernelFunction& operator=( TabulatedScatteringKernelFunction&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] momentumTransfers   the momentum transfer values
     *  @param[in] values              the scattering function values
     *  @param[in] boundaries          the boundaries of the interpolation regions
     *  @param[in] interpolants        the interpolation types of the interpolation regions
     */
    TabulatedScatteringKernelFunction( std::vector< double > momentumTransfers,
                                       std::vector< double > values,
                                       std::vector< std::size_t > boundaries,
                                       std::vector< InterpolationType > interpolants ) :
      InterpolationTable( std::move( momentumTransfers ), std::move( values ),
                          std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for a scattering function table using a single interpolation zone
     *
     *  @param[in] momentumTransfers   the momentum transfer values
     *  @param[in] values              the effective temperature values
     *  @param[in] interpolant         the interpolation type of the data (default lin-lin)
     */
    TabulatedScatteringKernelFunction( std::vector< double > momentumTransfers,
                                       std::vector< double > values,
                                       InterpolationType interpolant = InterpolationType::LinearLinear ) :
      InterpolationTable( std::move( momentumTransfers ), std::move( values ), interpolant ) {}

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
    TabulatedScatteringKernelFunction linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedScatteringKernelFunction( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringKernelFunction& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringKernelFunction& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringKernelFunction& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringKernelFunction& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedScatteringKernelFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringKernelFunction operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedScatteringKernelFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringKernelFunction operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedScatteringKernelFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringKernelFunction operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedScatteringKernelFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedScatteringKernelFunction operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedScatteringKernelFunction operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedScatteringKernelFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedScatteringKernelFunction& operator+=( const TabulatedScatteringKernelFunction& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedScatteringKernelFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedScatteringKernelFunction& operator-=( const TabulatedScatteringKernelFunction& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedScatteringKernelFunction and TabulatedScatteringKernelFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedScatteringKernelFunction operator+( const TabulatedScatteringKernelFunction& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedScatteringKernelFunction and TabulatedScatteringKernelFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedScatteringKernelFunction operator-( const TabulatedScatteringKernelFunction& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedScatteringKernelFunction& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedScatteringKernelFunction& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedScatteringKernelFunction addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedScatteringKernelFunction operator+( double left, const TabulatedScatteringKernelFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedScatteringKernelFunction subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedScatteringKernelFunction operator-( double left, const TabulatedScatteringKernelFunction& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedScatteringKernelFunction multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedScatteringKernelFunction operator*( double left, const TabulatedScatteringKernelFunction& right ) {

    return right * left;
  }

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
