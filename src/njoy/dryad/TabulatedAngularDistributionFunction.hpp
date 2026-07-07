#ifndef NJOY_DRYAD_TABULATEDANGULARDISTRIBUTIONFUNCTION
#define NJOY_DRYAD_TABULATEDANGULARDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  // forward declarations
  class LegendreAngularDistributionFunction;
  class TabulatedAngularDistribution;
  class MixedAngularDistribution;

  /**
   *  @class
   *  @brief An angular distribution function using tabulated data
   */
  class TabulatedAngularDistributionFunction :
      protected scion::math::InterpolationTable< double, double > {

    /* friend declaration */

    friend LegendreAngularDistributionFunction;
    friend TabulatedAngularDistribution;
    friend MixedAngularDistribution;

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param[in] table   the interpolation table
     */
    TabulatedAngularDistributionFunction( InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ) {}

  protected:

    /**
     *  @brief Calculate a cdf from the distribution function
     */
    TabulatedAngularDistributionFunction calculateCdf( bool set_cdf_to_one = false ) const {

      std::vector< double > cdf = this->cumulativeIntegral();
      if ( set_cdf_to_one ) {

        cdf.back() = 1.;
      }
      return TabulatedAngularDistributionFunction( this->cosines(), std::move( cdf ),
                                                   this->boundaries(), this->interpolants() );
    }

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedAngularDistributionFunction() = default;

    TabulatedAngularDistributionFunction( const TabulatedAngularDistributionFunction& ) = default;
    TabulatedAngularDistributionFunction( TabulatedAngularDistributionFunction&& ) = default;

    TabulatedAngularDistributionFunction& operator=( const TabulatedAngularDistributionFunction& ) = default;
    TabulatedAngularDistributionFunction& operator=( TabulatedAngularDistributionFunction&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] cosines        the cosine values
     *  @param[in] values         the probability values
     *  @param[in] boundaries     the boundaries of the interpolation regions
     *  @param[in] interpolants   the interpolation types of the interpolation regions
     */
    TabulatedAngularDistributionFunction(
        std::vector< double > cosines,
        std::vector< double > values,
        std::vector< std::size_t > boundaries,
        std::vector< InterpolationType > interpolants ) :
      InterpolationTable( std::move( cosines ), std::move( values ),
                          std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for a probability using a single interpolation zone
     *
     *  @param[in] cosines        the cosine values
     *  @param[in] values         the probability values
     *  @param[in] interpolant    the interpolation type of the data (default lin-lin)
     */
    TabulatedAngularDistributionFunction(
        std::vector< double > cosines,
        std::vector< double > values,
        InterpolationType interpolant = InterpolationType::LinearLinear ) :
      InterpolationTable( std::move( cosines ), std::move( values ), interpolant ) {}

    /* methods */

    /**
     *  @brief Return the cosine values
     */
    const std::vector< double >& cosines() const {

      return this->x();
    }

    /**
     *  @brief Return the probability values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower cosine limit
     */
    double lowerCosineLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper cosine limit
     */
    double upperCosineLimit() const {

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
    using InterpolationTable::mean;

    /**
     *  @brief Normalise the distribution function
     */
    void normalise() {

      this->operator/=( this->integral() );
    }

    /**
     *  @brief Return a linearised angular distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedAngularDistributionFunction linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedAngularDistributionFunction( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAngularDistributionFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAngularDistributionFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedAngularDistributionFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedAngularDistributionFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAngularDistributionFunction operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedAngularDistributionFunction operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedAngularDistributionFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistributionFunction&
    operator+=( const TabulatedAngularDistributionFunction& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedAngularDistributionFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistributionFunction&
    operator-=( const TabulatedAngularDistributionFunction& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAngularDistributionFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistributionFunction
    operator+( const TabulatedAngularDistributionFunction& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedAngularDistributionFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAngularDistributionFunction
    operator-( const TabulatedAngularDistributionFunction& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedAngularDistributionFunction& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedAngularDistributionFunction& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAngularDistributionFunction
  operator+( double left, const TabulatedAngularDistributionFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAngularDistributionFunction
  operator-( double left, const TabulatedAngularDistributionFunction& right ) {

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
  inline TabulatedAngularDistributionFunction
  operator*( double left, const TabulatedAngularDistributionFunction& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
