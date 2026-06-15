#ifndef NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECROSSSECTIONCOVARIANCEMATRIX
#define NJOY_FORMAT_GENDF_READ_COVARIANCE_CREATECROSSSECTIONCOVARIANCEMATRIX

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/covariance/CrossSectionMetadata.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/format/createVector.hpp"
#include "njoy/format/adjustScatterLevel.hpp"
#include "ENDFtk/gsection/33g.hpp"

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
   *  @param[in] relative     the flag to indicate whether or not the covariance data is relative
   *  @param[in] material     the unparsed ENDF material
   */
  inline std::vector< dryad::covariance::CrossSectionCovarianceMatrix >
  createCrossSectionCovarianceMatrix(
      dryad::id::ParticleID projectile,
      dryad::id::ParticleID target,
      std::vector< double > boundaries, bool relative,
      ENDFtk::section::GType< 33 >& section ) {

    std::vector< dryad::covariance::CrossSectionCovarianceMatrix > covariances;

    int mt = section.sectionNumber();
    int lumped = section.lumpedReactionNumber();
    if ( lumped != 0 ) {

      Log::info( "No covariance data for MT{}, included in lumped MT{} covariances",
                 mt, lumped );
    }

    dryad::id::ReactionID row( projectile, target, adjustScatterLevel( projectile, target, mt ) );
    for ( int column_mt : section.secondaryReactions() ) {

      decltype(auto) data = section.covariance( column_mt );

      unsigned int size = boundaries.size() - 1;
      matrix::Matrix< double > matrix( size, size );
      for ( unsigned int i = 0; i < size; ++i ) {

        for ( unsigned int j = 0; j < size; ++j ) {

          matrix( i, j ) = data[i][j];
        }
      }

      using CrossSectionMetadata = dryad::covariance::CrossSectionMetadata;
      if ( mt == column_mt ) {

        Log::info( "Reading data for MT{}", mt );
        covariances.emplace_back( CrossSectionMetadata( { row }, boundaries ),
                                  std::move( matrix ), relative );
      }
      else {

        Log::info( "Reading cross term for MT{} and MT{}", mt, column_mt );
        dryad::id::ReactionID column( projectile, target, adjustScatterLevel( projectile, target, column_mt ) );
        covariances.emplace_back( CrossSectionMetadata( { row }, boundaries ),
                                  CrossSectionMetadata( { column }, boundaries ),
                                  std::move( matrix ), relative );
      }
    }

    return covariances;
  }

} // covariance namespace
} // read namespace
} // gendf namespace
} // format namespace
} // njoy namespace

#endif
