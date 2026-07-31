#ifndef NJOY_DRYAD_RESONANCES_TABULATEDAVERAGEWIDTHS
#define NJOY_DRYAD_RESONANCES_TABULATEDAVERAGEWIDTHS

#include <vector>
#include <optional>
#include "njoy/constants.hpp"
#include "njoy/dryad/InterpolationType.hpp"
#include "scion/math/InterpolationTable.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @brief  A tabulated average width <Gamma_c>(E) for a single channel,
   *          together with the degrees of freedom for its chi-squared
   *          distribution
   *
   * Stores the average partial widths as a function of energy for one
   * reaction channel, as given in ENDF MF2/LRU=2, along with the integer
   * degrees of freedom for the chi-squared distribution for ladder generation:
   *
   *      Gamma_c_lambda = chi_squared(dof) * <Gamma_c> / dof
   *
   * For non-elastic channels, the stored value is the physical width directly
   * For the elastic channel, the stored value is the reduced neutron width
   * <Gamma_n^0> as given in ENDF. The physical neutron width at energy E is:
   *
   *      <Gamma_n>(E) = <Gamma_n^0>(E) * sqrt(E/E0) * P_l(E)
   *
   * where E0 is the reference energy (E0=1 eV), and P_l(E) is the neutron
   * penetrability factor for orbital angular momentum l.
   *
   * Units: energies in eV, widths in eV. DoF is dimensionless.
   *
   */
  class TabulatedAverageWidths :
    protected scion::math::InterpolationTable< double, double > {

    /* fields */

    std::optional< int > degrees_freedom_;

    /* auxiliary functions */

    static std::optional< int > combineDoF( const std::optional< int >& left, const std::optional< int >& right ) {

      if ( left.has_value() && right.has_value() ) {

        if ( left != right ) {

          Log::error( "TabulatedAverageWidths::combineDoF: conflicting degrees of freedom "
                      "values: {} and {}", left.value(), right.value() );
          throw std::exception();
        }

        return left;
      }

      return left.has_value() ? left : right;
    }

    /* constructor */

    /**
     *  @brief  Private constructor
     *
     *  @param[in]  dof     the degrees of freedom
     *  @param[in]  table   the interpolation table
     */
    TabulatedAverageWidths( std::optional< int > dof,
                            InterpolationTable< double, double > table ) :
      InterpolationTable( std::move( table ) ), degrees_freedom_( dof ) {}

  public:

    /* type aliases*/

    using InterpolationTable::XType;
    using InterpolationTable::YType;

    /* constructor */

    /**
     *  @brief  Default constructor (for pybind11 purposes only)
     */
    TabulatedAverageWidths() = default;

    TabulatedAverageWidths( const TabulatedAverageWidths& ) = default;
    TabulatedAverageWidths( TabulatedAverageWidths&& ) = default;

    TabulatedAverageWidths& operator=( const TabulatedAverageWidths& ) = default;
    TabulatedAverageWidths& operator=( TabulatedAverageWidths&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in]  dof            the degrees of freedom
     *  @param[in]  energies       the energy values (eV)
     *  @param[in]  widths         the average width values (eV)
     *  @param[in]  boundaries     the boundaries of the interpolation regions
     *  @param[in]  interpolants   the interpolation types of the interpolation regions
     */
    TabulatedAverageWidths( int dof,
                            std::vector< double > energies,
                            std::vector< double > widths,
                            std::vector< std::size_t > boundaries,
                            std::vector< InterpolationType > interpolants ) :
      TabulatedAverageWidths( std::optional< int >( dof ),
                              InterpolationTable< double, double >( std::move( energies ),
                                                                    std::move( widths ),
                                                                    std::move( boundaries ),
                                                                    std::move( interpolants ) ) ) {}

    /**
     *  @brief Constructor for a single interpolation zone
     *
     *  @param[in] dof           the degrees of freedom
     *  @param[in] energies      the energy values (eV)
     *  @param[in] widths        the average width values (eV)
     *  @param[in] interpolant   the interpolation type (default lin-lin)
     */
    TabulatedAverageWidths( int dof,
                            std::vector< double > energies,
                            std::vector< double > widths,
                            InterpolationType interpolant = InterpolationType::LinearLinear ) :
      TabulatedAverageWidths( std::optional< int >( dof ),
                              InterpolationTable< double, double >( std::move( energies ),
                                                                    std::move( widths ),
                                                                    interpolant ) ) {}

    /**
     *  @brief Constructor without the degrees of freedom
     *
     *  @param[in] energies       the energy values (eV)
     *  @param[in] widths         the average width values (eV)
     *  @param[in] boundaries     the boundaries of the interpolation regions
     *  @param[in] interpolants   the interpolation types of the interpolation regions
     */
    TabulatedAverageWidths( std::vector< double > energies,
                            std::vector< double > widths,
                            std::vector< std::size_t > boundaries,
                            std::vector< InterpolationType > interpolants ) :
      TabulatedAverageWidths( std::nullopt,
                              InterpolationTable< double, double >( std::move( energies ),
                                                                    std::move( widths ),
                                                                    std::move( boundaries ),
                                                                    std::move( interpolants ) ) ) {}

    /**
     *  @brief Constructor for a single interpolation zone without the degrees of freedom
     *
     *  @param[in] energies       the energy values (eV)
     *  @param[in] widths         the average width values (eV)
     *  @param[in] interpolant    the interpolation type (default lin-lin)
     */
    TabulatedAverageWidths( std::vector< double > energies,
                            std::vector< double > widths,
                            InterpolationType interpolant = InterpolationType::LinearLinear ) :
      TabulatedAverageWidths( std::nullopt,
                              InterpolationTable< double, double >( std::move( energies ),
                                                                    std::move( widths ),
                                                                    interpolant ) ) {}
    /* methods */

    /**
     *  @brief Return the energy values
     */
    const std::vector< double >& energies() const {

      return this->x();
    }

    /**
     *  @brief Return the average width values
     */
    const std::vector< double >& values() const {

      return this->y();
    }

    /**
     * @brief Return the degrees of freedom
     */
    const std::optional< int >& degreesOfFreedom() const {

      return this->degrees_freedom_;
    }

    /**
     * @brief Return the degrees of freedom
     */
    std::optional< int >& degreesOfFreedom() {

      return this->degrees_freedom_;
    }

    /**
     * @brief Set the degrees of freedom
     */
    void degreesOfFreedom( std::optional< int > dof ) {

      this->degrees_freedom_ = std::move( dof );
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
     *  @brief Return a linearised average width table
     *
     *  @param[in] tolerance   the linearisation tolerance
     */
    TabulatedAverageWidths linearise( double tolerance = constants::linearisation::tolerance ) const {

      using Tolerance = njoy::scion::linearisation::ToleranceConvergence< double, double >;
      auto table = InterpolationTable::linearise( Tolerance( tolerance, constants::linearisation::threshold ) );
      return TabulatedAverageWidths( this->degreesOfFreedom(), std::move( table ) );
    }

    /**
     *  @brief Inplace scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageWidths& operator+=( double right ) {

      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageWidths& operator-=( double right ) {

      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageWidths& operator*=( double right ) {

      InterpolationTable::operator*=( right );
      return *this;
    }

    /**
     *  @brief Inplace scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageWidths& operator/=( double right ) {

      InterpolationTable::operator/=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAverageWidths and scalar addition
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageWidths operator+( double right ) const {

      return TabulatedAverageWidths( this->degreesOfFreedom(),
                                     InterpolationTable::operator+( right ) );
    }

    /**
     *  @brief TabulatedAverageWidths and scalar subtraction
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageWidths operator-( double right ) const {

      return TabulatedAverageWidths( this->degreesOfFreedom(),
                                     InterpolationTable::operator-( right ) );
    }

    /**
     *  @brief TabulatedAverageWidths and scalar multiplication
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageWidths operator*( double right ) const {

      return TabulatedAverageWidths( this->degreesOfFreedom(),
                                     InterpolationTable::operator*( right ) );
    }

    /**
     *  @brief TabulatedAverageWidths and scalar division
     *
     *  @param[in] right    the scalar
     */
    TabulatedAverageWidths operator/( double right ) const {

      return TabulatedAverageWidths( this->degreesOfFreedom(),
                                     InterpolationTable::operator/( right ) );
    }

    /**
     *  @brief Unary minus
     */
    TabulatedAverageWidths operator-() const {

      return TabulatedAverageWidths( this->degreesOfFreedom(),
                                     InterpolationTable::operator-() );
    }

    /**
     *  @brief Inplace TabulatedAverageWidths addition
     *
     *  @param[in] right    the table
     */
    TabulatedAverageWidths& operator+=( const TabulatedAverageWidths& right ) {

      this->degreesOfFreedom() = combineDoF( this->degreesOfFreedom(), right.degreesOfFreedom() );
      InterpolationTable::operator+=( right );
      return *this;
    }

    /**
     *  @brief Inplace TabulatedAverageWidths subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAverageWidths& operator-=( const TabulatedAverageWidths& right ) {

      this->degreesOfFreedom() = combineDoF( this->degreesOfFreedom(), right.degreesOfFreedom() );
      InterpolationTable::operator-=( right );
      return *this;
    }

    /**
     *  @brief TabulatedAverageWidths and TabulatedAverageWidths addition
     *
     *  @param[in] right    the table
     */
    TabulatedAverageWidths operator+( const TabulatedAverageWidths& right ) const {

      return TabulatedAverageWidths( combineDoF( this->degreesOfFreedom(), right.degreesOfFreedom() ),
                                     InterpolationTable::operator+( right ) );
    }

    /**
     *  @brief TabulatedAverageWidths and TabulatedAverageWidths subtraction
     *
     *  @param[in] right    the table
     */
    TabulatedAverageWidths operator-( const TabulatedAverageWidths& right ) const {

      return TabulatedAverageWidths( combineDoF( this->degreesOfFreedom(), right.degreesOfFreedom() ),
                                      InterpolationTable::operator-( right ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const TabulatedAverageWidths& right ) const {

      return this->degreesOfFreedom() == right.degreesOfFreedom() &&
             InterpolationTable::operator==( right );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const TabulatedAverageWidths& right ) const {

      return ! this->operator==( right );
    }
  };

  /**
   *  @brief Scalar and TabulatedAverageWidths addition
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageWidths operator+( double left, const TabulatedAverageWidths& right ) {

    return right + left;
  }

  /**
   *  @brief Scalar and TabulatedAverageWidths subtraction
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageWidths operator-( double left, const TabulatedAverageWidths& right ) {

    auto result = -right;
    result += left;
    return result;
  }

  /**
   *  @brief Scalar and TabulatedAverageWidths multiplication
   *
   *  @param[in] left    the scalar
   *  @param[in] right   the table
   */
  inline TabulatedAverageWidths operator*( double left, const TabulatedAverageWidths& right ) {

    return right * left;
  }

} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif
