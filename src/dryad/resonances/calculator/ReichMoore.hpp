#ifndef NJOY_DRYAD_RESONANCES_CALCULATOR_REICHMOORE
#define NJOY_DRYAD_RESONANCES_CALCULATOR_REICHMOORE

// system includes
#include <algorithm>
#include <complex>
#include <variant>
#include <vector>

// other includes
#include "tools/overload.hpp"
#include "dryad/matrix.hpp"
#include "dryad/resonances/BoundaryCondition.hpp"
#include "dryad/resonances/Channel.hpp"
#include "dryad/resonances/ResonanceTable.hpp"
#include "dryad/resonances/calculator/Constant.hpp"
#include "dryad/resonances/calculator/ShiftFactor.hpp"

namespace njoy {
namespace dryad {
namespace resonances {
namespace calculator {

  /**
   *  @class
   *  @brief A matrix and cross section calculator for the Reich-Moore formalism
   */
  class ReichMoore {

    /* type aliases */

    using LMatrix = std::variant< calculator::Constant, calculator::ShiftFactor >;

    /* fields */

    LMatrix l_matrix_;
    matrix::Matrix< std::complex< double > > r_matrix_;
    matrix::Matrix< std::complex< double > > r_l_matrix_;
    matrix::Matrix< std::complex< double > > t_matrix_;
    matrix::Matrix< std::complex< double > > w_matrix_;
    matrix::Matrix< std::complex< double > > u_matrix_;
    matrix::DiagonalMatrix< double > sqrt_p_matrix_;
    matrix::DiagonalMatrix< std::complex< double > > omega_matrix_;

    std::vector< double > penetrabilities_;
    std::vector< double > shift_factors_;
    std::vector< double > phase_shifts_;
    std::vector< double > coulomb_phase_shifts_;
    std::vector< double > boundaries_;
    std::vector< bool > below_threshold_;

    /* auxiliary functions */

    #include "dryad/resonances/calculator/ReichMoore/src/selectLMatrix.hpp"
    #include "dryad/resonances/calculator/ReichMoore/src/verifyEliminatedChannel.hpp"

    std::vector< bool >&
    belowThreshold( double energy, const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->below_threshold_.begin(),
                      [&] ( const auto& channel ) { return channel.isBelowThreshold( energy ); } );
      return this->below_threshold_;
    }

    const matrix::DiagonalMatrix< std::complex< double > >&
    l_matrix( double energy,
              const std::vector< Channel >& channels ) {

      using Matrix = matrix::DiagonalMatrix< std::complex< double > >;
      tools::overload visitor{

        [&] ( ShiftFactor& function ) -> decltype(auto) {

          return function( this->penetrabilities() );
        },
        [&] ( Constant& function ) -> decltype(auto) {

          return function( this->shiftFactors( energy, channels ),
                           this->penetrabilities(),
                           this->boundaryConditions() );
        }
      };

      return std::visit( visitor, this->l_matrix_ );
    }

  public:

    /* constructor */

    #include "dryad/resonances/calculator/ReichMoore/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the current values for the penetrabilities
     */
    const std::vector< double >& penetrabilities() const {

      return this->penetrabilities_;
    }

    /**
     *  @brief Evaluate and return the penetrabilities
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     */
    const std::vector< double >&
    penetrabilities( double energy, const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->penetrabilities_.begin(),
                      [&] ( const auto& channel ) { return channel.penetrability( energy ); } );
      return this->penetrabilities_;
    }

    /**
     *  @brief Return the current values for the shift factors
     */
    const std::vector< double >& shiftFactors() const {

      return this->shift_factors_;
    }

    /**
     *  @brief Evaluate and return the shift factors
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     */
    const std::vector< double >&
    shiftFactors( double energy, const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->shift_factors_.begin(),
                      [&] ( const auto& channel ) { return channel.shiftFactor( energy ); } );
      return this->shift_factors_;
    }

    /**
     *  @brief Return the current values for the phase shifts
     */
    const std::vector< double >& phaseShifts() const {

      return this->phase_shifts_;
    }

    /**
     *  @brief Evaluate and return the phase shifts
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     */
    const std::vector< double >&
    phaseShifts( double energy, const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->phase_shifts_.begin(),
                      [&] ( const auto& channel ) { return channel.phaseShift( energy ); } );
      return this->phase_shifts_;
    }

    /**
     *  @brief Return the current values for the Coulomb phase shift differences
     */
    const std::vector< double >& phaseShiftDifferences() const {

      return this->coulomb_phase_shifts_;
    }

