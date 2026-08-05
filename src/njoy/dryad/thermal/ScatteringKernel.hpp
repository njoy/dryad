#ifndef NJOY_DRYAD_THERMAL_SCATTERINGKERNEL
#define NJOY_DRYAD_THERMAL_SCATTERINGKERNEL

// system includes
#include <algorithm>
#include <tuple>

// other includes
#include "scion/linearisation/Lineariser.hpp"
#include "scion/integration/AdaptiveGaussLobatto.hpp"
#include "njoy/dryad/thermal/ShortCollisionTimeScatteringKernel.hpp"
#include "njoy/dryad/thermal/TabulatedScatteringKernel.hpp"
#include "njoy/dryad/TabulatedAngularDistribution.hpp"
#include "njoy/dryad/TabulatedEnergyDistribution.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace dryad {
namespace thermal {

  /**
   *  @class
   *  @brief An S(a,b) scattering kernel for incoherent inelastic thermal scattering
   */
  class ScatteringKernel {

    /* fields */

    ShortCollisionTimeScatteringKernel sct_;
    TabulatedScatteringKernel sab_;

    double kt_;

    /**
     *  @brief Return the moderator temperature as an energy value
     */
    double moderatorTemperatureAsEnergy() const {

      return this->kt_;
    }

    /**
     *  @brief Return the initial incident energy grid for a given lower and upper energy
     *
     *  @param[in] lower   the lower energy limit
     *  @param[in] upper   the upper energy limit
     */
    std::vector< double > initialIncidentEnergyGrid( double lower, double upper ) const {

      //! @todo optimise the grid better?
      std::vector< double > grid = { 1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1., 10. };

      auto iter = std::upper_bound( grid.begin(), grid.end(), lower );
      iter = grid.insert( iter, lower );
      grid.erase( grid.begin(), iter );

      iter = std::lower_bound( grid.begin(), grid.end(), upper );
      iter = grid.insert( iter, upper );
      grid.erase( std::next( iter ), grid.end() );

      return grid;
    }

    /**
     *  @brief Return the initial outgoing energy grid for a given incident energy
     *
     *  @param[in] incident    the incident energy
     */
    std::vector< double > initialOutgoingEnergyGrid( double incident ) const {

      //! @todo optimise the grid better?
      std::vector< double > grid = { 0, 1e-9, 1e-8, 1e-7, 1e-6, 1e-5, 1e-4,
                                     1e-3, 1e-2, 1e-1, 1., 10., incident };
      for ( double beta : this->tabulatedScatteringKernel().energyTransfers() ) {

        if ( incident + this->moderatorTemperatureAsEnergy() * beta > 0. ) {

          grid.emplace_back( incident + this->moderatorTemperatureAsEnergy() * beta );
        }
        if ( this->isEnergyTransferSymmetric() ) {

          if ( incident - this->moderatorTemperatureAsEnergy() * beta > 0. ) {

            grid.emplace_back( incident - this->moderatorTemperatureAsEnergy() * beta );
          }
        }
      }
      std::sort( grid.begin(), grid.end() );
      grid.erase( std::unique( grid.begin(), grid.end() ), grid.end() );

      return grid;
    }

