#ifndef NJOY_DRYAD_RESONANCES_CALCULATOR_GENERALRMATRIX
#define NJOY_DRYAD_RESONANCES_CALCULATOR_GENERALRMATRIX

// system includes
#include <variant>
#include <vector>

// other includes
#include "dryad/matrix.hpp"
#include "dryad/resonances/calculator/Constant.hpp"
#include "dryad/resonances/calculator/ShiftFactor.hpp"

namespace njoy {
namespace dryad {
namespace resonances {
namespace calculator {

  /**
   *  @class
   *  @brief A matrix and cross section calculator for the general R-matrix formalism
   */
  class GeneralRMatrix {

    using LMatrix = std::variant< calculator::Constant, calculator::ShiftFactor >;

    /* fields */

    LMatrix l_matrix_;
    matrix::Matrix< std::complex< double > > g_matrix_;
    matrix::Matrix< std::complex< double > > a_matrix_;
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

    // blatantly copied from Reich-Moore
    #include "dryad/resonances/calculator/ReichMoore/src/selectLMatrix.hpp"
    #include "dryad/resonances/calculator/GeneralRMatrix/src/makeGMatrix.hpp"

    /* auxiliary functions */

    std::vector< bool >&
    belowThreshold( double energy, const std::vector< Channel >& channels ) {

      std::transform( channels.begin(), channels.end(), this->below_threshold_.begin(),
                      [&] ( const auto& channel ) { return channel.isBelowThreshold( energy ); } );
      return this->below_threshold_;
    }

    const matrix::DiagonalMatrix< std::complex< double > >&
    l_matrix() {

      using Matrix = matrix::DiagonalMatrix< std::complex< double > >;
      tools::overload visitor{

        [&] ( ShiftFactor& function ) -> decltype(auto) {

          return function.matrix();
        },
        [&] ( Constant& function ) -> decltype(auto) {

          return function.matrix();
        }
      };

      return std::visit( visitor, this->l_matrix_ );
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

    #include "dryad/resonances/calculator/GeneralRMatrix/src/ctor.hpp"

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

      std::transform( channels.begin(), channels.end(), this->penetrabilities_.begin(),
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

      std::transform( channels.begin(), channels.end(), this->shift_factors_.begin(),
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

      std::transform( channels.begin(), channels.end(), this->phase_shifts_.begin(),
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

      std::transform( channels.begin(), channels.end(), this->coulomb_phase_shifts_.begin(),
                      [&] ( const auto& channel ) { return channel.phaseShiftDifference( energy ); } );
      return this->coulomb_phase_shifts_;
    }

    const std::vector< double >& boundaryConditions() const {

      return this->boundaries_;
    }

    const std::vector< double >&
    boundaryConditions( const std::vector< Channel >& channels ) {

      std::transform( channels.begin(), channels.end(), this->boundaries_.begin(),
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

      unsigned int number_channels = table.numberChannels();
      unsigned int number_levels = table.numberEnergies();

      // calculate penetrabilitiesand the L matrix at this energy
      this->penetrabilities( energy, channels );
      this->l_matrix( energy, channels );

      //! @todo handle below threshold reactions?

      this->a_matrix_.setZero();
      for ( unsigned int lambda = 0; lambda < number_levels; ++lambda ) {

        this->a_matrix_( lambda, lambda ) = ( table.energies()[lambda] - energy );
        for ( unsigned int mu = 0; mu < number_levels; ++mu ) {

          for ( unsigned int c = 0; c < number_channels; ++c ) {

            this->a_matrix_( lambda, mu ) -= table.reducedWidthAmplitudes()[c][lambda] *
                                             this->l_matrix().diagonal()[c] *
                                             table.reducedWidthAmplitudes()[c][mu];
          }
        }
      }
      this->a_matrix_ = this->a_matrix_.inverse();

      // calculate and return the matrix
      // R_L = ( 1 - RL )^-1 R = G A G^T
      this->r_l_matrix_ = this->g_matrix_ * this->a_matrix_ *
                          this->g_matrix_.transpose();
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
      unsigned int number_channels = channels.size();
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
      unsigned int number_channels = channels.size();
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
      unsigned int number_channels = channels.size();
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

      // calculate the u matrix
      this->u_matrix( energy, channels, table );

      // loop over the channels and check for input channels
      unsigned int number_channels = channels.size();
      for ( unsigned int c = 0; c < number_channels; ++c ) {

        if ( channels[c].isIncidentChannel() ) {

          // wave numbers are stored in fm^-1, we need to convert to barn^-1/2
          // so the cross section will be returned in barn

          double k = channels[c].waveNumber( energy ) * constants::deca;
          double gj = channels[c].statisticalSpinFactor();
          double factor = constants::pi / k / k * gj;

          //! @todo check this formula: SAMMY says exp( 2 i w_c ), endf102 says exp( i w_c )
          auto exp = std::exp( std::complex< double >( 0., 2. * this->phaseShiftDifferences()[c] ) );

          for ( unsigned int cprime = 0; cprime < number_channels; ++cprime ) {

            if ( c != cprime ) {

              double norm = std::norm( this->u_matrix()(c,cprime) );
              xs[ channels[cprime].reaction() ] += factor * norm;
            }
            else {

              double norm = std::norm( exp - this->u_matrix()(c,cprime) );
              xs[ channels[cprime].reaction() ] += factor * norm;
            }
          }
        }
      }
    }
  };

} // calculator namespace
} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
