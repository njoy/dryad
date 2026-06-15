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

    #include "njoy/dryad/resonances/ResonanceTable/src/processTable.hpp"
    #include "njoy/dryad/resonances/ResonanceTable/src/verifyTable.hpp"
    #include "njoy/dryad/resonances/ResonanceTable/src/verifyCompatibility.hpp"

  public:

    /* constructor */

    #include "njoy/dryad/resonances/ResonanceTable/src/ctor.hpp"

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
     */
    bool hasChannel( const id::ChannelID& id ) const {

      auto iter = std::lower_bound( this->channels().begin(), this->channels().end(), id );
      return iter != this->channels().end() && *iter == id;
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
