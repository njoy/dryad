#ifndef NJOY_FORMAT_GNDS_READ_CREATETHERMALSCATTERING
#define NJOY_FORMAT_GNDS_READ_CREATETHERMALSCATTERING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/format/gnds/read/thermal/createCoherentElasticScattering.hpp"
#include "njoy/format/gnds/read/thermal/createIncoherentElasticScattering.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create a ThermalScattering instance from a GNDS xml document
   *
   *  @param[in] lower      the lower energy limit
   *  @param[in] upper      the upper energy limit
   *  @param[in] document   the GNDS xml document
   *  @param[in] style      the gnds style to process (default is eval)
   */
  inline dryad::ThermalScattering
  createThermalScattering( double lower, double upper,
                           const pugi::xml_document& document,
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

          coherent = thermal::createCoherentElasticScattering( lower, upper, tsl );
        }
        else if ( strcmp( tsl.name(), "thermalNeutronScatteringLaw_incoherentElastic" ) == 0 ) {

          incoherent = thermal::createIncoherentElasticScattering( lower, upper, tsl );
        }
      }

      return dryad::ThermalScattering( std::move( coherent ), std::move( incoherent ) );
    }
    else {

      Log::error( "The GNDS file does not contain thermal scattering data" );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