    /**
     *  @brief Linearise the incoherent inelastic scattering angular distribution for a
     *         given incident and outgoing energy (unnormalised)
     *
     *  @param[in] incident    the incident energy
     *  @param[in] outgoing    the outgoing energy
     *  @param[in] ratio       the atomic mass ratio of the target to the projectile
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    std::pair< std::vector< double >, std::vector< double > >
    lineariseAngularDistribution( double incident, double outgoing, double ratio,
                                  double tolerance = constants::linearisation::tolerance ) const {

      //! @todo optimise the grid better?
      std::vector< double > grid = { -1.0, -0.8, -0.6, -0.4, -0.2, 0.0, 0.2, 0.4, 0.6, 0.8, 1.0 };

      // this version works well when using adaptive linearisation
      // for the energy distribution
      // std::vector< double > grid = { -1. };
      // std::size_t number = 100;
      // for ( std::size_t i = 0; i < number; ++i ) {
      //
      //   grid.emplace_back( grid.back() + 2. / number );
      // }

      using MidpointSplit = scion::linearisation::MidpointSplit< double, double >;
      using Tolerance = scion::linearisation::ToleranceConvergence< double, double >;
      using Lineariser = scion::linearisation::Lineariser< std::vector< double >, std::vector< double > >;

      std::vector< double > cosines;
      std::vector< double > values;
      Lineariser lineariser( cosines, values );
      Tolerance converged( tolerance, constants::linearisation::threshold );
      lineariser( grid,
                  [&] ( auto&& cosine ) { return this->operator()( incident, outgoing, cosine, ratio ); },
                  [&] ( auto&& trial , auto&& reference, auto&& xLeft,
                        auto&& xRight, auto&& yLeft    , auto&& yRight ) {

                    return converged( trial, reference, xLeft, xRight, yLeft, yRight ) ||
                           std::abs( xRight - xLeft ) <= ( 100. * std::numeric_limits< double >::epsilon() ) * std::abs( xLeft );
                  },
                  MidpointSplit() );

      return std::make_pair( std::move( cosines ), std::move( values ) );
    }

    /**
     *  @brief Linearise the incoherent inelastic scattering energy distribution for a
     *         given incident energy (unnormalised)
     *
     *  @param[in] incident    the incident energy
     *  @param[in] outgoing    the outgoing energy
     *  @param[in] ratio       the atomic mass ratio of the target to the projectile
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    std::pair< std::vector< double >, std::vector< double > >
    lineariseEnergyDistribution( double incident, double ratio,
                                 double tolerance = constants::linearisation::tolerance ) const {

      scion::integration::AdaptiveGaussLobatto< double, double > integrator;
      auto function = [&] ( auto&& outgoing ) -> double {

        double b = this->energyTransfer( incident, outgoing );

        // this is the version using adaptive linearisation
        // auto angular = this->lineariseAngularDistribution( incident, outgoing, ratio, tolerance );
        // double integral = scion::integration::integral( angular.first, angular.second, scion::integration::linlin );

        double integral = integrator( [&] ( auto&& cosine )
                                          { return this->operator()( incident, outgoing, cosine, ratio ); },
                                      -1., 1., constants::integration::tolerance );
        return std::sqrt( outgoing / incident ) * std::exp( -0.5 * b ) * integral;
      };

      using MidpointSplit = scion::linearisation::MidpointSplit< double, double >;
      using Tolerance = scion::linearisation::ToleranceConvergence< double, double >;
      using Lineariser = scion::linearisation::Lineariser< std::vector< double >, std::vector< double > >;

      std::vector< double > energies;
      std::vector< double > values;
      Lineariser lineariser( energies, values );
      Tolerance converged( tolerance, constants::linearisation::threshold );
      lineariser( this->initialOutgoingEnergyGrid( incident ),
                  function,
                  [&] ( auto&& trial , auto&& reference, auto&& xLeft,
                        auto&& xRight, auto&& yLeft    , auto&& yRight ) {

                    return converged( trial, reference, xLeft, xRight, yLeft, yRight ) ||
                           std::abs( xRight - xLeft ) <= ( 100. * std::numeric_limits< double >::epsilon() ) * std::abs( xLeft );
                  },
                  MidpointSplit() );

      return std::make_pair( std::move( energies ), std::move( values ) );
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ScatteringKernel() = default;

    ScatteringKernel( const ScatteringKernel& ) = default;
    ScatteringKernel( ScatteringKernel&& ) = default;

    ScatteringKernel& operator=( const ScatteringKernel& ) = default;
    ScatteringKernel& operator=( ScatteringKernel&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] moderatorTemperature   the moderator temperature
     *  @param[in] effectiveTemperature   the effective temperature used in the SCT approximation
     *  @param[in] table                  the tabulated S(a,b) scattering kernel
     */
    ScatteringKernel( double moderatorTemperature, double effectiveTemperature,
                      TabulatedScatteringKernel table ) :
        sct_( moderatorTemperature, effectiveTemperature ),
        sab_( std::move( table ) ) {

      this->kt_ = constants::k * this->moderatorTemperature() / constants::e;
    }

    /**
     *  @brief Constructor
     *
     *  @param[in] moderatorTemperature   the moderator temperature
     *  @param[in] effectiveTemperature   the effective temperature used in the SCT approximation
     *  @param[in] energyTransfers        the energy transfer values
     *  @param[in] functions              the associated scattering functions
     *  @param[in] boundaries             the boundaries of the interpolation regions
     *  @param[in] interpolants           the interpolation types of the interpolation regions
     */
    ScatteringKernel( double moderatorTemperature,
                      double effectiveTemperature,
                      std::vector< double > energyTransfers,
                      std::vector< TabulatedScatteringKernelFunction > functions,
                      std::vector< std::size_t > boundaries,
                      std::vector< InterpolationType > interpolants ) :
        ScatteringKernel(
            moderatorTemperature, effectiveTemperature,
            TabulatedScatteringKernel( std::move( energyTransfers ), std::move( functions ),
                                       std::move( boundaries ), std::move( interpolants ) ) ) {}

