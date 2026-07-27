#ifndef NJOY_DRYAD_RESONANCES_TABULATEDBACKGROUND
#define NJOY_DRYAD_RESONANCES_TABULATEDBACKGROUND

// system includes
#include <complex>
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
   *  @brief A channel background using tabulated data
   *
   *  The energy values are given in eV and the background values
   *  are dimensionless complex values.
   *
   *  @todo c++20 : use defaulted comparison operators
   */
  class TabulatedBackground :
      protected scion::math::InterpolationTable< double, std::complex< double > > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "njoy/dryad/resonances/TabulatedBackground/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief Return the background values
     */
    const std::vector< std::complex< double > >& values() const {

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
    TabulatedBackground linearise( double tolerance = constants::linearisation::tolerance ) const {

      auto has_converged = [&] ( const std::complex< double >& trial,
                                 const std::complex< double >& reference,
                                 const double&, const double&,
                                 const std::complex< double >&, const std::complex< double >& ) {

        if ( trial == reference ) {

          return true;
        }

        const auto diff_real = std::abs( trial.real() - reference.real() );
        const auto norm_real = std::abs( reference.real() );
        const auto diff_imag = std::abs( trial.imag() - reference.imag() );
        const auto norm_imag = std::abs( reference.imag() );
        return diff_real < std::max( tolerance * norm_real, njoy::constants::linearisation::threshold ) &&
               diff_imag < std::max( tolerance * norm_imag, njoy::constants::linearisation::threshold );
      };

      auto table = InterpolationTable::linearise( has_converged );
      return TabulatedBackground( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedBackground& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedBackground& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedBackground& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedBackground& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedBackground and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedBackground operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedBackground and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedBackground operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedBackground and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedBackground operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedBackground and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedBackground operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedBackground operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedBackground addition
     *
     *  @param[in] right    the table
     */
    TabulatedBackground& operator+=( const TabulatedBackground& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedBackground subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedBackground& operator-=( const TabulatedBackground& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedBackground and TabulatedBackground addition
     *
     *  @param[in] right    the table
     */
    TabulatedBackground operator+( const TabulatedBackground& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedBackground and TabulatedBackground subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedBackground operator-( const TabulatedBackground& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedBackground& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedBackground& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedBackground addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedBackground operator+( double left, const TabulatedBackground& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedBackground subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedBackground operator-( double left, const TabulatedBackground& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedBackground multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedBackground operator*( double left, const TabulatedBackground& right ) {

    return right * left;
  }

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
