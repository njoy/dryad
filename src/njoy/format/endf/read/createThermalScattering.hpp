#ifndef NJOY_FORMAT_ENDF_READ_CREATETHERMALSCATTERING
#define NJOY_FORMAT_ENDF_READ_CREATETHERMALSCATTERING

// system includes

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/format/endf/read/thermal/createCoherentElasticScattering.hpp"
#include "njoy/format/endf/read/thermal/createIncoherentElasticScattering.hpp"
#include "njoy/format/endf/read/thermal/createIncoherentInelasticScattering.hpp"
#include "njoy/format/endf/read/createDocumentation.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create a ThermalScattering instance from an unparsed ENDF material
   *
   *  @param[in] material   the unparsed ENDF material
   *  @param[in] upper      the optional upper energy limit (default: use the upper
   *                        energy limit of the evaluation)
   */
  inline dryad::ThermalScattering
  createThermalScattering( const ENDFtk::tree::Material& material,
                           std::optional< double > upper = std::nullopt ) {

    if ( material.hasSection( 7, 2 ) || material.hasSection( 7, 4 ) ) {

      auto information = material.section( 1, 451 ).parse< 1, 451 >();
      dryad::Documentation documentation = createDocumentation( information );

      double lower_limit = 1e-5;
      double upper_limit = upper.has_value() ? upper.value() : 10.;

      std::optional< dryad::thermal::CoherentElasticScattering > coherent = std::nullopt;
      std::optional< dryad::thermal::IncoherentElasticScattering > incoherent = std::nullopt;
      std::optional< dryad::thermal::IncoherentInelasticScattering > inelastic = std::nullopt;

      if ( material.hasSection( 7, 4 ) ) {

        auto section = material.section( 7, 4 ).parse< 7, 4 >();

        if ( ! upper.has_value() ) {

          upper_limit = section.constants().upperEnergyLimit();
        }
        inelastic = thermal::createIncoherentInelasticScattering( lower_limit, upper_limit, section );
      }

      if ( material.hasSection( 7, 2 ) ) {

        using CoherentElasticScatteringType = std::optional< dryad::thermal::CoherentElasticScattering >;
        using IncoherentElasticScatteringType = std::optional< dryad::thermal::IncoherentElasticScattering >;
        using CoherentElastic = ENDFtk::section::Type< 7, 2 >::CoherentElastic;
        using IncoherentElastic = ENDFtk::section::Type< 7, 2 >::IncoherentElastic;
        using MixedElastic = ENDFtk::section::Type< 7, 2 >::MixedElastic;

        auto createCoherentElastic = tools::overload{

          [&] ( const CoherentElastic& law ) -> CoherentElasticScatteringType {

            return thermal::createCoherentElasticScattering( lower_limit, upper_limit, law );
          },
          [&] ( const IncoherentElastic& ) -> CoherentElasticScatteringType {

            return std::nullopt;
          },
          [&] ( const MixedElastic& law ) -> CoherentElasticScatteringType {

            return thermal::createCoherentElasticScattering( lower_limit, upper_limit, law.coherent() );
          }
        };

        auto createIncoherentElastic = tools::overload{

          [&] ( const CoherentElastic& ) -> IncoherentElasticScatteringType {

            return std::nullopt;
          },
          [&] ( const IncoherentElastic& law ) -> IncoherentElasticScatteringType {

            return thermal::createIncoherentElasticScattering( lower_limit, upper_limit, law );
          },
          [&] ( const MixedElastic& law ) -> IncoherentElasticScatteringType {

            return thermal::createIncoherentElasticScattering( lower_limit, upper_limit, law.incoherent() );
          }
        };

        auto section = material.section( 7, 2 ).parse< 7, 2 >();
        coherent = std::visit( createCoherentElastic, section.scatteringLaw() );
        incoherent = std::visit( createIncoherentElastic, section.scatteringLaw() );
      }

      return dryad::ThermalScattering( std::move( documentation ),
                                       std::move( coherent ),
                                       std::move( incoherent ),
                                       std::move( inelastic ) );
    }
    else {

      Log::error( "The ENDF file does not contain thermal scattering data" );
      throw std::exception();
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