    /**
     *  @brief Constructor using a single interpolation zone
     *
     *  @param[in] moderatorTemperature   the moderator temperature
     *  @param[in] effectiveTemperature   the effective temperature used in the SCT approximation
     *  @param[in] energyTransfers        the energy transfer values
     *  @param[in] functions              the associated functions
     *  @param[in] interpolant            the interpolation type of the data (default lin-lin)
     */
    ScatteringKernel( double moderatorTemperature,
                      double effectiveTemperature,
                      std::vector< double > energyTransfers,
                      std::vector< TabulatedScatteringKernelFunction > functions,
                      InterpolationType interpolant = InterpolationType::LinearLinear ) :
        ScatteringKernel(
            moderatorTemperature, effectiveTemperature,
            TabulatedScatteringKernel( std::move( energyTransfers ), std::move( functions ),
                                       interpolant ) ) {}

    /* methods */

    /**
     *  @brief Return the moderator temperature
     */
    double moderatorTemperature() const {

      return this->shortCollisionTime().moderatorTemperature();
    }

    /**
     *  @brief Return the effective temperature used for the short collision time approximation
     */
    double effectiveTemperature() const {

      return this->shortCollisionTime().effectiveTemperature();
    }

    /**
     *  @brief Return the short collision time approximation
     */
    const ShortCollisionTimeScatteringKernel& shortCollisionTime() const {

      return this->sct_;
    }

    /**
     *  @brief Return the short collision time approximation
     */
    ShortCollisionTimeScatteringKernel& shortCollisionTime() {

      return this->sct_;
    }

    /**
     *  @brief Return the tabulated scattering kernel
     */
    const TabulatedScatteringKernel& tabulatedScatteringKernel() const {

      return this->sab_;
    }

    /**
     *  @brief Return the short collision time approximation
     */
    TabulatedScatteringKernel& tabulatedScatteringKernel() {

      return this->sab_;
    }

    /**
     *  @brief Return whether or not the scattering kernel is symmetric along the
     *         energy transfer axis
     */
    bool isEnergyTransferSymmetric() const {

      return ! ( this->tabulatedScatteringKernel().energyTransfers().front() < 0. );
    }

    /**
     *  @brief Evaluate the momentum transfer for a given incident and outgoing energy
     *
     *  @param[in] incident    the incident energy
     *  @param[in] outgoing    the outgoing energy
     */
    double momentumTransfer( double incident, double outgoing, double cosine, double ratio ) const {

      return ( outgoing + incident - 2. * cosine * std::sqrt( outgoing * incident ) )
             / ratio / this->moderatorTemperatureAsEnergy();
    }

    /**
     *  @brief Evaluate the energy transfer for a given incident and outgoing energy
     *
     *  @param[in] incident    the incident energy
     *  @param[in] outgoing    the outgoing energy
     */
    double energyTransfer( double incident, double outgoing ) const {

      return ( outgoing - incident ) / this->moderatorTemperatureAsEnergy();
    }

    /**
     *  @brief Evaluate the scattering kernel for a given incident energy, outgoing energy
     *         and cosine value
     *
     *  @param[in] incident    the incident energy
     *  @param[in] outgoing    the outgoing energy
     *  @param[in] cosine      the cosine value
     *  @param[in] ratio       the atomic mass ratio of the target to the projectile
     */
    double operator()( double incident, double outgoing, double cosine, double ratio ) const {

      return this->operator()( this->momentumTransfer( incident, outgoing, cosine, ratio ),
                               this->energyTransfer( incident, outgoing ) );
    }

