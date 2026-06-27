#ifndef NJOY_FORMAT_ENDF_READ_CREATEREACTIONS
#define NJOY_FORMAT_ENDF_READ_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/format/endf/ReactionInformation.hpp"
#include "njoy/format/endf/read/createReaction.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Calculate a summation cross section
   *
   *  @param[in] partials    the identifiers for the partials that compose the summation
   *  @param[in] reactions   all reactions found
   */
  inline dryad::TabulatedCrossSection
  calculateSummationCrossSection( const std::vector< dryad::id::ReactionID >& partials,
                                  const std::vector< dryad::Reaction >& reactions ) {

    auto find_cross_section = [] ( const auto& id, const auto& reactions ) {

      auto iter = std::find_if( reactions.begin(), reactions.end(),
                                [ id ] ( auto&& reaction ) { return reaction.identifier() == id; } );
      if ( iter == reactions.end() ) {

        Log::error( "Missing partial reaction {}", id.symbol() );
        throw std::exception();
      }

      return iter->crossSection().linearise();
    };

    dryad::TabulatedCrossSection sum = find_cross_section( partials.front(), reactions );
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
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] material     the unparsed ENDF material
   *  @param[in] normalise    the flag to indicate whether or not distributions
   *                          need to be normalised
   *  @param[in] masses       the atomic mass values read from the ENDF file
   */
  inline std::vector< dryad::Reaction >
  createReactions( const dryad::id::ParticleID& projectile,
                   const dryad::id::ParticleID& target,
                   const ENDFtk::tree::Material& material,
                   bool normalise,
                   std::map< dryad::id::ParticleID, double >& masses ) {

    std::vector< dryad::Reaction > reactions;
    if ( material.hasFile( 3 ) || material.hasFile( 23 ) ) {

      // where the cross section data is coming from
      int source = material.hasFile( 3 ) ? 3 : 23;

      // loop over the available reactions and create the reaction objects
      reactions.reserve( material.file( source ).sectionNumbers().size() );
      for ( auto mt : material.file( source ).sectionNumbers() ) {

        if ( ! endf::ReactionInformation::isDerived( mt ) ) {

          reactions.emplace_back( createReaction( projectile, target, material, mt, normalise, masses ) );
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
            dryad::id::ReactionID id( projectile, target, mt );

            // partials
            std::vector< dryad::id::ReactionID > partials =
            ReactionInformation::partials( projectile, target, material, 33, mt );

            // cross section
            dryad::TabulatedCrossSection xs = calculateSummationCrossSection( partials, reactions );

            reactions.emplace_back( std::move( id ), std::move( partials ), std::move( xs ) );
          }
        }
      }

      // sort by MT
      std::sort( reactions.begin(), reactions.end(),
                 [] ( auto&& left, auto&&right )
                    { return left.identifier().reactionType().mt()
                             < right.identifier().reactionType().mt(); } );

      // calculate deficit reaction for elastic scattering in electro-atomic data
      if ( material.hasSection( 23, 526 ) && ReactionInformation::isSummation( material, 526 ) ) {

        auto total = std::find_if( reactions.begin(), reactions.end(),
                                   [] ( const auto& reaction )
                                      { return reaction.identifier().reactionType()
                                               == dryad::id::ReactionType( "total-scattering" ); } );
        auto partial = std::find_if( reactions.begin(), reactions.end(),
                                     [] ( const auto& reaction )
                                        { return reaction.identifier().reactionType()
                                                 == dryad::id::ReactionType( "large-angle-scattering" ); } );
        dryad::TabulatedCrossSection deficit = total->crossSection().linearise();
        deficit -= partial->crossSection().linearise();

        reactions.emplace_back( dryad::Reaction( dryad::id::ReactionID( projectile, target, "deficit-scattering" ),
                                                 deficit, {}, std::nullopt, 0. ) );
      }

      reactions.shrink_to_fit();
    }
    return reactions;
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
