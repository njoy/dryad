#ifndef NJOY_DRYAD_FORMAT_GNDS_ATOMIC_CREATEELECTRONSUBSHELLCONFIGURATION
#define NJOY_DRYAD_FORMAT_GNDS_ATOMIC_CREATEELECTRONSUBSHELLCONFIGURATION

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/atomic/ElectronSubshellConfiguration.hpp"
#include "dryad/format/gnds/createEnergy.hpp"
#include "dryad/format/gnds/atomic/createElectronSubshellID.hpp"
#include "pugixml.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace atomic {

  /**
   *  @brief Create an ElectronSubshellConfiguration from a GNDS configuration node
   */
  dryad::atomic::ElectronSubshellConfiguration
  createElectronSubshellConfiguration( const pugi::xml_node& configuration ) {

    // shell id and population are attributes on the configuration node
    id::ElectronSubshellID identifier = createElectronSubshellID( configuration.attribute( "subshell" ).as_string() );
    double population = configuration.attribute( "electronNumber" ).as_double();

    // energy and unit are attributes on the double node in the bindingEnergy node
    //! @todo we do not verify the eval style
    pugi::xml_node node = configuration.child( "bindingEnergy" ).child( "double" );
    double energy = createEnergy( node.attribute( "value" ).as_double(), node.attribute( "unit" ).as_string() );

    // look for transitions
    pugi::xml_node decay = configuration.child( "decayData" );
    if ( ! decay ) {

      return dryad::atomic::ElectronSubshellConfiguration( identifier, energy, population );
    }
    else {

      std::vector< dryad::atomic::RadiativeTransitionData > radiative;
      std::vector< dryad::atomic::NonRadiativeTransitionData > nonradiative;

      pugi::xml_node modes = decay.child( "decayModes" );
      for ( pugi::xml_node mode = modes.child( "decayMode" ); mode; mode = mode.next_sibling(  "decayMode"  ) ) {

        // transition probability is an attribute on the double node in the probability node
        double probability = mode.child( "probability" ).child( "double" ).attribute( "value" ).as_double();

        // helper lambda function
        auto isVacancyProduct = [] ( pugi::xml_node product ) {

          return product.attribute( "pid" ).as_string()[0] == 'O';
        };

        // go to the products and see if we have a radiative or non-radiative transition
        pugi::xml_node products = mode.child( "decayPath" ).child( "decay" ).child( "products" );
        if ( products.find_child_by_attribute( "pid", "photon" ) ) {

          // get the originating shell id
          id::ElectronSubshellID originating = 
          createRadiativeTransitionElectronSubshellID( products.find_child( isVacancyProduct ).attribute( "pid" ).as_string() );

          // GNDS does not store the transition energy
          radiative.emplace_back( originating, probability );
        }
        else {

          // get the originating and emitting shell id
          auto pair = 
          createNonRadiativeTransitionElectronSubshellID( products.find_child( isVacancyProduct ).attribute( "pid" ).as_string() );

          // GNDS does not store the transition energy
          nonradiative.emplace_back( pair.first, pair.second, probability );
        }
      }
      return dryad::atomic::ElectronSubshellConfiguration( identifier, energy, population,
                                                           std::move( radiative ),
                                                           std::move( nonradiative ) );
    }
  }

} // atomic namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
