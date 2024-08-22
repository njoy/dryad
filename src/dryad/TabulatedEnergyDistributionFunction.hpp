#ifndef NJOY_DRYAD_TABULATEDENERGYDISTRIBUTIONFUNCTION
#define NJOY_DRYAD_TABULATEDENERGYDISTRIBUTIONFUNCTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An energy distribution function using tabulated data
   */
  class TabulatedEnergyDistributionFunction :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/TabulatedEnergyDistributionFunction/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const noexcept {

      return this->x();
    }

    /**
     *  @brief Return the probability values
     */
    const std::vector< double >& values() const noexcept {

      return this->y();
    }

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const noexcept {

      return this->x().front();
    }

    /**
     *  @brief Return the upper energy limit
     */
    double upperEnergyLimit() const noexcept {

      return this->x().back();
    }

    using InterpolationTable::boundaries;
    using InterpolationTable::interpolants;
    using InterpolationTable::numberPoints;
    using InterpolationTable::numberRegions;
    using InterpolationTable::isLinearised;

    using InterpolationTable::operator();

    /**
     *  @brief Return a linearised energy distribution table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedEnergyDistributionFunction linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedEnergyDistributionFunction( InterpolationTable::linearise( tolerance ) );
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
