#ifndef NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATECROSSSECTIONCOVARIANCEBLOCK
#define NJOY_DRYAD_FORMAT_GNDS_COVARIANCE_CREATECROSSSECTIONCOVARIANCEBLOCK

// system includes

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/id/ReactionID.hpp"
#include "dryad/covariance/CrossSectionCovarianceBlock.hpp"
#include "dryad/format/gnds/readCovarianceMatrix.hpp"
#include "dryad/format/gnds/covariance/createVarianceScaling.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace covariance {

  /**
   *  @brief Create a cross section covariance block from a GNDS covariance section
   */
  dryad::covariance::CrossSectionCovarianceBlock
  createCrossSectionCovarianceBlock(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const pugi::xml_node& covariance ) {

    bool relative = true;
    dryad::id::ReactionID rowReaction;
    dryad::id::ReactionID columnReaction;
    std::vector< std::vector< double > > rowStructures;
    std::vector< std::vector< double > > columnStructures;
    std::vector< dryad::covariance::Matrix< double > > matrices;
    std::optional< dryad::covariance::VarianceScaling > scaling = std::nullopt;

    auto row = covariance.child( "rowData" );
    if ( row ) {

      //! @todo use the href instead to get the id? requires opening two files
      std::string reaction = row.attribute( "ENDF_MFMT" ).as_string();
      reaction.erase( reaction.begin(),
                      std::find( reaction.begin(), reaction.end(), ',' ) + 1 );
      rowReaction = id::ReactionID( projectile, target, id::ReactionType( projectile, std::stoi( reaction ) ) );
    }
    else {

      Log::error( "Covariance row reaction not found, cannot find the associated reaction" );
      throw std::exception();
    }
    auto column = covariance.child( "columnData" );
    if ( column ) {

      //! @todo use the href instead to get the id? requires opening two files
      std::string reaction = column.attribute( "ENDF_MFMT" ).as_string();
      reaction.erase( reaction.begin(),
                      std::find( reaction.begin(), reaction.end(), ',' ) + 1 );
      columnReaction = id::ReactionID( projectile, target, id::ReactionType( projectile, std::stoi( reaction ) ) );
    }

    bool cross = false;
    if ( row && column ) {

      cross = true;
    }

    auto sum = covariance.child( "sum" );
    if ( sum ) {

      Log::error( "No explicit covariance components are defined" );
      throw std::exception();
    }
    else {

      // search for the node with the matrix data
      auto node = covariance.child( "mixed" );
      if ( !node ) {

        node = covariance;
      }

      // read all matrix data
      for ( pugi::xml_node matrix = node.child( "covarianceMatrix" ); matrix;
            matrix = matrix.next_sibling( "covarianceMatrix" ) ) {

        // read data
        auto data = readCovarianceMatrix( matrix );
        rowStructures.emplace_back( std::move( std::get< 1 >( data ) ) );
        columnStructures.emplace_back( std::move( std::get< 2 >( data ) ) );
        matrices.emplace_back( std::move( std::get< 3 >( data ) ) );

        // convert structures
        convertEnergies( rowStructures.back(), std::get< 4 >( data ) );
        convertEnergies( columnStructures.back(), std::get< 5 >( data ) );
      }

      // check for variance scaling
      auto scale = node.child( "shortRangeSelfScalingVariance" );
      if ( scale ) {

        scaling = createVarianceScaling( scale );
        if ( cross ) {

          Log::error( "A cross term cannot have variance scaling" );
          throw std::exception();
        }
      }
    }

    if ( rowStructures.size() == 1 ) {

      if ( cross ) {

        return dryad::covariance::CrossSectionCovarianceBlock(
                 dryad::covariance::CrossSectionMetadata( projectile, target, rowReaction,
                                                          std::move( rowStructures.front() ) ),
                 dryad::covariance::CrossSectionMetadata( projectile, target, columnReaction,
                                                          std::move( columnStructures.front() ) ),
                 std::move( matrices.front() ), relative );
      }
      else {

        return dryad::covariance::CrossSectionCovarianceBlock(
                 dryad::covariance::CrossSectionMetadata( projectile, target, rowReaction,
                                                          std::move( rowStructures.front() ) ),
                 std::move( matrices.front() ),
                 relative, std::move( scaling ) );
}
    }
    else {

      Log::error( "Not implemented yet, contact a developer" );
      throw std::exception();
    }
  }

} // covariance namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