    /**
     *  @brief Evaluate the scattering kernel for a given momentum and energy transfer value
     *
     *  @param[in] a   the momentum transfer value
     *  @param[in] b   the energy transfer value
     */
    double operator()( double a, double b ) const {

      if ( this->isEnergyTransferSymmetric() && b < 0. ) {

        b = -b;
      }

      if ( a < this->tabulatedScatteringKernel().lowerMomentumTransferLimit() ) {

        a = this->tabulatedScatteringKernel().lowerMomentumTransferLimit();
      }

      if ( b < this->tabulatedScatteringKernel().lowerEnergyTransferLimit() ||
           b > this->tabulatedScatteringKernel().upperEnergyTransferLimit() ||
           a > this->tabulatedScatteringKernel().upperMomentumTransferLimit() ) {

        return this->shortCollisionTime()( a, b );
      }
      else {

        return this->tabulatedScatteringKernel()( a, b );
      }
    }

    /**
     *  @brief Return the incoherent inelastic scattering angular distribution for a
     *         given incident and outgoing energy
     *
     *  @param[in] incident    the incident energy
     *  @param[in] outgoing    the outgoing energy
     *  @param[in] ratio       the atomic mass ratio of the target to the projectile
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedAngularDistribution
    angularDistribution( double incident, double outgoing, double ratio,
                         double tolerance = constants::linearisation::tolerance ) const {

      auto angular = this->lineariseAngularDistribution( incident, outgoing, ratio, tolerance );
      return TabulatedAngularDistribution( std::move( angular.first ), std::move( angular.second ),
                                           InterpolationType::LinearLinear, true );
    }

    /**
     *  @brief Return the incoherent inelastic scattering outgoing energy distribution for a
     *         given incident energy
     *
     *  @param[in] incident    the incident energy
     *  @param[in] ratio       the atomic mass ratio of the target to the projectile
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedEnergyDistribution
    energyDistribution( double incident, double ratio,
                        double tolerance = constants::linearisation::tolerance ) const {

      auto energy = this->lineariseEnergyDistribution( incident, ratio, tolerance );
      return TabulatedEnergyDistribution( std::move( energy.first ), std::move( energy.second ),
                                          InterpolationType::LinearLinear, true );
    }

    /**
     *  @brief Return the incoherent inelastic cross section value for a given incident energy
     *
     *  @param[in] incident    the incident energy
     *  @param[in] xs          the bound atom cross section
     *  @param[in] ratio       the atomic mass ratio of the target to the projectile
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    double
    crossSectionValue( double incident, double xs, double ratio,
                       double tolerance = constants::linearisation::tolerance ) const {

      auto energy = this->lineariseEnergyDistribution( incident, ratio, tolerance );
      double integral = scion::integration::integral( energy.first, energy.second, scion::integration::linlin );
      return 0.5 * xs / this->moderatorTemperatureAsEnergy() * integral;
    }

    /**
     *  @brief Return the incoherent inelastic cross section
     *
     *  @param[in] lower       the lower energy limit
     *  @param[in] upper       the upper energy limit
     *  @param[in] xs          the bound atom cross section
     *  @param[in] ratio       the atomic mass ratio of the target to the projectile
     *  @param[in] tolerance   the linearisation tolerance (default: 0.1 %)
     */
    TabulatedCrossSection
    crossSection( double lower,
                  double upper,
                  double xs,
                  double ratio,
                  double tolerance = constants::linearisation::tolerance ) const {

      using MidpointSplit = scion::linearisation::MidpointSplit< double, double >;
      using Tolerance = scion::linearisation::ToleranceConvergence< double, double >;
      using Lineariser = scion::linearisation::Lineariser< std::vector< double >, std::vector< double > >;

      std::vector< double > energies;
      std::vector< double > values;
      Lineariser lineariser( energies, values );
      lineariser( this->initialIncidentEnergyGrid( lower, upper ),
                  [&] ( auto&& incident ) { return this->crossSectionValue( incident, xs, ratio, tolerance ); },
                  Tolerance( tolerance, constants::linearisation::threshold ),
                  MidpointSplit() );

      return TabulatedCrossSection( std::move( energies ), std::move( values ) );
    }

    /**
     *  @brief Comparison operator: equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator==( const ScatteringKernel& right ) const {

      return std::tie( this->shortCollisionTime(), this->tabulatedScatteringKernel()  ) ==
             std::tie( right.shortCollisionTime(), right.tabulatedScatteringKernel() );
    }

    /**
     *  @brief Comparison operator: not equal
     *
     *  @param[in] right   the object on the right hand side
     */
    bool operator!=( const ScatteringKernel& right ) const {

      return ! this->operator==( right );
    }
  };

} // thermal namespace
} // dryad namespace
} // njoy namespace

#endif
