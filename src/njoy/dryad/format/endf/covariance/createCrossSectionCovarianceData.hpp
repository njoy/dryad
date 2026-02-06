#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATECROSSSECTIONCOVARIANCEDATA
#define NJOY_DRYAD_FORMAT_ENDF_CREATECROSSSECTIONCOVARIANCEDATA

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/CrossSectionCovarianceData.hpp"
#include "njoy/dryad/format/endf/covariance/createCrossSectionCovarianceMatrix.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a CrossSectionCovarianceData from an unparsed ENDF material
   *
   *  @param[in] reaction     the reaction identifier
   *  @param[in] material     the unparsed ENDF material
   *  @param[in] mt           the MT number to process
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   */
  inline std::optional< CrossSectionCovarianceData >
  createCrossSectionCovarianceData( const ENDFtk::tree::Material& material ) {

    std::optional< CrossSectionCovarianceData > covariances = std::nullopt;

    if ( material.hasFile( 33 ) ) {

      Log::info( "Reading cross section covariance data" );

      auto adjust_scatter_level = [&projectile, &target] ( int mt ) {

        if ( target.e() > 0 && projectile != id::ParticleID::photon() ) {

          int ground = id::ReactionID( projectile, target.groundState(), 2 ).reactionType().mt().value();
          int elastic = id::ReactionID( projectile, target, 2 ).reactionType().mt().value();
          if ( mt > ground && mt <= elastic ) {

            return mt - 1;
          }
        }
        return mt;
      };

      std::vector< covariance::CrossSectionCovarianceMatrix > matrices;
      matrices.reserve( material.file( 33 ).sectionNumbers().size() );
      for ( auto mt : material.file( 33 ).sectionNumbers() ) {

        id::ReactionID row( projectile, target, adjust_scatter_level( mt ) );

        auto section = material.section( 33, mt ).parse< 33 >();
        for ( const auto& block : section.reactions() ) {

          id::ReactionID column( projectile, target, adjust_scatter_level( block.MT1() ) );
          if ( row == column ) {

            matrices.emplace_back( covariance::createCrossSectionCovarianceMatrix( row, block ) );
          }
          else {

            matrices.emplace_back( covariance::createCrossSectionCovarianceMatrix( row, column, block ) );
          }
        }
      }

      covariances = CrossSectionCovarianceData( std::move( matrices ) );
    }

    return covariances;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
