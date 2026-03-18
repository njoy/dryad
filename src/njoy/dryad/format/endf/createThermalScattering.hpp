#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATETHERMALSCATTERING
#define NJOY_DRYAD_FORMAT_ENDF_CREATETHERMALSCATTERING

// system includes

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/format/endf/thermal/createCoherentElasticScattering.hpp"
#include "njoy/dryad/format/endf/thermal/createIncoherentElasticScattering.hpp"
#include "njoy/dryad/format/endf/createDocumentation.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a ThermalScattering instance from an unparsed ENDF material
   *
   *  @param[in] material    the unparsed ENDF material
   */
  inline ThermalScattering
  createThermalScattering( const ENDFtk::tree::Material& material ) {

    if ( material.hasSection( 7, 2 ) || material.hasSection( 7, 4 ) ) {

      auto information = material.section( 1, 451 ).parse< 1, 451 >();
      Documentation documentation = createDocumentation( information );

      std::optional< dryad::thermal::CoherentElasticScattering > coherent = std::nullopt;
      std::optional< dryad::thermal::IncoherentElasticScattering > incoherent = std::nullopt;
      if ( material.hasSection( 7, 2 ) ) {

        using CoherentElasticScatteringType = std::optional< dryad::thermal::CoherentElasticScattering >;
        using IncoherentElasticScatteringType = std::optional< dryad::thermal::IncoherentElasticScattering >;
        using CoherentElastic = ENDFtk::section::Type< 7, 2 >::CoherentElastic;
        using IncoherentElastic = ENDFtk::section::Type< 7, 2 >::IncoherentElastic;
        using MixedElastic = ENDFtk::section::Type< 7, 2 >::MixedElastic;

        auto createCoherentElastic = tools::overload{

          [&] ( const CoherentElastic& law ) -> CoherentElasticScatteringType {

            return thermal::createCoherentElasticScattering( law );
          },
          [&] ( const IncoherentElastic& law ) -> CoherentElasticScatteringType {

            return std::nullopt;
          },
          [&] ( const MixedElastic& law ) -> CoherentElasticScatteringType {

            return thermal::createCoherentElasticScattering( law.coherent() );
          }
        };

        auto createIncoherentElastic = tools::overload{

          [&] ( const CoherentElastic& law ) -> IncoherentElasticScatteringType {

            return std::nullopt;
          },
          [&] ( const IncoherentElastic& law ) -> IncoherentElasticScatteringType {

            return thermal::createIncoherentElasticScattering( law );
          },
          [&] ( const MixedElastic& law ) -> IncoherentElasticScatteringType {

            return thermal::createIncoherentElasticScattering( law.incoherent() );
          }
        };

        auto section = material.section( 7, 2 ).parse< 7, 2 >();
        coherent = std::visit( createCoherentElastic, section.scatteringLaw() );
        incoherent = std::visit( createIncoherentElastic, section.scatteringLaw() );
      }

      return ThermalScattering( std::move( documentation ),
                                std::move( coherent ),
                                std::move( incoherent ) );
    }
    else {

      Log::error( "The ENDF file does not contain thermal scattering data" );
      throw std::exception();
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
