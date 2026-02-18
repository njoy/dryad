#ifndef NJOY_DRYAD_TABULATEDSCATTERINGFUNCTION
#define NJOY_DRYAD_TABULATEDSCATTERINGFUNCTION

// system includes
#include <vector>

// other includes
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief A scattering function table
   */
  class TabulatedScatteringFunction :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "njoy/dryad/TabulatedScatteringFunction/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the inverse length values
     */
    const std::vector< double >& inverseLengths() const {

      return this->x();
    }

    /**
     *  @brief Return the scattering function values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower inverse length limit
     */
    double lowerInverseLengthLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper inverse length limit
     */
    double upperInverseLengthLimit() const {

      return this->x().back();
    }

    /**
     *  @brief Return the inverse length value associated to an energy,cosine pair
     *
     *  @param energy   the incident photon energy
     *  @param cosine   the outgoing photon cosine
     */
    double inverseLength( double energy, double cosine ) const {

      const double constant = 1e-10 * constants::e / constants::h / constants::c; // units: 1 / eV / angstrom
      return constant * energy * std::sqrt( 0.5 * ( 1 - cosine ) );
    }

    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    /**
     *  @brief Evaluate the scattering function for an energy,cosine pair
     *
     *  @param energy   the incident photon energy
     *  @param cosine   the outgoing photon cosine
     */
    double operator()( double energy, double cosine ) const {

      return this->operator()( std::min( this->inverseLength( energy, cosine ),
                                         this->inverseLengths().back() ) );
    }

    /**
     *  @brief Return a linearised scattering function table
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

} // dryad namespace
} // njoy namespace

#endif
