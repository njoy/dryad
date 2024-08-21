#ifndef NJOY_DRYAD_TABULATEDENERGYDISTRIBUTION
#define NJOY_DRYAD_TABULATEDENERGYDISTRIBUTION

// system includes
#include <vector>

// other includes
#include "dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {

  /**
   *  @class
   *  @brief An energy distribution table
   */
  class TabulatedEnergyDistribution :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "dryad/TabulatedEnergyDistribution/src/ctor.hpp"

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
    TabulatedEnergyDistribution linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedEnergyDistribution( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistribution& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistribution& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistribution& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistribution& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedEnergyDistribution and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistribution operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedEnergyDistribution and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistribution operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedEnergyDistribution and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistribution operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedEnergyDistribution and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedEnergyDistribution operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedEnergyDistribution operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedEnergyDistribution addition
     *
     *  @param[in] right    the table
     */
    TabulatedEnergyDistribution& operator+=( const TabulatedEnergyDistribution& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedEnergyDistribution subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedEnergyDistribution& operator-=( const TabulatedEnergyDistribution& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedEnergyDistribution and TabulatedEnergyDistribution addition
     *
     *  @param[in] right    the table
     */
    TabulatedEnergyDistribution operator+( const TabulatedEnergyDistribution& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedEnergyDistribution and TabulatedEnergyDistribution subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedEnergyDistribution operator-( const TabulatedEnergyDistribution& right ) const {

      return InterpolationTable::operator-( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedEnergyDistribution addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedEnergyDistribution operator+( double left, const TabulatedEnergyDistribution& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedEnergyDistribution subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedEnergyDistribution operator-( double left, const TabulatedEnergyDistribution& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedEnergyDistribution multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedEnergyDistribution operator*( double left, const TabulatedEnergyDistribution& right ) {

    return right * left;
  }

} // dryad namespace
} // njoy namespace

#endif
