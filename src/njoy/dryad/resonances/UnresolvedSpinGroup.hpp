#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDSPINGROUP
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDSPINGROUP

// system includes
#include <vector>
#include <algorithm>

// other includes
#include "njoy/dryad/resonances/UnresolvedChannel.hpp"
#include "njoy/dryad/resonances/UnresolvedResonanceTable.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class UnresolvedSpinGroup
   *  @brief A spin group corresponding to a Jpi quantum number set in the
   *         unresolved resonance range.
   */
  class UnresolvedSpinGroup {

    //! @todo URR-specific calculator and sampler types, once their interfaces are settled. Something like:
    // using Calculator = std::variant< calculator::HauserFeshbach, calculator::MoldauerWidthFluctuation, ... >;
    // using Sampler    = std::variant< sampler::GOESampler, sampler::WignerDistributionSampler, ... >;

    std::vector< UnresolvedChannel > channels_;
    UnresolvedResonanceTable table_;
    std::vector< id::ReactionID > reactions_;

    //! @todo fields for calculator and sampler
    // Calculator calculator_;
    // Sampler sampler_;

    /* auxiliary functions */

    /**
     *  @brief Perform basic verification on the spin group
     *
     *  @param[in] channels   the channels in the spin group
     *  @param[in] table      the resonance parameter table
     */
    static void verifySpinGroup( const std::vector< UnresolvedChannel >& channels,
                                 const UnresolvedResonanceTable& table ) {

      std::size_t nc = channels.size();
      if ( nc == 0 ) {

        Log::error( " At least one channel must be present in a spin group." );
        Log::info( "Number of channels: {}", nc );
        throw std::exception();
      }
      if ( nc != table.numberChannels() ) {

        Log::error( " The number of channels in the resonance table must match the number of channels in the spin group." );
        Log::info( "Number of channels in spin group: {}", nc );
        Log::info( "Number of channels in resonance table: {}", table.numberChannels() );
        throw std::exception();
      }

      auto iter = std::adjacent_find( channels.begin(), channels.end(),
                                 [] ( auto&& left, auto&& right ) {

                                   return left.identifier() == right.identifier();
                                 } );
      if ( iter != channels.end() ) {

        Log::error( " Each channel in a spin group must have a unique identifier." );
        Log::info( "Duplicate channel identifier: {}", iter->identifier().symbol() );
        throw std::exception();
      }
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
                    { return left.identifier() < right.identifier(); }
        );

      for ( const auto& channel : this->channels() ) {

        auto id = channel.identifier().reaction();
        auto iter = std::lower_bound( this->reactions().begin(),
                                      this->reactions().end(), id );
        if ( ! ( iter != this->reactions().end() && *iter == id ) ) {

          this->reactions().insert( iter, id );
        }
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    UnresolvedSpinGroup() = default;

    UnresolvedSpinGroup( const UnresolvedSpinGroup& ) = default;
    UnresolvedSpinGroup( UnresolvedSpinGroup&& ) = default;

    UnresolvedSpinGroup& operator=( const UnresolvedSpinGroup& ) = default;
    UnresolvedSpinGroup& operator=( UnresolvedSpinGroup&& ) = default;

    /**
     *  @brief Constructor
     *
     *  If the channels are not sorted, they will get sorted through the order
     *  of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical
     *  sorting order).
     *
     * @todo a future overload may accept a calculator and/or sampler
     *       configuration once those interfaces are decided on (mirroring
     *       SpinGroup's ctor that takes a Formalism and BoundaryCondition and
     *       calls selectCalculator). For now the spin group only stores the
     *       channels and the average parameter table.
     *
     *  @param[in] channels     the channels in the spin group
     *  @param[in] resonances   the unresolved resonance table of the spin group
     */
    UnresolvedSpinGroup( std::vector< UnresolvedChannel > channels,
                         UnresolvedResonanceTable resonances ) :
                      channels_( std::move( channels ) ),
                      table_( std::move( resonances ) ) {

      this->processChannels();
      verifySpinGroup( this->channels(), this->resonanceTable() );
    }

    /* methods */

    /**
     *  @brief Return the channels in the spin group
     */
    const std::vector< UnresolvedChannel >& channels() const {

      return this->channels_;
    }

    /**
     *  @brief Return the channels in the spin group
     */
    std::vector< UnresolvedChannel >& channels() {

      return this->channels_;
    }

    /**
     *  @brief Set the channels in the spin group
     *
     *  @param[in] channels  the channels
     */
    void channels( std::vector< UnresolvedChannel > channels ) {

      this->channels_ = std::move( channels );
      this->processChannels();
    }

    /**
     *  @brief Return the resonance table
     */
    const UnresolvedResonanceTable& resonanceTable() const {

      return this->table_;
    }

<<<<<<< HEAD
    /**
     *  @brief Return the resonance table
     */
    UnresolvedResonanceTable& resonanceTable() {

      return this->table_;
    }

    /**
     *  @brief Set the resonance table
     *
     *  @param[in] table  the resonance table
     */
    void resonanceTable( UnresolvedResonanceTable table ) {

      this->table_ = std::move( table );
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
     *  @brief Return the total angular momentum of the spin group
     */
    double totalAngularMomentum() const {

      return this->channels().front().quantumNumbers().totalAngularMomentum();
    }

    /**
     *  @brief Return the parity of the spin group
     */
    short parity() const {

      return this->channels().front().quantumNumbers().parity();
    }

    //! @todo average infinitely dilute cross sections from the average parameters.
    //        analog of SpinGroup::crossSections, but operating on the average
    //        widths and level spacings rather than per-resonance parameters.
    //        Will dispatch through the calculator variant once one exists.
    //
    // void crossSections( double energy,
    //                     std::map< id::ReactionID, double >& xs );
    //
    // void crossSections( std::vector< double >& energies,
    //                     std::map< id::ReactionID, std::vector< double > >& xs );

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left   the object on the left-hand-side
     *  @param[in] right  the object on the right-hand-side
     */
    friend bool operator==( const UnresolvedSpinGroup& left,
                            const UnresolvedSpinGroup& right ) {

      return std::tie( left.channels(), left.resonanceTable() ) ==
             std::tie( right.channels(), right.resonanceTable() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left   the object on the left-hand-side
     *  @param[in] right  the object on the right-hand-side
     */
    friend bool operator!=( const UnresolvedSpinGroup& left,
                            const UnresolvedSpinGroup& right ) {
      return ! ( left == right );
    }
  };

} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif
