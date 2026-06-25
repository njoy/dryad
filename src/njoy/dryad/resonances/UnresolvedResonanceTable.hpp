#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDRESONANCETABLE
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDRESONANCETABLE

// system includes
#include <vector>
#include <algorithm>
#include <tuple>

// other includes
#include "tools/apply_permutation.hpp"
#include "njoy/dryad/resonances/TabulatedLevelSpacing.hpp"
#include "njoy/dryad/resonances/TabulatedAverageWidths.hpp"
#include "njoy/dryad/id/ChannelID.hpp"

namespace njoy{
namespace dryad{
namespace resonances{

  /**
   *  @class
   *  @brief A table of unresolved average parameters for a set of channels
   */
  class UnresolvedResonanceTable {

    /* fields */

    std::vector< id::ChannelID > channels_;
    std::vector< TabulatedAverageWidths > widths_;
    TabulatedLevelSpacing spacings_;

    /* auxiliary functions */

    /**
     *  @brief Process the data before storing it in the table
     *
     *  @param[in] channels   the channel identifiers (nc values)
     *  @param[in] widths     the tabulated average widths (nc values)
     *  @param[in] spacings   the average level spacing
     */
    static auto processTable( std::vector< id::ChannelID > channels,
                              std::vector< TabulatedAverageWidths > widths,
                              TabulatedLevelSpacing spacings ) {

      // verify if the channels are sorted by channel id
      if ( ! std::is_sorted( channels.begin(), channels.end() ) ) {

        std::vector< std::size_t > order( channels.size() );
        std::iota( order.begin(), order.end(), 0 );
        std::sort( order.begin(), order.end(),
                   [&] ( auto i, auto j ) { return channels[i] < channels[j]; } );

        std::sort( channels.begin(), channels.end() );
        tools::apply_permutation( widths,   order );
      }

      return std::make_tuple( std::move( channels ), std::move( widths ), std::move( spacings ) );
    }

    /**
     *  @brief Basic verification of the table
     *
     *  @param[in] channels   the channel identifiers (nc values)
     *  @param[in] widths     the tabulated average widths (nc values)
     *  @param[in] spacings   the average level spacing
     */
    static void verifyTable( const std::vector< id::ChannelID >& channels,
                             const std::vector< TabulatedAverageWidths >& widths,
                             const TabulatedLevelSpacing& spacings ) {

      std::size_t nc = channels.size();

      if ( nc == 0 ) {

        Log::error( "At least one channel should be defined" );
        Log::info( "Number channels: {}", nc );
        throw std::exception();
      }

      auto channel = std::adjacent_find( channels.begin(), channels.end() );
      if ( channel != channels.end() ) {

        Log::error( "The channels are not unique" );
        Log::info( "The channel = {} appears more than once", channel->symbol() );
        throw std::exception();
      }

      if ( nc != widths.size() ) {

        Log::error( "The number of channel identifiers and the number of average "
                    "widths is not as expected" );
        Log::info( "Number channel identifiers: {}", nc );
        Log::info( "Number average widths: {}", widths.size() );
        throw std::exception();
      }
    }

    /**
     *  @brief Return an iterator for the channel identifier (using lower_bound)
     */
    auto iterator( const id::ChannelID& id ) const {

      return std::lower_bound( this->channels().begin(), this->channels().end(), id );
    }

    /* constructors */

    /**
     *  @brief Private intermediate constructor
     */
    UnresolvedResonanceTable( std::tuple< std::vector< id::ChannelID >,
                                          std::vector< TabulatedAverageWidths >,
                                          TabulatedLevelSpacing >&& data ) :
        channels_( std::move( std::get< 0 >( data ) ) ),
        widths_( std::move( std::get< 1 >( data ) ) ),
        spacings_( std::move( std::get< 2 >( data ) ) ) {

      verifyTable( this->channels(), this->widths(), this->spacings() );
    }

  public:

    /* constructor */

    /**
     * @brief Default constructor (for pybind11 purposes only)
     */
    UnresolvedResonanceTable() = default;

    UnresolvedResonanceTable( const UnresolvedResonanceTable& ) = default;
    UnresolvedResonanceTable( UnresolvedResonanceTable&& ) = default;

    UnresolvedResonanceTable& operator=( const UnresolvedResonanceTable& ) = default;
    UnresolvedResonanceTable& operator=( UnresolvedResonanceTable&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] channels   the channel identifiers (nc values)
     *  @param[in] widths     the tabulated average widths (nc values)
     *  @param[in] spacings   the average level spacing
     */
    UnresolvedResonanceTable( std::vector< id::ChannelID > channels,
                              std::vector< TabulatedAverageWidths > widths,
                              TabulatedLevelSpacing spacings ) :
        UnresolvedResonanceTable( processTable( std::move( channels ),
                                                std::move( widths ),
                                                std::move( spacings ) ) ) {}

    /* methods */

    /**
     *  @brief Return the channel identifiers
     */
    const std::vector< id::ChannelID >& channels() const {

      return this->channels_;
    }

    /**
     *  @brief Return the channel identifiers
     */
    std::vector< id::ChannelID >& channels() {

      return this->channels_;
    }

    /**
     *  @brief Return the average widths
     */
    const std::vector< TabulatedAverageWidths >& widths() const {

      return this->widths_;
    }

    /**
     *  @brief Return the average widths
     */
    std::vector< TabulatedAverageWidths >& widths() {

      return this->widths_;
    }

    /**
     *  @brief Return the level spacings
     */
    const TabulatedLevelSpacing& spacings() const {

      return this->spacings_;
    }

    /**
     *  @brief Return the level spacings
     */
    TabulatedLevelSpacing& spacings() {

      return this->spacings_;
    }

    /**
     *  @brief Return the number of channels in the table
     */
    std::size_t numberChannels() const { return this->channels().size(); }

    /**
     *  @brief Return whether or not a given channel is present
     *
     *  @param[in] id   the channel identifier
     */
    bool hasChannel( const id::ChannelID& id ) const {

      auto iter = this->iterator( id );
      return iter != this->channels().end() && *iter == id;
    }

    /**
     *  @brief Return the average widths for a given channel
     *
     *  @param[in] id   the channel identifier
     */
    const TabulatedAverageWidths& channelWidths( const id::ChannelID& id ) const {

      auto iter = this->iterator( id );
      if ( iter == this->channels().end() || *iter != id ) {

        Log::error( "Channel {} not found in table", id.symbol() );
        throw std::exception();
      }
      return this->widths()[ std::distance( this->channels().begin(), iter ) ];
    }

    /**
     *  @brief Return the average widths for a given channel
     *
     *  @param[in] id   the channel identifier
     */
    TabulatedAverageWidths& channelWidths( const id::ChannelID& id ) {

      return const_cast< TabulatedAverageWidths& > ( const_cast< const UnresolvedResonanceTable& >( *this ).channelWidths( id ) );
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const UnresolvedResonanceTable& left, const UnresolvedResonanceTable& right ) {

      return std::tie( left.channels(), left.widths(), left.spacings() ) ==
             std::tie( right.channels(), right.widths(), right.spacings() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const UnresolvedResonanceTable& left, const UnresolvedResonanceTable& right ) {

      return ! ( left == right );
    }
  };

} // namespace resonances
} // namespace dryad
} // namespace njoy

#endif
