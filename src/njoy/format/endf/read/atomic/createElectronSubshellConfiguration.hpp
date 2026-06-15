#ifndef NJOY_FORMAT_ENDF_READ_ATOMIC_CREATEELECTRONSUBSHELLCONFIGURATION
#define NJOY_FORMAT_ENDF_READ_ATOMIC_CREATEELECTRONSUBSHELLCONFIGURATION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/atomic/ElectronSubshellConfiguration.hpp"
#include "njoy/format/endf/read/atomic/createElectronSubshellID.hpp"
#include "ENDFtk/section/28.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace atomic {

  /**
   *  @brief Create an ElectronSubshellConfiguration from an ENDF MF28 SubshellData object
   *
   *  @param[in] subshell    the parsed subshell data
   *  @param[in] normalise   option to indicate whether or not to normalise
   *                         all probability data
   */
  inline dryad::atomic::ElectronSubshellConfiguration
  createElectronSubshellConfiguration( const ENDFtk::section::Type< 28 >::SubshellData& subshell,
                                       bool normalise ) {

    dryad::id::ElectronSubshellID identifier = createElectronSubshellID( subshell.subshellDesignator() );
    double energy = subshell.subshellBindingEnergy();
    double population = subshell.numberSubshellElectrons();
    if ( subshell.numberTransitions() == 0 ) {

      return dryad::atomic::ElectronSubshellConfiguration( identifier, energy, population );
    }
    else {

      std::vector< dryad::atomic::RadiativeTransitionData > radiative;
      std::vector< dryad::atomic::NonRadiativeTransitionData > nonradiative;
      for ( const auto& transition : subshell.transitions() ) {

        if ( transition.isRadiative() ) {

          radiative.emplace_back( createElectronSubshellID( transition.secondarySubshellDesignator() ),
                                  transition.transitionProbability(),
                                  transition.transitionEnergy() );
        }
        else {

          nonradiative.emplace_back( createElectronSubshellID( transition.secondarySubshellDesignator() ),
                                     createElectronSubshellID( transition.tertiarySubshellDesignator() ),
                                     transition.transitionProbability(),
                                     transition.transitionEnergy() );
        }
      }

      return dryad::atomic::ElectronSubshellConfiguration( identifier, energy, population,
                                                           std::move( radiative ),
                                                           std::move( nonradiative ),
                                                           normalise );
    }
  }

} // atomic namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
