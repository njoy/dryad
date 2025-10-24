#ifndef NJOY_DRYAD_RESONANCES_SPINGROUP
#define NJOY_DRYAD_RESONANCES_SPINGROUP

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "dryad/resonances/Channel.hpp"
#include "dryad/resonances/ResonanceTable.hpp"

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

    /* fields */

    std::vector< Channel > channels_;
    ResonanceTable table_;

    /* auxiliary functions */

    #include "dryad/resonances/SpinGroup/src/createData.hpp"
    #include "dryad/resonances/SpinGroup/src/verifySpinGroup.hpp"

  public:

    /* constructor */

    #include "dryad/resonances/SpinGroup/src/ctor.hpp"

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
     *  @param channels  the channels
     */
    void channels( std::vector< Channel > channels ) {

      this->channels_ = std::move( channels );
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
     *  @param table  the resonance table
     */
    void resonanceTable( ResonanceTable table ) {

      this->table_ = std::move( table );
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
