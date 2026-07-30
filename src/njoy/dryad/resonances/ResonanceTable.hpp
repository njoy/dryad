#ifndef NJOY_DRYAD_RESONANCES_RESONANCETABLE
#define NJOY_DRYAD_RESONANCES_RESONANCETABLE

// system includes
#include <algorithm>
#include <numeric>
#include <vector>

// other includes
#include "tools/apply_permutation.hpp"
#include "njoy/dryad/id/ChannelID.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A table of parameters for a set of channels
   *
   *  The table contains level energies and reduced width amplitudes,
   *  all given as column data.
   */
  class ResonanceTable {

    /* fields */

    std::vector< id::ChannelID > channels_;
    std::vector< double > energies_;
    std::vector< std::vector< double > > amplitudes_;

    /* auxiliary functions */

    /**
     *  @brief Process the data before storing it in the table
     *
     *  @param[in] channels   the channel identifiers (nc values)
     *  @param[in] widths     the tabulated average widths (nc values)
     *  @param[in] spacings   the average level spacing
     */
    static auto processTable( std::vector< id::ChannelID > channels,
                              std::vector< double > energies,
                              std::vector< std::vector< double > > amplitudes ) {

      // verify if the channels are sorted by channel id
      if ( ! std::is_sorted( channels.begin(), channels.end() ) ) {

        // get the order
        std::vector< std::size_t > order( channels.size() );
        std::iota( order.begin(), order.end(), 0 );
        std::sort( order.begin(), order.end(),
                   [&] ( auto&& i, auto&& j ) { return channels[i] < channels[j]; } );

        // sort the channels and perform a permutation on the columns
        std::sort( channels.begin(), channels.end() );
        tools::apply_permutation( amplitudes, order );
      }

      // verify if the energies are sorted
      if ( ! std::is_sorted( energies.begin(), energies.end() ) ) {

        // get the order
        std::vector< std::size_t > order( energies.size() );
        std::iota( order.begin(), order.end(), 0 );
        std::sort( order.begin(), order.end(),
                   [&] ( auto&& i, auto&& j ) { return energies[i] < energies[j]; } );

        // sort the energies and perform a permutation on each column
        std::sort( energies.begin(), energies.end() );
        if ( amplitudes.size() == 1 ) {

          tools::apply_permutation( amplitudes.front(), order );
        }
        else {

          for ( auto& column : amplitudes ) {

            auto temp = order;
            tools::apply_permutation( column, temp );
          }
        }
      }

      return std::make_tuple( std::move( channels ), std::move( energies ), std::move( amplitudes ) );
    }

    /**
     *  @brief Process a table without parameters
     *
     *  @param[in] channels   the channel identifiers (nc values)
     */
    static auto processTable( std::vector< id::ChannelID > channels ) {

      std::vector< double > energies;
      std::vector< std::vector< double > > amplitudes( channels.size() );

      return processTable( std::move( channels ),
                           std::move( energies ),
                           std::move( amplitudes ) );
    }

    /**
     *  @brief Verify if 2 tables can be added together
     *
     *  @param[in] left    the table on the left
     *  @param[in] right   the table on the right
     */
    static void verifyCompatibility( const ResonanceTable& left, const ResonanceTable& right ) {

      // if there are common energies between the two tables: check for common channels
      std::vector< double > intersection( std::min( left.energies().size(), right.energies().size() ) );
      auto iter = std::set_intersection( left.energies().begin(), left.energies().end(),
                                         right.energies().begin(), right.energies().end(),
                                         intersection.begin() );
      if ( iter != intersection.begin() ) {

        std::vector< std::size_t > left_indices;
        std::vector< std::size_t > right_indices;
        for ( double energy : intersection ) {

          auto left_iter = std::lower_bound( left.energies().begin(), left.energies().end(), energy );
          auto right_iter = std::lower_bound( right.energies().begin(), right.energies().end(), energy );
          left_indices.emplace_back( std::distance( left.energies().begin(), left_iter ) );
          right_indices.emplace_back( std::distance( right.energies().begin(), right_iter ) );
        }

        for ( unsigned int i = 0; i < left.channels().size(); ++i ) {

          auto id = left.channels()[i];

          if ( right.hasChannel( id ) ) {

            auto channel_iter = std::lower_bound( right.channels().begin(), right.channels().end(), id );
            auto index = std::distance( right.channels().begin(), channel_iter );
            for ( unsigned int j = 0; j < intersection.size(); ++j ) {

              if ( left.reducedWidthAmplitudes()[i][left_indices[j]] != 0
                   && right.reducedWidthAmplitudes()[index][right_indices[j]] != 0 ) {

                Log::error( "Found a channel where both tables have a non-zero width for a common level energy" );
                Log::info( "Channel: {}", id.symbol() );
                Log::info( "Energy: {}", intersection[j] );
                throw std::exception();
              }
            }
          }
        }
      }
    }

    /**
     *  @brief Basic verification of the table
     *
     *  @param[in] channels   the channel identifiers (nc values)
     *  @param[in] widths     the tabulated average widths (nc values)
     *  @param[in] spacings   the average level spacing
     */
    static void verifyTable( const std::vector< id::ChannelID >& channels,
                             const std::vector< double >& energies,
                             const std::vector< std::vector< double > >& amplitudes ) {

      std::size_t nc = channels.size();
      std::size_t ne = energies.size();

      if ( nc  == 0 ) {

        Log::error( "At least one channel should be defined" );
        Log::info( "Number channels: {}", nc );
        throw std::exception();
      }

      auto energy = std::adjacent_find( energies.begin(), energies.end() );
      if ( energy != energies.end() ) {

        Log::warning( "The energies are not unique" );

        std::vector< double > duplicates;
        duplicates.insert( std::lower_bound( duplicates.begin(), duplicates.end(), *energy ), *energy );
        energy = std::adjacent_find( energy + 1, energies.end() );
        while ( energy != energies.end() ) {

          duplicates.insert( std::lower_bound( duplicates.begin(), duplicates.end(), *energy ), *energy );
          energy = std::adjacent_find( energy + 1, energies.end() );
        }
        duplicates.erase( std::unique( duplicates.begin(), duplicates.end() ), duplicates.end() );

        for ( double value : duplicates ) {

          Log::info( "The energy = {} appears more than once", value );
        }
      }

      auto channel = std::adjacent_find( channels.begin(), channels.end() );
      if ( channel != channels.end() ) {

        Log::error( "The channels are not unique" );
        Log::info( "The channel = {} appears more than once", channel->symbol() );
        throw std::exception();
      }

      if ( nc != amplitudes.size() ) {

        Log::error( "The number of channel identifiers and the number of columns of "
                    "reduced width amplitudes is not as expected" );
        Log::info( "Number channel identifiers: {}", nc );
        Log::info( "Number columns: {}", amplitudes.size() );
        throw std::exception();
      }

      for ( unsigned int i = 0; i < nc; ++i ) {

        if ( ne != amplitudes[i].size() ) {

          Log::error( "The number of reduced width amplitudes for channel \'{}\' is not as expected" );
          Log::info( "Number widths: {}", amplitudes[i].size() );
          Log::info( "Expected number: {}", ne );
          throw std::exception();
        }
      }
    }

    /* constructor */

    /**
     *  @brief Private intermediate constructor
     */
    ResonanceTable( std::tuple< std::vector< id::ChannelID >,
                                std::vector< double >,
                                std::vector< std::vector< double > > >&& data ) :
        channels_( std::move( std::get< 0 >( data ) ) ),
        energies_( std::move( std::get< 1 >( data ) ) ),
        amplitudes_( std::move( std::get< 2 >( data ) ) ) {

      this->verifyTable( this->channels(), this->energies(),
                         this->reducedWidthAmplitudes() );
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ResonanceTable() = default;

    ResonanceTable( const ResonanceTable& ) = default;
    ResonanceTable( ResonanceTable&& ) = default;

    ResonanceTable& operator=( const ResonanceTable& ) = default;
    ResonanceTable& operator=( ResonanceTable&& ) = default;

    /**
     *  @brief Constructor
     *
     *  The energies and channels do not have to be sorted (they will be sorted
     *  upon construction).
     *
     *  @param[in] channels     the channel identifiers (nc values)
     *  @param[in] energies     the level energies (ne values)
     *  @param[in] amplitudes   the reduced width amplitudes (nc arrays of ne values)
     */
    ResonanceTable( std::vector< id::ChannelID > channels,
                    std::vector< double > energies,
                    std::vector< std::vector< double > > amplitudes ) :
        ResonanceTable( processTable( std::move( channels ),
                                      std::move( energies ),
                                      std::move( amplitudes ) ) ) {}

    /**
     *  @brief Constructor
     *
     *  The energies do not have to be sorted (they will be sorted upon construction).
     *
     *  @param[in] channel      the channel identifier
     *  @param[in] energies     the level energies
     *  @param[in] amplitudes   the reduced width amplitudes
     */
    ResonanceTable( id::ChannelID channel,
                    std::vector< double > energies,
                    std::vector< double > amplitudes ) :
        ResonanceTable( std::vector< id::ChannelID >{ std::move( channel ) },
                        std::move( energies ),
                        std::vector< std::vector< double > >{ std::move( amplitudes ) } ) {}

    /**
     *  @brief Constructor for an empty table
     *
     *  @param[in] channels   the channel identifiers (nc values)
     */
    ResonanceTable( std::vector< id::ChannelID > channels ) :
        ResonanceTable( processTable( std::move( channels ) ) ) {}

    /**
     *  @brief Constructor for an empty table
     *
     *  @param[in] channel   the channel identifier
     */
    ResonanceTable( id::ChannelID channel ) :
        ResonanceTable( std::vector< id::ChannelID >{ std::move( channel ) } ) {}

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
     *  @brief Return the level energies
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the level energies
     */
    std::vector< double >& energies() {

      return this->energies_;
    }

    /**
     *  @brief Return the reduced width amplitudes
     */
    const std::vector< std::vector< double > >& reducedWidthAmplitudes() const {

      return this->amplitudes_;
    }

    /**
     *  @brief Return the reduced width amplitudes
     */
    std::vector< std::vector< double > >& reducedWidthAmplitudes() {

      return this->amplitudes_;
    }

    /**
     *  @brief Return the number of channels in the table
     */
    std::size_t numberChannels() const { return this->channels().size(); }

    /**
     *  @brief Return the number of level energies in the table
     */
    std::size_t numberEnergies() const { return this->energies().size(); }

    /**
     *  @brief Return whether or not a given channel is present
     *
     *  @param[in] id   the channel identifier
     */
    bool hasChannel( const id::ChannelID& id ) const {

      auto iter = std::lower_bound( this->channels().begin(), this->channels().end(), id );
      return iter != this->channels().end() && *iter == id;
    }

    /**
     *  @brief Return whether or not a given energy is present
     *
     *  @param[in] energy   the energy value
     */
    bool hasEnergy( double energy ) const {

      auto iter = std::lower_bound( this->energies().begin(), this->energies().end(), energy );
      return iter != this->energies().end() && *iter == energy;
    }

    /**
     *  @brief Inplace merge of two tables
     *
     *  When the two tables contain the same channel, the tables can only be merged
     *  if, for every common level energy between the two tables, one of the tables
     *  has a zero width value.
     *
     *  @param[in] right   the table to be merged with
     */
    ResonanceTable& operator+=( const ResonanceTable& right ) {

      // check if both tables can be merged
      verifyCompatibility( *this, right );

      // loop over the channels and add a column in the correct spot if required
      std::vector< std::size_t > indices;
      for ( const auto& id : right.channels() ) {

        auto iter = std::lower_bound( this->channels().begin(), this->channels().end(), id );
        auto index = std::distance( this->channels().begin(), iter );
        indices.emplace_back( index );
        if ( ! ( iter != this->channels().end() && *iter == id ) ) {

          this->channels().insert( iter, id );
          this->reducedWidthAmplitudes().insert( this->reducedWidthAmplitudes().begin() + index,
                                                 std::vector< double >( this->numberEnergies(), 0. ) );
        }
      }

      // go over all resonances in the other table
      for ( unsigned int i = 0; i < right.energies().size(); ++i ) {

        // the current energy
        auto energy = right.energies()[i];

        // look for the energy and determine the index of the row
        auto iter = std::lower_bound( this->energies().begin(), this->energies().end(), energy );
        auto row = std::distance( this->energies().begin(), iter );

        // insert a row if the energy is not present yet
        if ( ! ( iter != this->energies().end() && *iter == energy ) ) {

          this->energies().insert( iter, energy );
          for ( auto& column : this->reducedWidthAmplitudes() ) {

            column.insert( column.begin() + row, 0. );
          }
        }

        // assign amplitudes
        for ( unsigned int j = 0; j < right.numberChannels(); ++j ) {

          if ( right.reducedWidthAmplitudes()[j][i] != 0. ) {

            this->reducedWidthAmplitudes()[indices[j]][row] = right.reducedWidthAmplitudes()[j][i];
          }
        }
      }

      return *this;
    }

    /**
     *  @brief Merge two tables together
     *
     *  @param[in] right   the table to be merged with
     */
    ResonanceTable operator+( const ResonanceTable& right ) const {

      ResonanceTable result = *this;
      result += right;
      return result;
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const ResonanceTable& left, const ResonanceTable& right ) {

      return std::tie( left.channels(), left.energies(),
                       left.reducedWidthAmplitudes() ) ==
             std::tie( right.channels(), right.energies(),
                       right.reducedWidthAmplitudes() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const ResonanceTable& left, const ResonanceTable& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
