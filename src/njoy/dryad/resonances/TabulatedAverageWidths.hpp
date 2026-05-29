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
   *      <Gamma_n>(E) = <Gamma_n^0>(E) * sqrt(E) * P_l(E)
   * 
   * Units: energies in eV, widths in eV. DoF is dimensionless.
   *
   */
  class TabulatedAverageWidths : 
    protected scion::math::InterpolationTable< double, double > {
      std::optional< int > degrees_freedom_;
      public:

        /* type aliases*/
        using InterpolationTable::XType;
        using InterpolationTable::YType;

        /* auxiliary functions */
        #include "njoy/dryad/resonances/TabulatedAverageWidths/src/combineDoF.hpp"

        /* constructor */
        #include "njoy/dryad/resonances/TabulatedAverageWidths/src/ctor.hpp"

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
         * @brief Return the degrees of freedom for the chi-squared distribution
         */
        const std::optional<int>& degreesOfFreedom() const {
          return this->degrees_freedom_;
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
         *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
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

          this->degrees_freedom_ = combineDoF( this->degreesOfFreedom(), right.degreesOfFreedom() );
          InterpolationTable::operator+=( right );
          return *this;
        }

        /**
         *  @brief Inplace TabulatedAverageWidths subtraction
         *
         *  @param[in] right    the table
         */
        TabulatedAverageWidths& operator-=( const TabulatedAverageWidths& right ) {

          this->degrees_freedom_ = combineDoF( this->degreesOfFreedom(), right.degreesOfFreedom() );
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

          return this->degrees_freedom_ == right.degrees_freedom_
              && InterpolationTable::operator==( right );
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