#ifndef NJOY_DRYAD_RESONANCES_RESONANCETABLE
#define NJOY_DRYAD_RESONANCES_RESONANCETABLE

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/apply_permutation.hpp"
#include "dryad/id/ChannelID.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A table of parameters for a set of channels
   *
   *  The table contains level energies and reduced amplitude widths,
   *  all given as column data.
   */
  class ResonanceTable {

    /* fields */

    std::vector< id::ChannelID > channels_;
    std::vector< double > energies_;
    std::vector< std::vector< double > > amplitudes_;

    /* auxiliary functions */

    #include "dryad/resonances/ResonanceTable/src/verifyTable.hpp"

  public:

    /* constructor */

    #include "dryad/resonances/ResonanceTable/src/ctor.hpp"

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
     *  @brief Return the resonance energies
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the resonance energies
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
     */
    bool hasChannel( const id::ChannelID& id ) const {

      auto iter = std::find_if( this->channels().begin(), this->channels().end(),
                                [&] ( auto&& channel ) { return channel ==id; } );
      return iter != this->channels().end();
    }

    /**
     *  @brief Return whether or not a given energy is present
     */
    bool hasEnergy( double energy ) const {

      auto iter = std::lower_bound( this->energies().begin(), this->energies().end(), energy );
      return iter != this->energies().end() && *iter == energy;
    }

    /**
     *  @brief Inplace merge of two tables
     *
     *  @param[in] right   the table to be merged with
     */
    ResonanceTable& operator+=( const ResonanceTable& right ) {

      auto nc = this->numberChannels();

      // check the channels in the table
      for ( const auto& id : right.channels() ) {

        // throw an exception if the current table has this channel already
        if ( this->hasChannel( id ) ) {

          Log::error( "Channel \'{}\' is present in both tables", id.symbol() );
          throw std::exception();
        }

        // add the channel identifier and add a column for this channel
        this->channels().emplace_back( id );
        this->reducedWidthAmplitudes().emplace_back( this->numberEnergies(), 0. );
      }

      // go over all resonances in the other table
      for ( unsigned int i = 0; i < right.energies().size(); ++i ) {

        // the current energy
        auto energy = right.energies()[i];

        // look for the energy and determine the index of the row
        auto iter = std::lower_bound( this->energies().begin(), this->energies().end(), energy );
        auto row = std::distance( this->energies().begin(), iter );

        // insert a row if the energy is not present yet
        if ( iter == this->energies().end() ||
             ( iter != this->energies().end() && *iter != energy ) ) {

          this->energies().insert( iter, energy );
          for ( auto& column : this->reducedWidthAmplitudes() ) {

            column.insert( column.begin() + row, 0. );
          }
        }

        // assign amplitudes
        for ( unsigned int j = 0; j < right.numberChannels(); ++j ) {

          this->reducedWidthAmplitudes()[nc + j][row] = right.reducedWidthAmplitudes()[j][i];
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
