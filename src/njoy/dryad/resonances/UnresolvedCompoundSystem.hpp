#ifndef NJOY_DRYAD_RESONANCES_UNRESOLVEDCOMPOUNDSYSTEM
#define NJOY_DRYAD_RESONANCES_UNRESOLVEDCOMPOUNDSYSTEM

//system includes
#include <vector>

//other includes
#include "njoy/dryad/resonances/UnresolvedSpinGroup.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   * @class
   * @brief The compound nucleus system for unresolved resonance region
   *
   */
  class UnresolvedCompoundSystem {


    private:
      /* fields */

      double lower_;
      double upper_;
      std::vector< UnresolvedSpinGroup > unresolved_spin_groups_;
      std::vector< id::ReactionID > reactions_;

      /* auxiliary functions */
      #include "njoy/dryad/resonances/UnresolvedCompoundSystem/src/processSpinGroups.hpp"

    public:

      /* constructor */
      #include "njoy/dryad/resonances/CompoundSystem/src/ctor.hpp"

      /**
       * @brief Return the lower energy limit
       */
      double lowerEnergyLimit() const {

        return this->lower_;
      }

      /**
       *  @brief Set the lower energy limit
       *
       *  @param[in] lowerEnergy   the lower energy limit for the unresolved compound system
       */
      void lowerEnergyLimit( double lowerEnergy ) {

        this->lower_ = lowerEnergy;
      }

      /**
       *  @brief Return the upper energy limit
       */
      double upperEnergyLimit() const {

        return this->upper_;
      }

      /**
       *  @brief Set the upper energy limit
       *
       *  @param[in] upperEnergy   the upper energy limit for the unresolved compound system
       */
      void upperEnergyLimit( double upperEnergy ) {

        this->upper_ = upperEnergy;
      }

      /**
       *  @brief Return the spin groups that make up the unresolved compound system
       */
      const std::vector< UnresolvedSpinGroup >& spinGroups() const {

        return this->unresolved_spin_groups_;
      }

      /**
       *  @brief Return the spin groups that make up the compound system
       */
      std::vector< UnresolvedSpinGroup >& spinGroups() {

        return this->unresolved_spin_groups_;
      }

      /**
       *  @brief Set the spin groups that make up the compound system
       *
       *  @param spinGroups  the spin groups
       */
      void spinGroups( std::vector< UnresolvedSpinGroup > spinGroups ) {
                                                                                
        this->unresolved_spin_groups_ = std::move( spinGroups );
        this->processSpinGroups();
      }
                                                                                
      /**
       *  @brief Return the reactions to which this compound system contributes
       */
      const std::vector< id::ReactionID >& reactions() const {
                                                                                
        return this->reactions_;
      }
                                                                                
      /**
       *  @brief Return the reactions to which this compound system contributes
       */
      std::vector< id::ReactionID >& reactions() {
                                                                                
        return this->reactions_;
      }

      //  TODO
      // /**
      //  *  @brief Calculate the cross section values at a given energy
      //  *
      //  *  @param[in] energy   the energy
      //  *  @param[in] xs       the cross section values
      //  */
      //  TODO

      //  TODO
      // /**
      //  *  @brief Calculate the cross section values for a list of energies
      //  *
      //  *  @param[in] energies   the energy list
      //  *  @param[in] xs         the cross sections
      //  */
      //  TODO

      /**
       *  @brief Equality comparison
       *
       *  @param[in] left    the object on the left hand side
       *  @param[in] right   the object on the right hand side
       */
      friend bool operator==( const UnresolvedCompoundSystem& left, const UnresolvedCompoundSystem& right ) {

        return left.spinGroups() == right.spinGroups();
      }

      /**
       *  @brief Inequality comparison
       *
       *  @param[in] left    the object on the left hand side
       *  @param[in] right   the object on the right hand side
       */
      friend bool operator!=( const UnresolvedCompoundSystem& left, const UnresolvedCompoundSystem& right ) {

        return ! ( left == right );
      }
  };




  };
}
}
}

#endif
