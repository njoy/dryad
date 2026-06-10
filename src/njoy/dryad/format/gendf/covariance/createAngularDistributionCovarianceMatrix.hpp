#ifndef NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEMATRIX
#define NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEMATRIX

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/covariance/AngularDistributionMetadata.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/adjustScatterLevel.hpp"
#include "ENDFtk/gsection/34g.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gendf {
namespace covariance {

  /**
   *  @brief Create a cross section covariance matrix from a GENDF MF33 section
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed ENDF material
   */
  inline std::vector< dryad::covariance::AngularDistributionCovarianceMatrix >
  createAngularDistributionCovarianceMatrix(
      id::ParticleID projectile, id::ParticleID target,
      std::vector< double > boundaries,
      ReferenceFrame frame,
      ENDFtk::section::GType< 34 >& section ) {

    std::vector< dryad::covariance::AngularDistributionCovarianceMatrix > covariances;

    int mt = section.sectionNumber();
    bool relative = static_cast<bool>( section.covarianceFormat() );

    id::ReactionID row( projectile, target, 
                        adjustScatterLevel( projectile, target, 
                                            mt == 251 ? 2 : mt ) );

    decltype(auto) data = section.angularCovariance();

    unsigned int size = boundaries.size() - 1;
    matrix::Matrix< double > matrix( size, size );
    for ( unsigned int i = 0; i < size; ++i ) {

      for ( unsigned int j = 0; j < size; ++j ) {

        matrix( i, j ) = data[i][j];
      }
    }

    using AngularDistributionMetadata = dryad::covariance::AngularDistributionMetadata;

    std::size_t row_moment = static_cast< std::size_t >( section.primaryLegendre() );
    std::size_t col_moment = static_cast< std::size_t >( section.secondaryLegendre() );
    if ( row_moment == col_moment ) {

      Log::info( "Reading data for MT{} P{}", mt, row_moment );
      covariances.emplace_back( frame, 
                                AngularDistributionMetadata( { row }, { row_moment }, boundaries ),
                                std::move( matrix ), 
                                relative);
    }
    else {

      Log::info( "Reading data for MT{} cross term for P{} and P{}", mt, row_moment, col_moment );
      covariances.emplace_back( frame, 
                                AngularDistributionMetadata( { row }, { row_moment }, boundaries ),
                                AngularDistributionMetadata( { row }, { col_moment }, boundaries ),
                                std::move( matrix ), 
                                relative);
    }

    return covariances;
  }

} // covariance namespace
} // gendf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif // NJOY_DRYAD_FORMAT_GENDF_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEMATRIX