#ifndef NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEMATRIX
#define NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATEANGULARDISTRIBUTIONCOVARIANCEMATRIX

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/covariance/AngularDistributionMetadata.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceMatrix.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/adjustScatterLevel.hpp"
#include "ENDFtk/gsection/34g.hpp"

namespace njoy {
namespace format {
namespace gendf {
namespace read {
namespace covariance {

  /**
   *  @brief Create a cross section covariance matrix from a GENDF MF33 section
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] boundaries   the group structure
   *  @param[in] frame        the reference frame
   *  @param[in] section      the parsed ENDF MF34 section
   */
  inline std::vector< dryad::covariance::AngularDistributionCovarianceMatrix >
  createAngularDistributionCovarianceMatrix(
      dryad::id::ParticleID projectile,
      dryad::id::ParticleID target,
      std::vector< double > boundaries,
      dryad::ReferenceFrame frame,
      ENDFtk::section::GType< 34 >& section ) {

    std::vector< dryad::covariance::AngularDistributionCovarianceMatrix > covariances;

    int mt = section.sectionNumber();
    bool relative = static_cast<bool>( section.covarianceFormat() );

    dryad::id::ReactionID row( projectile, target,
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

    std::vector< std::size_t > row_moment = { static_cast< std::size_t >( section.primaryLegendre() ) };
    std::vector< std::size_t > col_moment = { static_cast< std::size_t >( section.secondaryLegendre() ) };
    if ( row_moment.front() == col_moment.front() ) {

      Log::info( "Reading data for MT{} P{}", mt, row_moment.front() );
      covariances.emplace_back( frame,
                                AngularDistributionMetadata( { row }, std::move( row_moment ), boundaries ),
                                std::move( matrix ),
                                relative );
    }
    else {

      Log::info( "Reading data for MT{} cross term for P{} and P{}", mt, row_moment.front(), col_moment.front() );
      covariances.emplace_back( frame,
                                AngularDistributionMetadata( { row }, std::move( row_moment ), boundaries ),
                                AngularDistributionMetadata( { row }, std::move( col_moment ), boundaries ),
                                std::move( matrix ),
                                relative );
    }

    return covariances;
  }

} // covariance namespace
} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
