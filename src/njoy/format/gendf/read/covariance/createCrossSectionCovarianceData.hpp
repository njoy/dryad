#ifndef NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECROSSSECTIONCOVARIANCEDATA
#define NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECROSSSECTIONCOVARIANCEDATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceData.hpp"
#include "njoy/format/gendf/read/covariance/createCrossSectionCovarianceMatrix.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "ENDFtk/GMaterial.hpp"
#include "ENDFtk/tree/GMaterial.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {
namespace covariance {

  /**
   *  @brief Create a CrossSectionCovarianceData from an unparsed ENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] relative     the flag to indicate whether or not the covariance data is relative
   *  @param[in] material     the unparsed ENDF material
   */
  inline std::optional< dryad::covariance::CrossSectionCovarianceData >
  createCrossSectionCovarianceData( const dryad::id::ParticleID& projectile,
                                    const dryad::id::ParticleID& target,
                                    bool relative,
                                    const ENDFtk::tree::GMaterial& material ) {

    std::optional< dryad::covariance::CrossSectionCovarianceData > covariances = std::nullopt;

    std::vector< double > boundaries;
    if ( material.hasSection( 1, 451 ) ) {

      auto section = material.section( 1, 451 ).parse< 1, 451 >();
      boundaries = createVector( section.neutronStructure() );
    }
    else {

      Log::error( "Could not find MF1 MT451 section with the energy group boundaries" );
      throw std::exception();
    }

    if ( material.hasFile( 33 ) ) {

      Log::info( "Reading cross section covariance data" );

      std::vector< dryad::covariance::CrossSectionCovarianceMatrix > matrices;
      matrices.reserve( material.file( 33 ).sectionNumbers().size() );
      for ( auto mt : material.file( 33 ).sectionNumbers() ) {

        if ( ! endf::ReactionInformation::isDerived( mt ) ) {

          auto section = material.section( 33, mt ).parse< 33 >();
          auto data = covariance::createCrossSectionCovarianceMatrix( projectile, target, boundaries, relative, section );
          std::move( data.begin(), data.end(), std::back_inserter( matrices ) );
        }
        else {

          Log::warning( "Skipping data for derived MT{}", mt );
        }
      }

      covariances = dryad::covariance::CrossSectionCovarianceData( std::move( matrices ) );
    }

    return covariances;
  }

} // covariance namespace
} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
