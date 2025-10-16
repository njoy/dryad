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

    /* fields */

    std::vector< Channel > channels_;
    ResonanceTable resonances_;

    /* auxiliary functions */

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

      return this->resonances_;
    }

    /**
     *  @brief Return the resonance table
     */
    ResonanceTable& resonanceTable() {

      return this->resonances_;
    }

    /**
     *  @brief Set the resonance table
     *
     *  @param table  the resonance table
     */
    void resonanceTable( ResonanceTable table ) {

      this->resonances_ = std::move( table );
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
