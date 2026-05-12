#ifndef NJOY_DRYAD_FORMAT_COLLECTPARTICLEIDENTIFIERS
#define NJOY_DRYAD_FORMAT_COLLECTPARTICLEIDENTIFIERS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/Reaction.hpp"

namespace njoy {
namespace dryad {
namespace format {

  /**
   *  @brief Collect all identifiers used in a set of reactions
   *
   *  @param[in] reactions   the reactions
   */
  inline std::vector< id::ParticleID >
  collectParticleIdentifiers( const std::vector< Reaction >& reactions ) {

    std::vector< id::ParticleID > identifiers;

    for ( const auto& reaction : reactions ) {

      identifiers.emplace_back( reaction.identifier().projectile() );
      identifiers.emplace_back( reaction.identifier().target() );
      if ( reaction.identifier().particles().has_value() ) {

        identifiers.emplace_back( reaction.identifier().residual().value() );
        if ( reaction.identifier().particles()->size() > 0 ) {

          for ( const auto& [particle, multiplicity] : reaction.identifier().particles().value() ) {

            identifiers.emplace_back( particle );
          }
        }
        else {

          identifiers.emplace_back( id::ParticleID::photon() );
        }

        for ( const auto& product : reaction.products() ) {

          identifiers.emplace_back( product.productIdentifier() );
        }
      }
    }

    std::sort( identifiers.begin(), identifiers.end() );
    identifiers.erase( std::unique( identifiers.begin(), identifiers.end() ),
                       identifiers.end() );

    return identifiers;
  };

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
