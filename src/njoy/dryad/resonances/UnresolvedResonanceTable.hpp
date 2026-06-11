#ifndef NJOY_DRYAD_RESONANCES__UNRESOLVEDRESONANCETABLE
#define NJOY_DRYAD_RESONANCES__UNRESOLVEDRESONANCETABLE

#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>
#include <optional>

#include "tools/apply_permutation.hpp"
#include "njoy/dryad/resonances/TabulatedLevelSpacing.hpp"
#include "njoy/dryad/resonances/TabulatedAverageWidths.hpp"
#include "njoy/dryad/id/ChannelID.hpp"


namespace njoy{
namespace dryad{

namespace resonances{

    /**
     * @class
     * @brief A resonance table of average resonance parameters corresponding 
     *        to a Jpi quantum number set for use in the unresolved resonance
     *        region
     */

    class UnresolvedResonanceTable {

      private:

        std::vector< id::ChannelID > channels_;
        std::vector< TabulatedAverageWidths > widths_;
        TabulatedLevelSpacing spacings_;

        /* auxiliary functions */
        #include "njoy/dryad/resonances/UnresolvedResonanceTable/src/processTable.hpp"
        #include "njoy/dryad/resonances/UnresolvedResonanceTable/src/verifyTable.hpp"
        #include "njoy/dryad/resonances/UnresolvedResonanceTable/src/iterator.hpp"
        #include "njoy/dryad/resonances/UnresolvedResonanceTable/src/unifyEnergyGrids.hpp"


    

      public:
        /* constructor */
        #include "njoy/dryad/resonances/UnresolvedResonanceTable/src/ctor.hpp"

        /* methods */

        /**
        * @brief return the number of channels in the table
        */
        int numberChannels() const {
          return this->channels_.size();
        }

        /**
        * @brief return the channel identifiers
        */
        const std::vector< id::ChannelID >& channels() const { 
          return this->channels_;
        }

        /**
        * @brief Return the channel identifiers
        */

        std::vector< id::ChannelID >& channels() { 
          return this->channels_;
        }

        /**
        * @brief Returns if the table has a given channel
        */
        bool hasChannel( const id::ChannelID& channel ) const {
          return std::find( channels_.begin(), channels_.end(), channel ) != channels_.end();
        }

        /**
        * @brief Return the TabulatedAverageWidths for a given channel
        */
        const TabulatedAverageWidths& widths( const id::ChannelID& channel ) const {
          auto iter = this->iterator( channel );
          if ( iter == this->channels().cend() || *iter != channel ) {
            Log::error( "Channel {} not found in table", channel.symbol() );
            throw std::exception();
          }
          return this->widths()[ std::distance( this->channels().cbegin(), iter ) ];
        }

        /**
        * @brief Return the TabulatedAverageWidths for a given channel
        */
        TabulatedAverageWidths& widths( const id::ChannelID& channel ) {
          auto iter = this->iterator( channel );
          if ( iter == this->channels().cend() || *iter != channel ) {
            Log::error( "Channel {} not found in table", channel.symbol() );
            throw std::exception();
          }
          else {
            return this->widths()[ std::distance( this->channels().cbegin(), iter ) ];
          }
        }

        /**
        * @brief Return the average widths
        */
        const std::vector< TabulatedAverageWidths >& widths() const {
          return this->widths_;
        }

        /**
        * @brief Return the average widths
        */
        std::vector< TabulatedAverageWidths >& widths() {
          return this->widths_;
        }

        /**
        * @brief Return the level spacings
        */
        const TabulatedLevelSpacing& spacings() const {
          return this->spacings_;
        }

        /**
        * @brief Return the level spacings
        */
        TabulatedLevelSpacing& spacings() {
          return this->spacings_;
        }

        /**
        * @brief Equality comparison
        *
        * @param[in] left    the object on the left hand side
        * @param[in] right   the object on the right hand side
        */
        friend bool operator==( const UnresolvedResonanceTable& left, const UnresolvedResonanceTable& right ) {
          return std::tie( left.channels(), left.widths(), left.spacings() ) ==
                 std::tie( right.channels(), right.widths(), right.spacings() );
        }

        /**
        * @brief Inequality comparison
        *
        * @param[in] left    the object on the left hand side
        * @param[in] right   the object on the right hand side
        */
        friend bool operator!=( const UnresolvedResonanceTable& left, const UnresolvedResonanceTable& right ) {
          return ! ( left == right );
        }

    };
} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif