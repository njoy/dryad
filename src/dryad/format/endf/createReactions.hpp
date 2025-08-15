#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/ReactionInformation.hpp"
#include "dryad/format/endf/createReaction.hpp"
#include "dryad/Reaction.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Calculate a summation cross section
   */
  TabulatedCrossSection
  calculateSummationCrossSection( const std::vector< id::ReactionID >& partials,
                                  const std::vector< Reaction >& reactions ) {

    auto find_cross_section = [] ( const auto& id, const auto& reactions ) {

      auto iter = std::find_if( reactions.begin(), reactions.end(),
                                [ id ] ( auto&& reaction ) { return reaction.identifier() == id; } );
      if ( iter == reactions.end() ) {

        Log::error( "Missing partial reaction {}", id.symbol() );
        throw std::exception();
      }

      return iter->crossSection().linearise();
    };

    TabulatedCrossSection sum = find_cross_section( partials.front(), reactions );
    for ( unsigned int i = 1; i < partials.size(); ++i ) {

      sum += find_cross_section( partials[i], reactions );
    }

    return sum;
  }

  /**
   *  @brief Create every Reaction from an unparsed ENDF material
   *
   *  This function will produce reaction instances for each MT number defined in
   *  MF3 or MF23 (if MF3 is not present in the file). If neither MF3 or MF23 are
   *  present, the function will return an empty vector.
   */
  std::vector< Reaction >
  createReactions( const id::ParticleID& projectile, const id::ParticleID& target,
                   const ENDFtk::tree::Material& material,
                   bool normalise ) {

    std::vector< Reaction > reactions;
    if ( material.hasFile( 3 ) || material.hasFile( 23 ) ) {

      int source = material.hasFile( 3 ) ? 3 : 23;

      // loop over the available reactions and create the reaction objects
      reactions.reserve( material.file( source ).sectionNumbers().size() );
      for ( auto mt : material.file( source ).sectionNumbers() ) {

        if ( ! endf::ReactionInformation::isDerived( mt ) ) {

          Log::info( "Reading data for MT{}", mt );
          reactions.emplace_back( createReaction( projectile, target, material, mt, normalise ) );
        }
        else {

          Log::warning( "Skipping data for derived MT{}", mt );
        }
      }

      // if the data has cross section covariance data, look for lumped covariances
      if ( material.hasFile( 33 ) ) {

        for ( auto mt : material.file( 33 ).sectionNumbers() ) {

          if ( endf::ReactionInformation::isLumpedCovariance( mt ) ) {

            Log::info( "Reading data for MT{}", mt );

            // metadata and miscellaneous information
            id::ReactionID id( projectile, target, id::ReactionType( mt ) );

            // partials
            std::vector< id::ReactionType > endf_partials = ReactionInformation::partials( projectile, material, 33, mt );
            std::vector< id::ReactionID > partials( endf_partials.size() );
            std::transform( endf_partials.begin(), endf_partials.end(), partials.begin(),
                            [&projectile, &target]
                               ( auto&& type )
                               { return id::ReactionID( projectile, target, type ); } );

            // cross section
            TabulatedCrossSection xs = calculateSummationCrossSection( partials, reactions );

            reactions.emplace_back( std::move( id ), std::move( partials ), std::move( xs ) );
          }
        }
      }

      // calculate deficit reaction for elastic scattering in electro-atomic data
      if ( material.hasSection( 23, 526 ) && ReactionInformation::isSummation( material, 526 ) ) {

        auto total = std::find_if( reactions.begin(), reactions.end(),
                                   [] ( const auto& reaction )
                                      { return reaction.identifier().reactionType()
                                               == id::ReactionType( "total-scattering" ); } );
        auto partial = std::find_if( reactions.begin(), reactions.end(),
                                     [] ( const auto& reaction )
                                        { return reaction.identifier().reactionType()
                                                 == id::ReactionType( "large-angle-scattering" ); } );
        TabulatedCrossSection deficit = total->crossSection().linearise();
        deficit -= partial->crossSection().linearise();

        reactions.emplace_back( Reaction( id::ReactionID( projectile, target, id::ReactionType( "deficit-scattering" ) ),
                                          deficit, {}, std::nullopt, 0. ) );
      }
    }
    return reactions;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
