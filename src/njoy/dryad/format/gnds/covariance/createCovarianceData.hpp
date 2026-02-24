#ifndef NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATECOVARIANCEDATA
#define NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATECOVARIANCEDATA

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/CovarianceData.hpp"
#include "njoy/dryad/format/endf/ReactionInformation.hpp"
#include "njoy/dryad/format/gnds/covariance/createCrossSectionCovarianceMatrix.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace covariance {

  /**
   *  @brief Create covariance data from GNDS covariance sections
   *
   *  @param[in] projectile    the projectile identifier
   *  @param[in] target        the target identifier
   *  @param[in] covariances   the GNDS covariance sections node
   */
  inline dryad::covariance::CovarianceData
  createCovarianceData(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const pugi::xml_node& covariances ) {

    // check that this is a valid covariance sections node
    throwExceptionOnWrongNode( covariances, "covarianceSections" );

    std::vector< dryad::covariance::CrossSectionCovarianceMatrix > xs_covariances;

    for ( pugi::xml_node matrix = covariances.child( "covarianceSection" ); matrix;
          matrix = matrix.next_sibling( "covarianceSection" ) ) {

      auto row = matrix.child( "rowData" );
      auto sum = matrix.child( "sum" );

      std::string string = row.attribute( "ENDF_MFMT" ).as_string();
      auto iter = std::find( string.begin(), string.end(), ',' );
      std::size_t index = std::distance( string.begin(), iter );

      auto type = std::stoi( string.substr( 0, index ) );
      auto reaction = std::stoi( string.substr( index + 1 ) );

      if ( ! endf::ReactionInformation::isDerived( reaction ) ) {

        if ( type == 33 ) {

          if ( ! sum ) {

            auto entries = createCrossSectionCovarianceMatrix( projectile, target, matrix );
            std::move( entries.begin(), entries.end(), std::back_inserter( xs_covariances ) );
          }
          else {

            Log::warning( "No explicit covariance components are defined for MT{}, skipping for now", reaction );
          }
        }
        else {

          Log::warning( "Covariance matrices for MF{} are not implemented yet, skipping for now", type );
        }
      }
      else {

        Log::warning( "Skipping data for derived MT{}", reaction );
      }
    }

    std::optional< dryad::covariance::CrossSectionCovarianceData > xs = std::nullopt;
    if ( xs_covariances.size() > 0 ) {

      xs = dryad::covariance::CrossSectionCovarianceData( std::move( xs_covariances ) );
    }

    return dryad::covariance::CovarianceData( std::move( xs ) );
  }

} // covariance namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
