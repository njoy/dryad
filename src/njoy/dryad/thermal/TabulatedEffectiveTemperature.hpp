#ifndef NJOY_DRYAD_THERMAL_TABULATEDEFFECTIVETEMPERATURE
#define NJOY_DRYAD_THERMAL_TABULATEDEFFECTIVETEMPERATURE

// system includes
#include <vector>

// other includes
#include "njoy/dryad/type-aliases.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief An effective temperature table
   *
   *  This is a table of effective temperatures (given in K) for the
   *  short collision-time approximation given as a function of moderator
   *  temperature (given in K) for a scattering atom.
   */
  class TabulatedEffectiveTemperature  :
      protected scion::math::InterpolationTable< double, double > {

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    #include "njoy/dryad/thermal/TabulatedEffectiveTemperature/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the moderator temperature values
     */
    const std::vector< double >& moderatorTemperatures() const {

      return this->x();
    }

    /**
     *  @brief Return the effetive temperature values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     *  @brief Return the lower moderator temperature limit
     */
    double lowerModeratorTemperatureLimit() const {

      return this->x().front();
    }

    /**
     *  @brief Return the upper moderator temperature limit
     */
    double upperModeratorTemperatureLimit() const {

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
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedEffectiveTemperature linearise( ToleranceConvergence tolerance = {} ) const {

      return TabulatedEffectiveTemperature( InterpolationTable::linearise( tolerance ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedEffectiveTemperature& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedEffectiveTemperature& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedEffectiveTemperature& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedEffectiveTemperature& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedEffectiveTemperature and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedEffectiveTemperature operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedEffectiveTemperature and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedEffectiveTemperature operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedEffectiveTemperature and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedEffectiveTemperature operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedEffectiveTemperature and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedEffectiveTemperature operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedEffectiveTemperature operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedEffectiveTemperature addition
     *
     *  @param[in] right    the table
     */
    TabulatedEffectiveTemperature& operator+=( const TabulatedEffectiveTemperature& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedEffectiveTemperature subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedEffectiveTemperature& operator-=( const TabulatedEffectiveTemperature& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedEffectiveTemperature and TabulatedEffectiveTemperature addition
     *
     *  @param[in] right    the table
     */
    TabulatedEffectiveTemperature operator+( const TabulatedEffectiveTemperature& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedEffectiveTemperature and TabulatedEffectiveTemperature subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedEffectiveTemperature operator-( const TabulatedEffectiveTemperature& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedEffectiveTemperature& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedEffectiveTemperature& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedEffectiveTemperature addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedEffectiveTemperature operator+( double left, const TabulatedEffectiveTemperature& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedEffectiveTemperature subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedEffectiveTemperature operator-( double left, const TabulatedEffectiveTemperature& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedEffectiveTemperature multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedEffectiveTemperature operator*( double left, const TabulatedEffectiveTemperature& right ) {

    return right * left;
  }

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
