#ifndef NJOY_DRYAD_RESONANCES_TABULATEDLEVELSPACING
#define NJOY_DRYAD_RESONANCES_TABULATEDLEVELSPACING

// system includes
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
   *  @brief A tabulated average level spacing <D>(E) for one spin group
   *
   *  The energy values are in eV and the level spacings are in eV.
   */

  class TabulatedLevelSpacing :
    protected scion::math::InterpolationTable< double, double > {

    /* constructor */

    /**
     *  @brief Private constructor
     *  @param[in] table    the interpolation table
     */
    TabulatedLevelSpacing( InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ) {}

  public:

    /* type aliases */
    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposed only)
     */
    TabulatedLevelSpacing() = default;

    TabulatedLevelSpacing( const TabulatedLevelSpacing& ) = default;
    TabulatedLevelSpacing( TabulatedLevelSpacing&& ) = default;

    TabulatedLevelSpacing& operator=( const TabulatedLevelSpacing& ) = default;
    TabulatedLevelSpacing& operator=( TabulatedLevelSpacing&& ) = default;

    /**
     *  @brief  Constructor
     *
     *  @param[in]  energies        the energy values (eV)
     *  @param[in]  spacings        the average level spacing values (eV)
     *  @param[in]  boundaries      the boundaries of the interpolation regions
     *  @param[in]  interpolants    the interpolation types of the interpolation regions
     */
    TabulatedLevelSpacing( std::vector< double > energies,
                           std::vector< double > spacings,
                           std::vector< std::size_t > boundaries,
                           std::vector< InterpolationType > interpolants ) :
      InterpolationTable( std::move( energies ), std::move( spacings ),
                          std::move( boundaries ), std::move( interpolants ) ) {}

    /**
     *  @brief  Constructor for a single interpolation zone
     *
     *  @param[in]  energies        the energy values (eV)
     *  @param[in]  spacings        the average level spacing values (eV)
     *  @param[in]  interpolant     the interpolation type (default lin-lin)
     */
    TabulatedLevelSpacing( std::vector< double > energies,
                           std::vector< double > spacings,
                           InterpolationType interpolant = InterpolationType::LinearLinear ) :
      InterpolationTable( std::move( energies ), std::move( spacings ), interpolant ) {}

    /* methods */

    /**
     *  @brief returns the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief  Return the average level spacing values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     * @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->x().front();
    }

    /**
     * @brief Return the upper energy limit
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
     *  @brief Return a linearised level spacing table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedLevelSpacing linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedLevelSpacing( std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedLevelSpacing& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedLevelSpacing& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedLevelSpacing& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedLevelSpacing& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedLevelSpacing and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedLevelSpacing operator+( double right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedLevelSpacing and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedLevelSpacing operator-( double right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief TabulatedLevelSpacing and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedLevelSpacing operator*( double right ) const {

      return InterpolationTable::operator*( right );
    }

    /**
     *  @brief TabulatedLevelSpacing and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedLevelSpacing operator/( double right ) const {

      return InterpolationTable::operator/( right );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedLevelSpacing operator-() const {

      return InterpolationTable::operator-();
    }

    /**
     *  @brief Inplace TabulatedLevelSpacing addition
     *
     *  @param[in] right    the table
     */
    TabulatedLevelSpacing& operator+=( const TabulatedLevelSpacing& right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedLevelSpacing subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedLevelSpacing& operator-=( const TabulatedLevelSpacing& right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedLevelSpacing and TabulatedLevelSpacing addition
     *
     *  @param[in] right    the table
     */
    TabulatedLevelSpacing operator+( const TabulatedLevelSpacing& right ) const {

      return InterpolationTable::operator+( right );
    }

    /**
     *  @brief TabulatedLevelSpacing and TabulatedLevelSpacing subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedLevelSpacing operator-( const TabulatedLevelSpacing& right ) const {

      return InterpolationTable::operator-( right );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedLevelSpacing& right ) const {

      return InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedLevelSpacing& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedLevelSpacing addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedLevelSpacing operator+( double left, const TabulatedLevelSpacing& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedLevelSpacing subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedLevelSpacing operator-( double left, const TabulatedLevelSpacing& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedLevelSpacing multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedLevelSpacing operator*( double left, const TabulatedLevelSpacing& right ) {

    return right * left;
  }

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
