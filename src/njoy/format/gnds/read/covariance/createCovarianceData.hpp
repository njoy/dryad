#ifndef NJOY_FORMAT_GNDS_READ_COVARIANCE_CREATECOVARIANCEDATA
#define NJOY_FORMAT_GNDS_READ_COVARIANCE_CREATECOVARIANCEDATA

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/CovarianceData.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "njoy/format/gnds/read/covariance/createCrossSectionCovarianceMatrix.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace covariance {

  /**
   *  @brief Create covariance data from GNDS covariance suite
   *
   *  @param[in] projectile    the projectile identifier
   *  @param[in] target        the target identifier
   *  @param[in] covariances   the GNDS covariance suite node
   */
  inline dryad::covariance::CovarianceData
  createCovarianceData(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const pugi::xml_node& covariances ) {

    // check that this is a valid covariance sections node
    throwExceptionOnWrongNode( covariances, "covarianceSuite" );

    //! @todo verify that the projectile and target are the ones defined in the covariance suite?

    Log::info( "Reading covariance data" );
    std::vector< dryad::covariance::CrossSectionCovarianceMatrix > xs_covariances;

    auto node = covariances.child( "covarianceSections" );
    for ( pugi::xml_node matrix = node.child( "covarianceSection" ); matrix;
          matrix = matrix.next_sibling( "covarianceSection" ) ) {

      auto row = matrix.child( "rowData" );
      auto column = matrix.child( "columnData" );
      auto sum = matrix.child( "sum" );

      std::string string = row.attribute( "ENDF_MFMT" ).as_string();
      auto iter = std::find( string.begin(), string.end(), ',' );
      std::size_t index = std::distance( string.begin(), iter );

      auto type = std::stoi( string.substr( 0, index ) );
      auto reaction = std::stoi( string.substr( index + 1 ) );

      bool is_material_cross_term = false;
      if ( column ) {

        // href that do not start with $reactions# are material cross terms
        if ( strncmp( column.attribute( "href" ).as_string(), "$reactions#",11 ) != 0 ) {

          is_material_cross_term = true;
        }
      }

      if ( ! dryad::format::endf::ReactionInformation::isDerived( reaction ) ) {

        if ( type == 33 ) {

          if ( ! sum && ! is_material_cross_term ) {

            auto entries = createCrossSectionCovarianceMatrix( projectile, target, matrix );
            std::move( entries.begin(), entries.end(), std::back_inserter( xs_covariances ) );
          }
          else {

            if ( sum ) {

              Log::warning( "No explicit cross section covariance components are defined for MT{}, skipping for now", reaction );
            }
            else {

              Log::warning( "Skipping cross-material cross section covariance term for MT{}, contact a developer", reaction );
            }
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

    return dryad::covariance::CovarianceData( std::move( xs ), std::nullopt );
  }

} // covariance namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
