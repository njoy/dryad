#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATETHERMALSCATTERING
#define NJOY_DRYAD_FORMAT_GNDS_CREATETHERMALSCATTERING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/format/gnds/thermal/createCoherentElasticScattering.hpp"
#include "njoy/dryad/format/gnds/thermal/createIncoherentElasticScattering.hpp"
#include "njoy/dryad/ThermalScattering.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create a ThermalScattering instance from a GNDS xml document
   *
   *  @param[in] document   the GNDS xml document
   *  @param[in] style      the gnds style to process (default is eval)
   */
  inline ThermalScattering
  createThermalScattering( const pugi::xml_document& document,
                           const std::string& style = "eval" ) {

   auto suite = document.child( "reactionSuite" );

    if ( suite ) {

      std::optional< dryad::thermal::CoherentElasticScattering > coherent = std::nullopt;
      std::optional< dryad::thermal::IncoherentElasticScattering > incoherent = std::nullopt;

      // loop over reaction nodes
      auto reactions = suite.child( "reactions" );
      for ( pugi::xml_node reaction = reactions.child( "reaction" );
            reaction; reaction = reaction.next_sibling( "reaction" ) ) {

        auto tsl = reaction.child( "doubleDifferentialCrossSection" )
                           .find_child_by_attribute( "label", style.c_str() );
        if ( strcmp( tsl.name(), "thermalNeutronScatteringLaw_coherentElastic" ) == 0 ) {

          coherent = thermal::createCoherentElasticScattering( tsl );
        }
        else if ( strcmp( tsl.name(), "thermalNeutronScatteringLaw_incoherentElastic" ) == 0 ) {

          incoherent = thermal::createIncoherentElasticScattering( tsl );
        }
      }

      return ThermalScattering( std::move( coherent ), std::move( incoherent ) );
    }
    else {

      Log::error( "The GNDS file does not contain thermal scattering data" );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
