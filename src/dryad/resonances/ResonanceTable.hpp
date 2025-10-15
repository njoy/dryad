#ifndef NJOY_DRYAD_RESONANCES_RESONANCETABLE
#define NJOY_DRYAD_RESONANCES_RESONANCETABLE

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "dryad/id/ChannelID.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief A table of resonance parameters for a set of channels
   *
   *  The table contains resonance energies and reduced amplitude widths,
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
     *  @brief Return the resonance energies
     */
    const std::vector< double >& energies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the reduced width amplitudes
     */
    const std::vector< std::vector< double > >& reducedWidthAmplitudes() const {

      return this->amplitudes_;
    }

    /**
     *  @brief Return the number of channels in the table
     */
    std::size_t numberChannels() const { return this->channels().size(); }

    /**
     *  @brief Return the number of resonances int he table
     */
    std::size_t numberResonances() const { return this->energies().size(); }

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
