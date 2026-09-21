#ifndef NJOY_FORMAT_GNDS_READ_CREATETHERMALSCATTERING
#define NJOY_FORMAT_GNDS_READ_CREATETHERMALSCATTERING

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/format/gnds/StyleType.hpp"
#include "njoy/format/gnds/read/convertEnergy.hpp"
#include "njoy/format/gnds/read/createStyleLabel.hpp"
#include "njoy/format/gnds/read/createDocumentation.hpp"
#include "njoy/format/gnds/read/thermal/createCoherentElasticScattering.hpp"
#include "njoy/format/gnds/read/thermal/createIncoherentElasticScattering.hpp"
#include "njoy/format/gnds/read/thermal/createIncoherentInelasticScattering.hpp"

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
  createThermalScattering( const pugi::xml_document& document,
                           const std::optional< double >& upper = std::nullopt,
                           const StyleType& style = StyleType::Evaluation ) {

     auto suite = document.child( "reactionSuite" );

    if ( suite ) {

      std::optional< dryad::thermal::CoherentElasticScattering > coherent = std::nullopt;
      std::optional< dryad::thermal::IncoherentElasticScattering > incoherent = std::nullopt;
      std::optional< dryad::thermal::IncoherentInelasticScattering > inelastic = std::nullopt;

      double lower_limit = 1e-5;
      double upper_limit = upper.has_value() ? upper.value() : 10.;
      double projectileMass = 1.00866491574;

      auto styles = suite.child( "styles" );
      std::string style_label = createStyleLabel( suite.child( "styles" ), style );
      auto documentation = styles.find_child_by_attribute( "label", style_label.c_str() ).child( "documentation" );

      dryad::Documentation docs = createDocumentation( documentation, style_label );

      auto reactions = suite.child( "reactions" );
      auto reaction = reactions.find_child_by_attribute( "reaction", "ENDF_MT", "4" );
      if ( reaction ) {

        auto tsl = reaction.child( "doubleDifferentialCrossSection" )
                           .find_child_by_attribute( "label", style_label.c_str() );

        if ( ! upper.has_value() ) {

          auto emax = tsl.child( "scatteringAtoms" )
                         .find_child_by_attribute( "scatteringAtom", "primaryScatterer", "true" )
                         .child( "e_max" );
          upper_limit = emax.attribute( "value" ).as_double();
          convertEnergy( upper_limit, emax.attribute( "unit" ).as_string() );
        }
        inelastic = thermal::createIncoherentInelasticScattering( lower_limit, upper_limit,
                                                                  projectileMass, tsl );
      }

      // loop over reaction nodes and look for elastic
      for ( pugi::xml_node reaction = reactions.child( "reaction" );
            reaction; reaction = reaction.next_sibling( "reaction" ) ) {

        auto tsl = reaction.child( "doubleDifferentialCrossSection" )
                           .find_child_by_attribute( "label", style_label.c_str() );
        if ( strcmp( tsl.name(), "thermalNeutronScatteringLaw_coherentElastic" ) == 0 ) {

          coherent = thermal::createCoherentElasticScattering( lower_limit, upper_limit, tsl );
        }
        else if ( strcmp( tsl.name(), "thermalNeutronScatteringLaw_incoherentElastic" ) == 0 ) {

          incoherent = thermal::createIncoherentElasticScattering( lower_limit, upper_limit, tsl );
        }
      }

      return dryad::ThermalScattering( std::move( docs ),
                                       std::move( coherent ),
                                       std::move( incoherent ),
                                       std::move( inelastic ) );
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
