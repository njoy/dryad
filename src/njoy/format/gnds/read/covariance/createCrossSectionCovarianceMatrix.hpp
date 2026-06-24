#ifndef NJOY_FORMAT_GNDS_READ_COVARIANCE_CREATECROSSSECTIONCOVARIANCEMATRIX
#define NJOY_FORMAT_GNDS_READ_COVARIANCE_CREATECROSSSECTIONCOVARIANCEMATRIX

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceMatrix.hpp"
#include "njoy/format/adjustScatterLevel.hpp"
#include "njoy/format/gnds/read/readCovarianceMatrix.hpp"
#include "njoy/format/gnds/read/covariance/createVarianceScaling.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {
namespace covariance {

  /**
   *  @brief Create a cross section covariance block from a GNDS covariance section
   *
   *  @param[in] projectile    the projectile identifier
   *  @param[in] target        the target identifier
   *  @param[in] covariances   the GNDS covariance section node giving a
   *                           cross section covariance matrix
   */
  inline std::vector< dryad::covariance::CrossSectionCovarianceMatrix >
  createCrossSectionCovarianceMatrix(
      const dryad::id::ParticleID& projectile,
      const dryad::id::ParticleID& target,
      const pugi::xml_node& covariance ) {

    bool relative = true;
    dryad::id::ReactionID rowReaction;
    dryad::id::ReactionID columnReaction;
    std::vector< std::vector< double > > rowStructures;
    std::vector< std::vector< double > > columnStructures;
    std::vector< matrix::Matrix< double > > matrices;
    std::optional< dryad::covariance::VarianceScaling > scaling = std::nullopt;

    bool is_cross_term = covariance.attribute( "crossTerm" ).as_bool( false );

    auto row = covariance.child( "rowData" );
    if ( row ) {

      //! @todo use the href instead to get the id? requires opening two files
      std::string reaction = row.attribute( "ENDF_MFMT" ).as_string();
      reaction.erase( reaction.begin(),
                      std::find( reaction.begin(), reaction.end(), ',' ) + 1 );
      auto mt = adjustScatterLevel( projectile, target, std::stoi( reaction ) );
      rowReaction = dryad::id::ReactionID( projectile, target,
                                           dryad::id::ReactionType( projectile, mt ) );
    }
    else {

      Log::error( "Covariance row reaction not found, cannot find the associated reaction" );
      throw std::exception();
    }
    auto column = covariance.child( "columnData" );
    if ( column ) {

      // href that start with $reactions# are cross terms for the target
      if ( strncmp( column.attribute( "href" ).as_string(), "$reactions#",11 ) == 0 ) {

        //! @todo use the href instead to get the id? requires opening two files
        std::string reaction = column.attribute( "ENDF_MFMT" ).as_string();
        reaction.erase( reaction.begin(),
                        std::find( reaction.begin(), reaction.end(), ',' ) + 1 );
        columnReaction = dryad::id::ReactionID( projectile, target,
                                                dryad::id::ReactionType( projectile, std::stoi( reaction ) ) );
      }
      else {

        throw std::runtime_error( "trying to read a cross material term, contact a developer" );
      }
    }

    if ( row && column ) {

      if ( ! is_cross_term ) {

        is_cross_term = true;
        Log::warning( "Covariance data not tagged as a cross term in a covarianceSection node with column data" );
      }
    }
    else if ( ! column && is_cross_term ) {

      is_cross_term = false;
      Log::warning( "Covariance data tagged as a cross term in a covarianceSection node without column data" );
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

      if ( ! is_cross_term ) {

        Log::info( "Reading cross section covariance data for MT{}", rowReaction.mt().value() );
      }
      else {

        Log::info( "Reading cross section covariance cross term for MT{} and MT{}",
                   rowReaction.mt().value(), columnReaction.mt().value() );
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
        if ( is_cross_term ) {

          Log::error( "A cross term cannot have variance scaling" );
          throw std::exception();
        }
      }
    }

    std::vector< dryad::covariance::CrossSectionCovarianceMatrix > covariances;
    for ( std::size_t i = 0; i < rowStructures.size(); i++ ) {

      if ( is_cross_term ) {

        using CrossSectionMetadata = dryad::covariance::CrossSectionMetadata;
        covariances.emplace_back(
                 CrossSectionMetadata( { rowReaction }, std::move( rowStructures[i] ) ),
                 CrossSectionMetadata( { columnReaction }, std::move( columnStructures[i] ) ),
                 std::move( matrices[i] ), relative );
      }
      else {

        using CrossSectionMetadata = dryad::covariance::CrossSectionMetadata;
        covariances.emplace_back(
                 CrossSectionMetadata( { rowReaction }, std::move( rowStructures[i] ) ),
                 std::move( matrices[i] ),
                 relative, scaling );
      }
    }

    return covariances;
  }

} // covariance namespace
} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
