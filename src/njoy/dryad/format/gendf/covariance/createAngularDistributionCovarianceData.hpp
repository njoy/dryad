#ifndef NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATA
#define NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceData.hpp"
#include "njoy/dryad/format/gendf/covariance/createAngularDistributionCovarianceMatrix.hpp"
#include "njoy/dryad/format/endf/ReactionInformation.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gendf {
namespace covariance {

  /**
   *  @brief Create an AngularDistributionCovarianceData from an unparsed ENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed ENDF material
   */
  inline std::optional< dryad::covariance::AngularDistributionCovarianceData >
  createAngularDistributionCovarianceData( const id::ParticleID& projectile,
                                    const id::ParticleID& target,
                                    const ReferenceFrame& frame,
                                    const ENDFtk::tree::GMaterial& material ) {

    std::optional< dryad::covariance::AngularDistributionCovarianceData > covariances = std::nullopt;

    std::vector< double > boundaries;
    if ( material.hasSection( 1, 451 ) ) {

      auto section = material.section( 1, 451 ).parse< 1, 451 >();
      boundaries = createVector( section.neutronStructure() );
    }
    else {

      Log::error( "Could not find MF1 MT451 section with the energy group boundaries" );
      throw std::exception();
    }

    if ( material.hasFile( 34 ) ) {

      Log::info( "Reading angular distribution covariance data" );

      std::vector< dryad::covariance::AngularDistributionCovarianceMatrix > matrices;
      matrices.reserve( material.file( 34 ).sectionNumbers().size() );
      for ( auto mt : material.file( 34 ).sectionNumbers() ) {

        auto section = material.section( 34, mt ).parse< 34 >();
        auto data = covariance::createAngularDistributionCovarianceMatrix( projectile, target, boundaries, frame, section );
        std::move( data.begin(), data.end(), std::back_inserter( matrices ) );
        
      }

      covariances = dryad::covariance::AngularDistributionCovarianceData( std::move( matrices ) );
    }

    return covariances;
  }

} // covariance namespace
} // gendf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif // NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEEDATA