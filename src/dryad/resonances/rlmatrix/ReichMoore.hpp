#ifndef NJOY_DRYAD_RESONANCES_RLMATRIX_REICHMOORE
#define NJOY_DRYAD_RESONANCES_RLMATRIX_REICHMOORE

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
#include "dryad/resonances/lmatrix.hpp"
#include <iostream>
namespace njoy {
namespace dryad {
namespace resonances {
namespace rlmatrix {

  /**
   *  @class
   *  @brief A functor to calculate the R_L matrix for the Reich-Moore formalism
   */
  class ReichMoore {

    /* type aliases */

    using LMatrix = std::variant< lmatrix::Constant, lmatrix::ShiftFactor >;

    /* fields */

    LMatrix l_matrix_;
    matrix::Matrix< std::complex< double > > r_matrix_;
    matrix::Matrix< std::complex< double > > r_l_matrix_;

    std::vector< double > shift_factors_;
    std::vector< double > boundaries_;
    std::vector< bool > below_threshold_;

    /* auxiliary functions */

    LMatrix selectBoundaryCondition( unsigned int size, const BoundaryCondition& boundary ) {

      switch ( boundary ) {

        case BoundaryCondition::Constant : return lmatrix::Constant( size );
        case BoundaryCondition::ShiftFactor : return lmatrix::ShiftFactor( size );
        default : {

          throw std::runtime_error( "Unknown boundary condition type" );
        }
      }
    }

    static void verifyEliminatedChannel( const std::vector< Channel >& channels ) {

      if ( channels.front().outgoingParticlePair().has_value() ) {

        if ( channels.front().outgoingParticlePair()->lightParticle().identifier()
             == id::ParticleID::photon() ) {

          return;
        }
      }
      throw std::runtime_error( "The eliminated capture channel is not the first channel" );
    }

    const std::vector< double >&
    shiftFactors( double energy, const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->shift_factors_.begin(),
                      [&] ( const auto& channel ) { return channel.shiftFactor( energy ); } );
      return this->shift_factors_;
    }

    const std::vector< double >&
    boundaryConditions( const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->boundaries_.begin(),
                      [] ( const auto& channel ) { return channel.boundaryCondition().value(); } );
      return this->boundaries_;
    }

    const std::vector< bool >&
    belowThreshold( double energy, const std::vector< Channel >& channels ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      std::transform( channels.begin() + 1, channels.end(), this->below_threshold_.begin(),
                      [&] ( const auto& channel ) { return channel.isBelowThreshold( energy ); } );
      return this->below_threshold_;
    }

    const matrix::DiagonalMatrix< std::complex< double > >&
    l_matrix( double energy,
              const std::vector< double >& penetrabilities,
              const std::vector< Channel >& channels ) {

      using Matrix = matrix::DiagonalMatrix< std::complex< double > >;
      tools::overload visitor{

        [&] ( lmatrix::ShiftFactor& function ) -> const Matrix& {

          return function( penetrabilities );
        },
        [&] ( lmatrix::Constant& function ) -> const Matrix& {

          return function( this->shiftFactors( energy, channels ),
                           penetrabilities,
                           this->boundaryConditions( channels ) );
        }
      };

      return std::visit( visitor, this->l_matrix_ );
    }

  public:

    /* constructor */

    #include "dryad/resonances/rlmatrix/ReichMoore/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the current value of the R_L matrix
     */
    const matrix::Matrix< std::complex< double > >& matrix() const {

      return this->r_l_matrix_;
    }

    /**
     *  @brief Return the current value of the R_L matrix
     */
    matrix::Matrix< std::complex< double > >& matrix() {

      return this->r_l_matrix_;
    }

    /**
     *  @brief Return the number of channels
     */
    unsigned int numberChannels() const {

      return this->matrix().cols();
    }

    /**
     *  @brief Evaluate and return the R_L matrix for the Reich-Moore formalism
     *
     *  @param[in] energy            the energy at which to evaluate the R_L matrix
     *  @param[in] penetrabilities   the penetrability value for each channel
     *  @param[in] channels          the channels of the spin group
     *  @param[in] table             the resonance table
     */
    const matrix::Matrix< std::complex< double > >&
    operator()( double energy,
                const std::vector< double >& penetrabilities,
                const std::vector< Channel >& channels,
                const ResonanceTable& table ) {

      // the eliminated channel has to be the first
      // this function needs to be modified if that assumption changes
      unsigned int eliminated = 0;

      // verify which channels are below threshold
      decltype(auto) below_threshold = this->belowThreshold( energy, channels );

      // populate the r matrix
      this->r_matrix_.setZero();
      for ( unsigned int c = 0; c < this->numberChannels(); ++c ) {

        if ( ! below_threshold[c] ) {

          for ( unsigned int cprime = c; cprime < this->numberChannels(); ++cprime ) {

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

      // calculate and return R_L = ( 1 - RL )^-1 R
      this->r_l_matrix_.setIdentity();
      this->r_l_matrix_ -= this->r_matrix_ *
                           this->l_matrix( energy, penetrabilities, channels );
      this->r_l_matrix_ = this->r_l_matrix_.inverse();
      this->r_l_matrix_ *= this->r_matrix_;

      return this->matrix();
    }
  };

} // rlmatrix namespace
} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
