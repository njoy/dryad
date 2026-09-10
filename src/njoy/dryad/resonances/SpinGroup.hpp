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

    /**
     *  @brief Transform the channel data into a set of channels and a resonance parameter
     *         table
     *
     *  @param[in] channels     the channel data in the spingroup
     */
    static auto createData( std::vector< ChannelData > channel_data ) {

      std::vector< Channel > channels( channel_data.size() );
      channels.reserve( channel_data.size() );
      std::transform( channel_data.begin(), channel_data.end(), channels.begin(),
                      [] ( auto&& channel ) { return std::move( channel.first ); } );

      ResonanceTable table = channel_data.front().second;
      for ( unsigned int i = 1; i < channel_data.size(); ++i ) {

        table += channel_data[i].second;
      }

      return std::make_tuple( std::move( channels ), std::move( table ) );
    }

    /**
     *  @brief Process the channel data
     *
     *  This function sorts the channels and initialises the reactions field with
     *  all reactions the spin group contributes to.
     */
    void processChannels() {

      std::sort( this->channels().begin(), this->channels().end(),
                 [] ( auto&& left, auto&& right )
                    { return left.identifier() < right.identifier(); } );

      this->reactions().clear();
      for ( const auto& channel : this->channels() ) {

        auto id = channel.identifier().reaction();
        auto iter = std::lower_bound( this->reactions().begin(),
                                      this->reactions().end(), id );
        if ( ! ( iter != this->reactions().end() && *iter == id ) ) {

          this->reactions().insert( iter, id );
        }
      }
    }

    /**
     *  @brief Select the calculator to be used
     *
     *  @param[in] formalism    the r matrix formalism option to be applied
     *  @param[in] boundary     the boundary condition option to be applied
     *  @param[in] channels     the channels in the spingroup
     *  @param[in] resonances   the resonance table of the spingroup
     */
    static Calculator selectCalculator( const Formalism& formalism,
                                        const BoundaryCondition& boundary,
                                        const std::vector< Channel >& channels,
                                        const ResonanceTable& table ) {

      switch ( formalism ) {

        case Formalism::ReichMoore : return calculator::ReichMoore( boundary, channels );
        case Formalism::GeneralRMatrix : return calculator::GeneralRMatrix( boundary, channels, table );
        default : {

          throw std::runtime_error( "Unknown formalism type" );
        }
      }
    }

    /**
     *  @brief Perform basic verification on the spin group
     *
     *  @param[in] channels   the channels in the spin group
     *  @param[in] table      the resonance parameter table
     */
    static void verifySpinGroup( const std::vector< Channel >& channels,
                                 const ResonanceTable& table ) {

      std::size_t nc = channels.size();

      if ( nc  == 0 ) {

        Log::error( "At least one channel should be defined" );
        Log::info( "Number channels: {}", nc );
        throw std::exception();
      }
      if ( nc != table.numberChannels() ) {

        Log::error( "The number of channels and the number of columns in the table are inconsistent" );
        Log::info( "Number channels: {}", channels.size() );
        Log::info( "Number columns in the table: {}", table.numberChannels() );
        throw std::exception();
      }

      auto iter = std::adjacent_find( channels.begin(), channels.end(),
                                      [] ( auto&& left, auto&& right )
                                         { return left.identifier() == right.identifier(); } );
      if ( iter != channels.end() ) {

        Log::error( "Channels in the spin group do not seem to be unique." );
        Log::info( "Channel \'{}\' is present at least twice", iter->identifier().symbol() );
        throw std::exception();
      }
    }

    /* constructor */

    /**
     *  @brief Private intermediate constructor
     */
    SpinGroup( std::tuple< std::vector< Channel >, ResonanceTable > data,
               const Formalism& formalism,
               const BoundaryCondition& boundary ) :
        SpinGroup( std::move( std::get< 0 >( data ) ),
                   std::move( std::get< 1 >( data ) ),
                   formalism, boundary ) {}

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    SpinGroup() = default;

    SpinGroup( const SpinGroup& ) = default;
    SpinGroup( SpinGroup&& ) = default;

    SpinGroup& operator=( const SpinGroup& ) = default;
    SpinGroup& operator=( SpinGroup&& ) = default;

    /**
     *  @brief Constructor
     *
     *  If the channels are not sorted, they will get sorted through the order
     *  of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical
     *  sorting order).
     *
     *  @param[in] channels     the channels in the spingroup
     *  @param[in] resonances   the resonance table of the spingroup
     *  @param[in] formalism    the r matrix formalism option to be applied
     *  @param[in] boundary     the boundary condition option to be applied
     */
    SpinGroup( std::vector< Channel > channels,
               ResonanceTable resonances,
               const Formalism& formalism,
               const BoundaryCondition& boundary ) :
        channels_( std::move( channels ) ),
        table_( std::move( resonances ) ),
        formalism_( formalism ),
        boundary_condition_( boundary ) {

      this->processChannels();
      this->calculator_ = selectCalculator( this->formalism(), this->boundaryCondition(),
                                            this->channels(), this->resonanceTable() );
      verifySpinGroup( this->channels(), this->resonanceTable() );
    }

    /**
     *  @brief Constructor
     *
     *  If the channels are not sorted, they will get sorted through the order
     *  of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical
     *  sorting order).
     *
     *  @param[in] channels     the channel data in the spingroup
     *  @param[in] formalism    the r matrix formalism option to be applied
     *  @param[in] boundary     the boundary condition option to be applied
     */
    SpinGroup( std::vector< ChannelData > channels,
               const Formalism& formalism,
               const BoundaryCondition& boundary ) :
        SpinGroup( createData( std::move( channels ) ), formalism, boundary ) {}

    /**
     *  @brief Return the number of channels
     */
    std::size_t numberChannels() const { return this->channels().size(); }

    /**
     *  @brief Return the number of level energies
     */
    std::size_t numberEnergies() const { return this->resonanceTable().numberEnergies(); }

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
