#ifndef NJOY_DRYAD_RESONANCES_COMPOUNDSYSTEM
#define NJOY_DRYAD_RESONANCES_COMPOUNDSYSTEM

// system includes
#include <vector>

// other includes
#include "njoy/dryad/resonances/SpinGroup.hpp"

namespace njoy {
namespace dryad {
namespace resonances {

  /**
   *  @class
   *  @brief The compound nucleus system
   */
  class CompoundSystem {

    /* fields */

    double lower_;
    double upper_;
    std::vector< SpinGroup > spin_groups_;

    std::vector< id::ReactionID > reactions_;

    /* auxiliary functions */

    /**
     *  @brief Process the spin group data
     *
     *  This function sorts the spin groups and initialises the reactions field with
     *  all reactions the spin group contributes to.
     */
    void processSpinGroups() {

      std::sort( this->spinGroups().begin(), this->spinGroups().end(),
                 [] ( auto&& left, auto&& right )
                    { return std::make_tuple( left.totalAngularMomentum(), left.parity() ) <
                             std::make_tuple( right.totalAngularMomentum(), right.parity() ); } );

      for ( const auto& group : this->spinGroups() ) {

        for ( const auto& reaction : group.reactions() ) {

          auto iter = std::lower_bound( this->reactions().begin(),
                                        this->reactions().end(), reaction );
          if ( ! ( iter != this->reactions().end() && *iter == reaction ) ) {

            this->reactions().insert( iter, reaction );
          }
        }
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    CompoundSystem() = default;

    CompoundSystem( const CompoundSystem& ) = default;
    CompoundSystem( CompoundSystem&& ) = default;

    CompoundSystem& operator=( const CompoundSystem& ) = default;
    CompoundSystem& operator=( CompoundSystem&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param[in] lowerEnergy   the lower energy limit for the compound system
     *  @param[in] upperEnergy   the upper energy limit for the compound system
     *  @param[in] spinGroups    the spin groups that make up the compound system
     */
    CompoundSystem( double lowerEnergy, double upperEnergy,
                    std::vector< SpinGroup > spinGroups ) :
        lower_( lowerEnergy ),
        upper_( upperEnergy ),
        spin_groups_( std::move( spinGroups ) ) {

      this->processSpinGroups();
    }

    /**
     *  @brief Return the lower energy limit
     */
    double lowerEnergyLimit() const {

      return this->lower_;
    }

    /**
     *  @brief Set the lower energy limit
     *
     *  @param[in] lowerEnergy   the lower energy limit for the compound system
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
     *  @param[in] upperEnergy   the upper energy limit for the compound system
     */
    void upperEnergyLimit( double upperEnergy ) {

      this->upper_ = upperEnergy;
    }

    /**
     *  @brief Return the spin groups that make up the compound system
     */
    const std::vector< SpinGroup >& spinGroups() const {

      return this->spin_groups_;
    }

    /**
     *  @brief Return the spin groups that make up the compound system
     */
    std::vector< SpinGroup >& spinGroups() {

      return this->spin_groups_;
    }

    /**
     *  @brief Set the spin groups that make up the compound system
     *
     *  @param[in] spinGroups  the spin groups
     */
    void spinGroups( std::vector< SpinGroup > spinGroups ) {

      this->spin_groups_ = std::move( spinGroups );
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

    /**
     *  @brief Calculate the cross section values at a given energy
     *
     *  @param[in] energy   the energy
     *  @param[in] xs       the cross section values
     */
    void crossSections( double energy, std::map< id::ReactionID, double >& xs ) {

      for ( auto& group : this->spinGroups() ) {

        group.crossSections( energy, xs );
      }
    }

    /**
     *  @brief Calculate the cross section values for a list of energies
     *
     *  @param[in] energies   the energy list
     *  @param[in] xs         the cross sections
     */
    void crossSections( std::vector<double>& energies, std::map< id::ReactionID, std::vector<double> >& xs ) {

      for ( auto& group : this->spinGroups() ) {

        group.crossSections( energies, xs );
      }
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator==( const CompoundSystem& left, const CompoundSystem& right ) {

      return left.spinGroups() == right.spinGroups();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the object on the left hand side
     *  @param[in] right   the object on the right hand side
     */
    friend bool operator!=( const CompoundSystem& left, const CompoundSystem& right ) {

      return ! ( left == right );
    }
  };

} // resonances namespace
} // dryad namespace
} // njoy namespace

#endif
