#ifndef NJOY_DRYAD_RESONANCES_SPINGROUP
#define NJOY_DRYAD_RESONANCES_SPINGROUP

// system includes
#include <algorithm>
#include <variant>
#include <vector>

// other includes
#include "dryad/resonances/Channel.hpp"
#include "dryad/resonances/ResonanceTable.hpp"
#include "dryad/resonances/BoundaryCondition.hpp"
#include "dryad/resonances/Formalism.hpp"
#include "dryad/resonances/calculator.hpp"

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

    /* type aliases */

    using Calculator = std::variant< calculator::ReichMoore, calculator::GeneralRMatrix >;

    /* fields */

    std::vector< Channel > channels_;
    ResonanceTable table_;
    Formalism formalism_;
    BoundaryCondition boundary_condition_;

    Calculator calculator_;
    std::vector< id::ReactionID > reactions_;

    /* auxiliary functions */

    #include "dryad/resonances/SpinGroup/src/createData.hpp"
    #include "dryad/resonances/SpinGroup/src/processChannels.hpp"
    #include "dryad/resonances/SpinGroup/src/verifySpinGroup.hpp"
    #include "dryad/resonances/SpinGroup/src/selectCalculator.hpp"

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
      this->processChannels();
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
     *  @brief Return the formalism
     */
    const Formalism& formalism() const {

      return this->formalism_;
    }

    /**
     *  @brief Return the boundary condition option
     */
    const BoundaryCondition boundaryCondition() const {

      return this->boundary_condition_;
    }

    /**
     *  @brief Return the total angular momentum J of the spin group
     */
    double totalAngularMomentum() const {

      return this->channels().front().quantumNumbers().totalAngularMomentum();
    }

    /**
     *  @brief Return the parity
     */
    short parity() const {

      return this->channels().front().quantumNumbers().parity();
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
     *  @brief Calculate the cross section values at a given energy
     *
     *  @param[in] energy   the energy
     *  @param[in] xs       the cross section values
     */
    void crossSections( double energy, std::map< id::ReactionID, double >& xs ) {

      std::visit( [&] ( auto&& calculator ) {

                    return calculator.crossSections( energy, this->channels(),
                                                     this->resonanceTable(), xs );
                  },
                  this->calculator_ );
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
