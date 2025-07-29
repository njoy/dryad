#ifndef NJOY_DRYAD_FORMAT_ENDF_ATOMIC_CREATEENDFSUBSHELLDATA
#define NJOY_DRYAD_FORMAT_ENDF_ATOMIC_CREATEENDFSUBSHELLDATA

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/atomic/ElectronSubshellConfiguration.hpp"
#include "dryad/format/endf/atomic/createEndfSubshellDesignator.hpp"
#include "ENDFtk/section/28.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace atomic {

  /**
   *  @brief Create an ENDF MF28 SubshellData object from a ElectronSubshellConfiguration object
   *
   *  @param[in] subshell    the subshell data
   */
  ENDFtk::section::Type< 28 >::SubshellData
  createEndfSubshellData( const dryad::atomic::ElectronSubshellConfiguration& subshell ) {

    unsigned int designator = createEndfSubshellDesignator( subshell.identifier() );
    double energy = subshell.bindingEnergy();
    double population = subshell.population();
    if ( subshell.numberTransitions() == 0 ) {

      return ENDFtk::section::Type< 28 >::SubshellData( designator, energy, population );
    }
    else {

      std::vector< unsigned int > originating;
      std::vector< unsigned int > emitting;
      std::vector< double > probabilities;
      std::vector< double > energies;
      for ( const auto& transition : subshell.radiativeTransitions() ) {

        originating.emplace_back( createEndfSubshellDesignator( transition.originatingShell() ) );
        emitting.emplace_back( 0 );
        probabilities.emplace_back( transition.probability() );
        energies.emplace_back( transition.energy().has_value() ? transition.energy().value() : 0. );
      }
      for ( const auto& transition : subshell.nonRadiativeTransitions() ) {

        originating.emplace_back( createEndfSubshellDesignator( transition.originatingShell() ) );
        emitting.emplace_back( createEndfSubshellDesignator( transition.emittingShell() ) );
        probabilities.emplace_back( transition.probability() );
        energies.emplace_back( transition.energy().has_value() ? transition.energy().value() : 0. );
      }

      return ENDFtk::section::Type< 28 >::SubshellData( designator, energy, population,
                                                        std::move( originating ),
                                                        std::move( emitting ),
                                                        std::move( energies ),
                                                        std::move( probabilities ) );
    }
  }

} // atomic namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
