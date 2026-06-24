#ifndef NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATA
#define NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECREATEANGULARDISTRIBUTIONCOVARIANCEDATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceData.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "njoy/format/gendf/read/covariance/createAngularDistributionCovarianceMatrix.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {
namespace covariance {

  /**
   *  @brief Create an AngularDistributionCovarianceData from an unparsed ENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed ENDF material
   */
  inline std::optional< dryad::covariance::AngularDistributionCovarianceData >
  createAngularDistributionCovarianceData( const dryad::id::ParticleID& projectile,
                                           const dryad::id::ParticleID& target,
                                           const dryad::ReferenceFrame& frame,
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
} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
