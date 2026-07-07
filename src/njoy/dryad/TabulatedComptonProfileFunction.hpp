#ifndef NJOY_DRYAD_TABULATEDCOMPTONPROFILEFUNCTION
#define NJOY_DRYAD_TABULATEDCOMPTONPROFILEFUNCTION

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  // forward declarations
  class TabulatedComptonProfile;

  /**
   *  @class
   *  @brief A tabulated Compton profile distribution for photoatomic data
   */
  class TabulatedComptonProfileFunction :
      protected scion::math::InterpolationTable< double, double > {

    /* friend declaration */

    friend TabulatedComptonProfile;

    /* constructor */

    /**
     *  @brief Private constructor
     *
     *  @param table   the interpolation table
     */
    TabulatedComptonProfileFunction( InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ) {}

  protected:

    /**
     *  @brief Calculate a cdf from the distribution function
     */
    TabulatedComptonProfileFunction calculateCdf( bool set_cdf_to_one = false ) const {

      std::vector< double > cdf = this->cumulativeIntegral();
      if ( set_cdf_to_one ) {

        cdf.back() = 1.;
      }
      return TabulatedComptonProfileFunction( this->momentum(),
                                              std::move( cdf ),
                                              this->boundaries(),
                                              this->interpolants() );
    }

  public:

    /* type aliases */

    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    TabulatedComptonProfileFunction() = default;

    TabulatedComptonProfileFunction( const TabulatedComptonProfileFunction& ) = default;
    TabulatedComptonProfileFunction( TabulatedComptonProfileFunction&& ) = default;

    TabulatedComptonProfileFunction& operator=( const TabulatedComptonProfileFunction& ) = default;
    TabulatedComptonProfileFunction& operator=( TabulatedComptonProfileFunction&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param momentum       the momentum values
     *  @param values         the probability values
     *  @param boundaries     the boundaries of the interpolation regions
     *  @param interpolants   the interpolation types of the interpolation regions
     */
    TabulatedComptonProfileFunction(
        std::vector< double > momentum,
        std::vector< double > values,
        std::vector< std::size_t > boundaries,
        std::vector< InterpolationType > interpolants ) :
      InterpolationTable( std::move( momentum ), std::move( values ),
                          std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief Constructor for a probability using a single interpolation zone
     *
     *  @param momentum       the momentum values
     *  @param values         the probability values
     *  @param interpolant    the interpolation type of the data (default lin-lin)
     */
    TabulatedComptonProfileFunction(
        std::vector< double > momentum,
        std::vector< double > values,
        InterpolationType interpolant = InterpolationType::LinearLinear ) :
      InterpolationTable( std::move( momentum ), std::move( values ), interpolant ) {}

    /* methods */

    /**
     *  @brief Return the momentum values
     */
    const std::vector< double >& momentum() const {

      return this->x();
    }

    /**
     *  @brief Return the probability values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower momentum limit
     */
    double lowerMomentumLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper momentum limit
     */
    double upperMomentumLimit() const {

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
     *  @brief Return a linearised Compton profile table
     *
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedComptonProfileFunction linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedComptonProfileFunction( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedComptonProfileFunction and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedComptonProfileFunction and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedComptonProfileFunction and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedComptonProfileFunction and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedComptonProfileFunction operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedComptonProfileFunction operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedComptonProfileFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfileFunction&
    operator+=( const TabulatedComptonProfileFunction& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedComptonProfileFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfileFunction&
    operator-=( const TabulatedComptonProfileFunction& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedComptonProfileFunction addition
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfileFunction
    operator+( const TabulatedComptonProfileFunction& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedComptonProfileFunction subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedComptonProfileFunction
    operator-( const TabulatedComptonProfileFunction& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedComptonProfileFunction& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedComptonProfileFunction& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedComptonProfileFunction
  operator+( double left, const TabulatedComptonProfileFunction& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedComptonProfileFunction
  operator-( double left, const TabulatedComptonProfileFunction& right ) {

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
  inline TabulatedComptonProfileFunction
  operator*( double left, const TabulatedComptonProfileFunction& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
