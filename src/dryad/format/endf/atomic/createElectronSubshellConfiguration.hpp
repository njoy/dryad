#ifndef NJOY_DRYAD_FORMAT_ENDF_ATOMIC_CREATEELECTRONSUBSHELLCONFIGURATION
#define NJOY_DRYAD_FORMAT_ENDF_ATOMIC_CREATEELECTRONSUBSHELLCONFIGURATION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/atomic/createElectronSubshellID.hpp"
#include "dryad/atomic/ElectronSubshellConfiguration.hpp"
#include "ENDFtk/section/28.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace atomic {

  /**
   *  @brief Create an ElectronSubshellConfiguration from an ENDF MF28 SubshellData object
   */
  dryad::atomic::ElectronSubshellConfiguration
  createElectronSubshellConfiguration( const ENDFtk::section::Type< 28 >::SubshellData& subshell ) {

    id::ElectronSubshellID identifier = createElectronSubshellID( subshell.subshellDesignator() );
    double energy = subshell.subshellBindingEnergy();
    double population = subshell.numberSubshellElectrons();
    if ( subshell.numberTransitions() == 0 ) {

      return dryad::atomic::ElectronSubshellConfiguration( identifier, energy, population );
    }
    else {

      double total = std::accumulate( subshell.transitionProbabilities().begin(),
                                      subshell.transitionProbabilities().end(), 0. );

      std::vector< dryad::atomic::RadiativeTransitionData > radiative;
      std::vector< dryad::atomic::NonRadiativeTransitionData > nonradiative;
      for ( const auto& transition : subshell.transitions() ) {

        if ( transition.isRadiative() ) {

          radiative.emplace_back( createElectronSubshellID( transition.secondarySubshellDesignator() ),
                                  transition.transitionProbability() / total,
                                  transition.transitionEnergy() );
        }
        else {

          nonradiative.emplace_back( createElectronSubshellID( transition.secondarySubshellDesignator() ),
                                     createElectronSubshellID( transition.tertiarySubshellDesignator() ),
                                     transition.transitionProbability() / total,
                                     transition.transitionEnergy() );
        }
      }

      return dryad::atomic::ElectronSubshellConfiguration( identifier, energy, population,
                                                           std::move( radiative ),
                                                           std::move( nonradiative ) );
    }
  }

} // atomic namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
