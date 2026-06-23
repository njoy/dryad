#ifndef NJOY_DRYAD_TABULATEDENERGYDISTRIBUTIONFUNCTION
#define NJOY_DRYAD_TABULATEDENERGYDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  // forward declarations
  class TabulatedEnergyDistribution;

  /**
   *  @class
   *  @brief An energy distribution function using tabulated data
   */
  class TabulatedEnergyDistributionFunction :
      protected scion::math::InterpolationTable< double, double > {

    /* friend declaration */

    friend TabulatedEnergyDistribution;

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param table   the interpolation table
     */
    TabulatedEnergyDistributionFunction( InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ) {}

  protected:

    /**
     *  @brief Calculate a cdf from the distribution function
     */
    TabulatedEnergyDistributionFunction calculateCdf( bool set_cdf_to_one = false ) const {

      std::vector< double > cdf = this->cumulativeIntegral();
      if ( set_cdf_to_one ) {

        cdf.back() = 1.;
      }
      return TabulatedEnergyDistributionFunction( this->energies(), std::move( cdf ),
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
    TabulatedEnergyDistributionFunction() = default;

    TabulatedEnergyDistributionFunction( const TabulatedEnergyDistributionFunction& ) = default;
    TabulatedEnergyDistributionFunction( TabulatedEnergyDistributionFunction&& ) = default;

    TabulatedEnergyDistributionFunction& operator=( const TabulatedEnergyDistributionFunction& ) = default;
    TabulatedEnergyDistributionFunction& operator=( TabulatedEnergyDistributionFunction&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param energies       the energy values
     *  @param values         the probability values
     *  @param boundaries     the boundaries of the interpolation regions
     *  @param interpolants   the interpolation types of the interpolation regions
     */
    TabulatedEnergyDistributionFunction(
        std::vector< double > energies,
        std::vector< double > values,
        std::vector< std::size_t > boundaries,
        std::vector< InterpolationType > interpolants ) :
      InterpolationTable( std::move( energies ), std::move( values ),
                          std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for an energy distirbution using a single interpolation zone
     *
     *  @param energies       the energy values
     *  @param values         the probability values
     *  @param interpolant    the interpolation type of the data (default lin-lin)
     */
    TabulatedEnergyDistributionFunction(
        std::vector< double > energies,
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
     *  @brief Return the probability values
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
     *  @brief Return a linearised energy distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedEnergyDistributionFunction linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedEnergyDistributionFunction( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistributionFunction& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistributionFunction& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistributionFunction& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistributionFunction& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedEnergyDistributionFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistributionFunction operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedEnergyDistributionFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistributionFunction operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedEnergyDistributionFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistributionFunction operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedEnergyDistributionFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistributionFunction operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedEnergyDistributionFunction operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedEnergyDistributionFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedEnergyDistributionFunction&
    operator+=( const TabulatedEnergyDistributionFunction& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedEnergyDistributionFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedEnergyDistributionFunction&
    operator-=( const TabulatedEnergyDistributionFunction& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedEnergyDistributionFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedEnergyDistributionFunction
    operator+( const TabulatedEnergyDistributionFunction& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedEnergyDistributionFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedEnergyDistributionFunction
    operator-( const TabulatedEnergyDistributionFunction& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedEnergyDistributionFunction& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedEnergyDistributionFunction& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedEnergyDistributionFunction
  operator+( double left, const TabulatedEnergyDistributionFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedEnergyDistributionFunction
  operator-( double left, const TabulatedEnergyDistributionFunction& right ) {

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
  inline TabulatedEnergyDistributionFunction
  operator*( double left, const TabulatedEnergyDistributionFunction& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
