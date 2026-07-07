#ifndef NJOY_DRYAD_RESONANCES_SPINGROUP
#define NJOY_DRYAD_RESONANCES_SPINGROUP

// system includes
#include <algorithm>
#include <variant>
#include <vector>

// other includes
#include "njoy/dryad/resonances/Channel.hpp"
#include "njoy/dryad/resonances/ResonanceTable.hpp"
#include "njoy/dryad/resonances/BoundaryCondition.hpp"
#include "njoy/dryad/resonances/Formalism.hpp"
#include "njoy/dryad/resonances/calculator.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A spin group corresponding to a Jpi quantum number set
   */
  class SpinGroup {

  public:

    /* type aliases */

    using ChannelData = std::pair< Channel, ResonanceTable >;

  private:

    /* type aliases */

    using Calculator = std::variant< calculator::ReichMoore, calculator::GeneralRMatrix >;

    /* fields */

    std::vector< Channel > channels_;
    ResonanceTable table_;
    Formalism formalism_;
    BoundaryCondition boundary_condition_;

    Calculator calculator_;
    std::vector< id::ReactionID > reactions_;

    /* auxiliary functions */

    #include "njoy/dryad/resonances/SpinGroup/src/createData.hpp"
    #include "njoy/dryad/resonances/SpinGroup/src/processChannels.hpp"
    #include "njoy/dryad/resonances/SpinGroup/src/verifySpinGroup.hpp"
    #include "njoy/dryad/resonances/SpinGroup/src/selectCalculator.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/resonances/SpinGroup/src/ctor.hpp"

    /**
     *  @brief Return the channels in the spin group
     */
    const std::vector< Channel >& channels() const {

      return this->channels_;
    }

    /**
     *  @brief Return the channels in the spin group
     */
    std::vector< Channel >& channels() {

      return this->channels_;
    }

    /**
     *  @brief Set the channels in the spin group
     *
     *  @param[in] channels  the channels
     */
    void channels( std::vector< Channel > channels ) {

      this->channels_ = std::move( channels );
      this->processChannels();
    }

    /**
     *  @brief Return the resonance table
     */
    const ResonanceTable& resonanceTable() const {

      return this->table_;
    }

    /**
     *  @brief Return the resonance table
     */
    ResonanceTable& resonanceTable() {

      return this->table_;
    }

    /**
     *  @brief Set the resonance table
     *
     *  @param[in] table  the resonance table
     */
    void resonanceTable( ResonanceTable table ) {

      this->table_ = std::move( table );
    }

    /**
     *  @brief Return the formalism
     */
    const Formalism& formalism() const {

      return this->formalism_;
    }

    /**
     *  @brief Return the boundary condition option
     */
    const BoundaryCondition& boundaryCondition() const {

      return this->boundary_condition_;
    }

    /**
     *  @brief Return the total angular momentum J of the spin group
     */
    double totalAngularMomentum() const {

      return this->channels().front().quantumNumbers().totalAngularMomentum();
    }

    /**
     *  @brief Return the parity
     */
    short parity() const {

      return this->channels().front().quantumNumbers().parity();
    }

    /**
     *  @brief Return the reactions to which this spin group contributes
     */
    const std::vector< id::ReactionID >& reactions() const {

      return this->reactions_;
    }

    /**
     *  @brief Return the reactions to which this spin group contributes
     */
    std::vector< id::ReactionID >& reactions() {

      return this->reactions_;
    }

    /**
     *  @brief Return the kinematics type applied to the spin group
     */
    Kinematics kinematicsType() const {

      return this->channels().front().kinematicsType();
    }

    /**
     *  @brief Return whether or not the channels in the spin group have backgrounds
     */
    bool hasChannelsWithBackground() const {

      return std::any_of( this->channels().begin(), this->channels().end(),
                          [] ( auto&& channel ) {

                            return channel.background().has_value();
                          } );
    }

    /**
     *  @brief Calculate the cross section values at a given energy
     *
     *  @param[in] energy   the energy
     *  @param[in] xs       the cross section values
     */
    void crossSections( double energy, std::map< id::ReactionID, double >& xs ) {

      std::visit( [&] ( auto&& calculator ) {

                    return calculator.crossSections( energy, this->channels(),
                                                     this->resonanceTable(), xs );
                  },
                  this->calculator_ );
    }

    /**
     *  @brief Calculate the cross section values for a list of energies
     *
     *  @param[in] energies   the energies
     *  @param[in] xs         the cross sections
     */
    void crossSections( std::vector<double>& energies, std::map< id::ReactionID, std::vector<double> >& xs ) {

      std::map< id::ReactionID, double > result;

      // for each energy, compute xs and insert in main container
      for ( std::size_t i = 0; i < energies.size(); ++i ) {

        this->crossSections( energies[i], result );
        for ( const auto& [reaction_id, cross_section] : result ) {

          auto& v = xs[reaction_id];
          if ( v.empty() ) {

            v.resize( energies.size(), 0.0 );
          }

          v[i] += cross_section;
        }
        result.clear();
      }
    }

    /**
     *  @brief Calculate the R_L matrix at a given energy
     *
     *  The R_L matrix is defined as ( 1 - RL )^-1 R in which R is the
     *  R matrix and L is a diagonal matrix defined as S - B + iP with
     *  S the shift factor and B the boundary condition of the channel.
     *
     *  @param[in] energy     the energy
     */
    const matrix::Matrix< std::complex< double > >&
    r_l_matrix( double energy ) {

      return std::visit( [&] ( auto&& calculator ) -> decltype(auto) {

                                 return calculator.r_l_matrix( energy, this->channels(),
                                                               this->resonanceTable() );
                               },
                               this->calculator_ );
    }

    /**
     *  @brief Calculate the T or X matrix at a given energy
     *
     *  The T or X matrix is defined as P^1/2 ( 1 - RL )^-1 R P^1/2 in which
     *  P is a diagonal matrix of the penetrabilities of each channel, R is the
     *  R matrix and L is a diagonal matrix defined as S - B + iP with S the shift
     *  factor and B the boundary condition of the channel.
     *
     *  @param[in] energy     the energy
     */
    const matrix::Matrix< std::complex< double > >&
    t_matrix( double energy ) {

      return std::visit( [&] ( auto&& calculator ) -> decltype(auto) {

                                 return calculator.t_matrix( energy, this->channels(),
                                                             this->resonanceTable() );
                               },
                               this->calculator_ );
    }

    /**
     *  @brief Calculate the W matrix at a given energy
     *
     *  The W matrix is defined as I + 2 i P^1/2 ( 1 - RL )^-1 R P^1/2 in which
     *  I is the identity matrix, P is a diagonal matrix of the penetrabilities of
     *  each channel, R is the R matrix and L is a diagonal matrix defined as
     *  S - B + iP with S the shift factor and B the boundary condition of the
     *  channel.
     *
     *  @param[in] energy     the energy
     */
    const matrix::Matrix< std::complex< double > >&
    w_matrix( double energy ) {

      return std::visit( [&] ( auto&& calculator ) -> decltype(auto) {

                                 return calculator.w_matrix( energy, this->channels(),
                                                             this->resonanceTable() );
                               },
                               this->calculator_ );
    }

    /**
     *  @brief Calculate the U or S matrix at a given energy
     *
     *  The U or S matrix is defined as omega W omega
     *  in which omega is a diagonal matrix equal to exp( i ( w - phi ) ) with w
     *  the Coulomb phase shift difference and phi the phase shift.
     *
     *  @param[in] energy     the energy
     */
    const matrix::Matrix< std::complex< double > >&
    u_matrix( double energy) {

      return std::visit( [&] ( auto&& calculator ) -> decltype(auto) {

                                 return calculator.u_matrix( energy, this->channels(),
                                                             this->resonanceTable() );
                               },
                               this->calculator_ );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const SpinGroup& left, const SpinGroup& right ) {

      return std::tie( left.channels(), left.resonanceTable() ) ==
             std::tie( right.channels(), right.resonanceTable() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const SpinGroup& left, const SpinGroup& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
