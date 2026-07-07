#ifndef NJOY_FORMAT_ENDF_READ_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEDATA
#define NJOY_FORMAT_ENDF_READ_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEDATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceData.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "njoy/format/endf/read/covariance/createAngularDistributionCovarianceMatrix.hpp"
#include "njoy/format/endf/read/createReferenceFrame.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace format {
namespace endf {
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
                                           const ENDFtk::tree::Material& material ) {

    std::optional< dryad::covariance::AngularDistributionCovarianceData > covariances = std::nullopt;

    auto mat = material.materialNumber();

    if ( material.hasFile( 34 ) ) {

      Log::info( "Reading angular distribution covariance data" );

      std::vector< dryad::covariance::AngularDistributionCovarianceMatrix > matrices;
      matrices.reserve( material.file( 34 ).sectionNumbers().size() );
      for ( auto mt : material.file( 34 ).sectionNumbers() ) {

        if ( ! endf::ReactionInformation::isDerived( mt ) ) {

          dryad::id::ReactionID row( projectile, target, adjustScatterLevel( projectile, target, mt ) );

          auto section = material.section( 34, mt ).parse< 34 >();
          for ( const auto& block : section.reactions() ) {

            auto mat1 = block.MAT1();
            auto mt1 = block.MT1();

            if ( mat1 == 0 || mat1 == mat ) {

              dryad::id::ReactionID column = dryad::id::ReactionID( projectile, target,
                                                             adjustScatterLevel( projectile, target, mt1 ) );

              for ( const auto& legendre : block.legendreBlocks() ) {

                std::size_t l1 = legendre.firstLegendreOrder();
                std::size_t l2 = legendre.secondLegendreOrder();

                int endf_frame = legendre.referenceFrame();
                if ( endf_frame == 0 ) {

                  if ( material.hasSection( 4, mt ) ) {

                    auto mf4_section = material.section( 4, mt ).parse< 4 >();
                    endf_frame = mf4_section.referenceFrame();
                  }
                  else {

                    Log::error( "No MF4 MT{} section found, cannot determine covariance reference frame", mt );
                    throw std::exception();
                  }
                }

                if ( legendre.numberDataBlocks() != 0 ) {

                  if ( row == column ) {

                    if ( l1 == l2 ) {

                      Log::info( "Reading data for MT{} P{}", mt, l1 );
                    }
                    else {

                      Log::info( "Reading cross term for MT{} P{} and P{}", mt, l1, l2 );
                    }
                  }
                  else {

                    if ( l1 == l2 ) {

                      Log::info( "Reading cross term for MT{} and MT{} P{}", mt, mt1, l1 );
                    }
                    else {

                      Log::info( "Reading cross term for MT{} and MT{} P{} and P{}", mt, mt1, l1, l2 );
                    }
                  }

                  for ( const auto& matrix : legendre.data() ) {

                    dryad::ReferenceFrame frame = createReferenceFrame( endf_frame );
                    matrices.emplace_back( createAngularDistributionCovarianceMatrix( frame, row, column, l1, l2, matrix ) );
                  }
                }
                else {

                  Log::warning( "No explicit covariance components are defined for MT{}, skipping for now", mt );
                }
              }
            }
            else {

              Log::warning( "Skipping cross-material term MAT{} MT{} vs MAT{} MT{}, contact a developer",
                            mat, mt, mat1, mt1 );
            }
          }
        }
        else {

          Log::warning( "Skipping data for derived MT{}", mt );
        }
      }

      covariances = dryad::covariance::AngularDistributionCovarianceData( std::move( matrices ) );
    }

    return covariances;
  }

} // covariance namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
