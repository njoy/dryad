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
   *       unresolved resonance range.
   */

  class UnresolvedSpinGroup {
    private:

      // TODO: URR-specific calculator and sampler types, once their interfaces are settled. Something like:
      // using Calculator = std::variant< calculator::HauserFeshbach, calculator::MoldauerWidthFluctuation, ... >;
      // using Sampler    = std::variant< sampler::GOESampler, sampler::WignerDistributionSampler, ... >;

      std::vector< UnresolvedChannel > channels_;
      UnresolvedResonanceTable table_;
      std::vector< id::ReactionID > reactions_;

      // TODO:
      // Calculator calculator_;
      // Sampler sampler_;

      /* auxiliary functions */
      #include "njoy/dryad/resonances/UnresolvedSpinGroup/src/processChannels.hpp"
      #include "njoy/dryad/resonances/UnresolvedSpinGroup/src/verifySpinGroup.hpp"

      public:

        /* constructor */
        #include "njoy/dryad/resonances/UnresolvedSpinGroup/src/ctor.hpp"

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
         *  @brief Return the resonance table
         */
        const UnresolvedResonanceTable& resonanceTable() const {

          return this->table_;
        }

        /**
         *  @brief Return the resonance table
         */
        UnresolvedResonanceTable& resonanceTable() {

          return this->table_;
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
         * @brief Set the channels in the spin group
         */
        void channels( std::vector< UnresolvedChannel > channels ) {

          this->channels_ = std::move( channels );
          this->processChannels();
        }

        /**
         * @brief Set the resonance table
         */
        void resonanceTable( UnresolvedResonanceTable table ) { 

          this->table_ = std::move( table );
        }

        /**
         * @brief Return the total angular momentum of the spin group
         */
        double totalAngularMomentum() const {

          return this->channels().front().quantumNumbers().totalAngularMomentum();
        }

        /**
         * @brief Return the parity of the spin group
         */
        short parity() const {

          return this->channels().front().quantumNumbers().parity();
        }

        /**
         * @brief Return whether or not the channels in the spin group have backgrounds
         */
        bool hasChannelsWithBackground() const {
          return std::any_of( this->channels().begin(), this->channels().end(),
                              [] ( auto&& channel ) {

                                return channel.background().has_value();
                              } );
        }

        // TODO: average infinitely dilute cross sections from the average parameters.
        //       analog of SpinGroup::crossSections, but operating on the average
        //       widths and level spacings rather than per-resonance parameters.
        //       Will dispatch through the calculator variant once one exists.
        //
        // void crossSections( double energy,
        //                     std::map< id::ReactionID, double >& xs );
        //
        // void crossSections( std::vector< double >& energies,
        //                     std::map< id::ReactionID, std::vector< double > >& xs );

        /**
         * @brief Equality comparison
         * 
         * @param[in] left   the object on the left-hand-side
         * 
         * @param[in] right  the object on the right-hand-side
         */
        friend bool operator==( const UnresolvedSpinGroup& left,
                                const UnresolvedSpinGroup& right ) {

          return std::tie( left.channels(), left.resonanceTable() ) ==
                 std::tie( right.channels(), right.resonanceTable() );
        }

        /**
         * @brief Inequality comparison
         * 
         * @param[in] left   the object on the left-hand-side
         * 
         * @param[in] right  the object on the right-hand-side
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