    /**
     *  @brief Evaluate and return the Coulomb phase shift differences
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     */
    const std::vector< double >&
    phaseShiftDifferences( double energy, const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->coulomb_phase_shifts_.begin(),
                      [&] ( const auto& channel ) { return channel.phaseShiftDifference( energy ); } );
      return this->coulomb_phase_shifts_;
    }

    const std::vector< double >& boundaryConditions() const {

      return this->boundaries_;
    }

    const std::vector< double >&
    boundaryConditions( const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->boundaries_.begin(),
                      [] ( const auto& channel ) { return channel.boundaryCondition().value(); } );
      return this->boundaries_;
    }

    /**
     *  @brief Return the current value of the R_L matrix
     */
    const matrix::Matrix< std::complex< double > >& r_l_matrix() const {

      return this->r_l_matrix_;
    }

    /**
     *  @brief Evaluate and return the R_L matrix
     *
     *  The R_L matrix is defined as ( 1 - RL )^-1 R in which R is the
     *  R matrix and L is a diagonal matrix defined as S - B + iP with
     *  S the shift factor and B the boundary condition of the channel.
     *
     *  This function will always evaluate the penetrabilities. If the
     *  boundary condition is the constant boundary condition, then this
     *  function will also evaluate the boundary condition values and
     *  shift factors.
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     *  @param[in] table      the resonance table
     */
    const matrix::Matrix< std::complex< double > >&
    r_l_matrix( double energy,
                const std::vector< Channel >& channels,
                const ResonanceTable& table ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      unsigned int eliminated = 0;
      unsigned int number_channels = channels.size() - 1;

      // calculate penetrabilities at this energy
      this->penetrabilities( energy, channels );

      // verify which channels are below threshold
      decltype(auto) below_threshold = this->belowThreshold( energy, channels );

      // populate the r matrix
      this->r_matrix_.setZero();
      for ( unsigned int c = 0; c < number_channels; ++c ) {

        if ( ! below_threshold[c] ) {

          for ( unsigned int cprime = c; cprime < number_channels; ++cprime ) {

            if ( ! below_threshold[cprime] ) {

              // accumulate the contribution for each level energy
              //
              // The R-matrix element R_{ij} for channel i to j is given by:
              //     R_{ij} = \frac{ \gamma_i \gamma_j }{ E_r - E - i \gamma * \gamma }
              // in which \gamma_i and \gamma_j are the reduced widths of channel i and j,
              // E_r is the level energy, E is the energy at which the resonance needs
              // to be evaluated and \gamma is the eliminated capture redcued width.
              for ( unsigned int lambda = 0; lambda < table.numberEnergies(); ++lambda ) {

                double gg = table.reducedWidthAmplitudes()[c+1][lambda] *
                            table.reducedWidthAmplitudes()[cprime+1][lambda];
                double delta = table.energies()[lambda] - energy;
                double Gamma = table.reducedWidthAmplitudes()[eliminated][lambda]
                             * table.reducedWidthAmplitudes()[eliminated][lambda];
                this->r_matrix_( c, cprime ) += gg / std::complex< double >( delta, -Gamma );
              }

              // the r matrix is symmetrical
              if ( cprime > c ) {

                this->r_matrix_( cprime, c ) = this->r_matrix_( c, cprime );
              }
            }
          }
        }
      }

      // calculate and return the matrix
      this->r_l_matrix_.setIdentity();
      this->r_l_matrix_ -= this->r_matrix_ *
                           this->l_matrix( energy, channels );
      this->r_l_matrix_ = this->r_l_matrix_.inverse();
      this->r_l_matrix_ *= this->r_matrix_;
      return this->r_l_matrix_;
    }

    /**
     *  @brief Return the current value of the T or X matrix
     */
    const matrix::Matrix< std::complex< double > >& t_matrix() const {

      return this->t_matrix_;
    }

    /**
     *  @brief Evaluate and return the T or X matrix
     *
     *  The T or X matrix is defined as P^1/2 ( 1 - RL )^-1 R P^1/2 in which
     *  P is a diagonal matrix of the penetrabilities of each channel, R is the
     *  R matrix and L is a diagonal matrix defined as S - B + iP with S the shift
     *  factor and B the boundary condition of the channel.
     *
     *  This function will always evaluate the penetrabilities. If the
     *  boundary condition is the constant boundary condition, then this
     *  function will also evaluate the boundary condition values and
     *  shift factors.
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     *  @param[in] table      the resonance table
     */
    const matrix::Matrix< std::complex< double > >&
    t_matrix( double energy,
              const std::vector< Channel >& channels,
              const ResonanceTable& table ) {

      // calculate the R_L = ( 1 - RL )^-1 R matrix (this also calculates penetrability)
      this->r_l_matrix( energy, channels, table );

      // calculate the square root of the penetrabilies
      unsigned int number_channels = channels.size() - 1;
      for ( unsigned int c = 0; c < number_channels; ++c ) {

        this->sqrt_p_matrix_.diagonal()[c] = std::sqrt( this->penetrabilities()[c] );
      }

      // calculate and return the matrix
      this->t_matrix_ = this->sqrt_p_matrix_;
      this->t_matrix_ *= this->r_l_matrix_;
      this->t_matrix_ *= this->sqrt_p_matrix_;
      return this->t_matrix_;
    }

    /**
     *  @brief Return the current value of the W matrix
     */
    const matrix::Matrix< std::complex< double > >& w_matrix() const {

      return this->w_matrix_;
    }

    /**
     *  @brief Evaluate and return the W matrix
     *
     *  The W matrix is defined as I + 2 i P^1/2 ( 1 - RL )^-1 R P^1/2 in which
     *  I is the identity matrix, P is a diagonal matrix of the penetrabilities of
     *  each channel, R is the R matrix and L is a diagonal matrix defined as
     *  S - B + iP with S the shift factor and B the boundary condition of the
     *  channel.
     *
     *  This function will always evaluate the penetrabilities. If the
     *  boundary condition is the constant boundary condition, then this
     *  function will also evaluate the boundary condition values and
     *  shift factors.
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     *  @param[in] table      the resonance table
     */
    const matrix::Matrix< std::complex< double > >&
    w_matrix( double energy,
              const std::vector< Channel >& channels,
              const ResonanceTable& table ) {

      // calculate and return the matrix
      unsigned int number_channels = channels.size() - 1;
      this->w_matrix_ = this->t_matrix( energy, channels, table );
      this->w_matrix_ *= std::complex< double >( 0, 2. );
      this->w_matrix_ += matrix::Matrix< double >::Identity( number_channels, number_channels );
      return this->w_matrix_;
    }

    /**
     *  @brief Return the current value of the U or S matrix
     */
    const matrix::Matrix< std::complex< double > >& u_matrix() const {

      return this->u_matrix_;
    }

    /**
     *  @brief Evaluate and return the U or S matrix
     *
     *  The U or S matrix is defined as omega W omega
     *  in which omega is a diagonal matrix equal to exp( i ( w - phi ) ) with w
     *  the Coulomb phase shift difference and phi the phase shift.
     *
     *  This function will always evaluate the penetrabilities, phase shifts and
     *  Coulomb phase shift differences. If the boundary condition is the constant
     *  boundary condition, then this function will also evaluate the boundary
     *  condition values and shift factors.
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     *  @param[in] table      the resonance table
     */
    const matrix::Matrix< std::complex< double > >&
    u_matrix( double energy,
              const std::vector< Channel >& channels,
              const ResonanceTable& table ) {

      // calculate phase shift and Coulomb phase shift differences at this energy
      this->phaseShifts( energy, channels );
      this->phaseShiftDifferences( energy, channels );

      // calculate the omega diagonal
      unsigned int number_channels = channels.size() - 1;
      for ( unsigned int c = 0; c < number_channels; ++c ) {

        double shift = this->phaseShiftDifferences()[c]
                       - this->phaseShifts()[c];
        this->omega_matrix_.diagonal()[c] = std::exp( std::complex< double >( 0., shift ) );
      }

      // calculate and return the matrix
      this->u_matrix_ = this->omega_matrix_;
      this->u_matrix_ *= this->w_matrix( energy, channels, table );
      this->u_matrix_ *= this->omega_matrix_;
      return this->u_matrix_;
    }

    /**
     *  @brief Evaluate and return the cross section values
     *
     *  @param[in] energy     the energy
     *  @param[in] channels   the channels of the spin group
     *  @param[in] table      the resonance table
     *  @param[in] xs         the cross section values
     */
    void crossSections( double energy,
                        const std::vector< Channel >& channels,
                        const ResonanceTable& table,
                        std::map< id::ReactionID, double >& xs ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      unsigned int eliminated = 0;
      unsigned int number_channels = channels.size() - 1;

      // calculate the u matrix
      this->u_matrix( energy, channels, table );

      // loop over the channels and check for input channels
      for ( unsigned int c = 0; c < number_channels; ++c ) {

        if ( channels[c+1].isIncidentChannel() ) {

          // wave numbers are stored in fm^-1, we need to convert to barn^-1/2
          // so the cross section will be returned in barn

          double k = channels[c+1].waveNumber( energy ) * constants::deca;
          double gj = channels[c+1].statisticalSpinFactor();
          double factor = constants::pi / k / k * gj;

          double delta = 1.;
          //! @todo check this formula: SAMMY says exp( 2 i w_c ), endf102 says exp( i w_c )
          auto exp = std::exp( std::complex< double >( 0., 2. * this->phaseShiftDifferences()[c] ) );

          for ( unsigned int cprime = 0; cprime < number_channels; ++cprime ) {

            if ( c != cprime ) {

              double norm = std::norm( this->u_matrix()(c,cprime) );
              delta -= norm;
              xs[ channels[cprime+1].reaction() ] += factor * norm;
            }
            else {

              double norm = std::norm( exp - this->u_matrix()(c,cprime) );
              delta -= std::norm( this->u_matrix()(c,cprime) );
              xs[ channels[cprime+1].reaction() ] += factor * norm;
            }
          }

          xs[ channels[eliminated].reaction() ] += factor * delta;
        }
      }
    }
  };

} // calculator namespace
} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
