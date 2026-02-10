#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATECROSSSECTIONCOVARIANCEDATA
#define NJOY_DRYAD_FORMAT_ENDF_CREATECROSSSECTIONCOVARIANCEDATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceData.hpp"
#include "njoy/dryad/format/endf/covariance/createCrossSectionCovarianceMatrix.hpp"
#include "njoy/dryad/format/endf/ReactionInformation.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace covariance {

  /**
   *  @brief Create a CrossSectionCovarianceData from an unparsed ENDF material
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed ENDF material
   */
  inline std::optional< dryad::covariance::CrossSectionCovarianceData >
  createCrossSectionCovarianceData( const id::ParticleID& projectile,
                                    const id::ParticleID& target,
                                    const ENDFtk::tree::Material& material ) {

    std::optional< dryad::covariance::CrossSectionCovarianceData > covariances = std::nullopt;

    auto mat = material.materialNumber();

    if ( material.hasFile( 33 ) ) {

      Log::info( "Reading cross section covariance data" );

      std::vector< dryad::covariance::CrossSectionCovarianceMatrix > matrices;
      matrices.reserve( material.file( 33 ).sectionNumbers().size() );
      for ( auto mt : material.file( 33 ).sectionNumbers() ) {

        if ( ! endf::ReactionInformation::isDerived( mt ) ) {

          id::ReactionID row( projectile, target, adjustScatterLevel( projectile, target, mt ) );

          auto section = material.section( 33, mt ).parse< 33 >();
          for ( const auto& block : section.reactions() ) {

            if ( block.numberExplicit() != 0 ) {

              auto mat1 = block.MAT1();
              auto mt1 = block.MT1();

              if ( mat1 == 0 || mat1 == mat ) {

                id::ReactionID column = id::ReactionID( projectile, target, adjustScatterLevel( projectile, target, mt1 ) );
                if ( row == column ) {

                  Log::info( "Reading data for MT{}", mt );
                  auto data = covariance::createCrossSectionCovarianceMatrix( row, block );
                  std::move( data.begin(), data.end(), std::back_inserter( matrices ) );
                }
                else {

                  Log::info( "Reading cross term for MT{} and MT{}", mt, mt1 );
                  auto data = covariance::createCrossSectionCovarianceMatrix( row, column, block );
                  std::move( data.begin(), data.end(), std::back_inserter( matrices ) );
                }
              }
              else {

                Log::warning( "Skipping cross-material term MAT{} MT{} vs MAT{} MT{}, contact a developer",
                              mat, mt, mat1, mt1 );
              }

            }
            else {

              Log::warning( "No explicit covariance components are defined for MT{}, skipping for now", mt );
            }
          }
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
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
