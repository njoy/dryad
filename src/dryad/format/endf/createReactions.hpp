#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_ENDF_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/endf/createReaction.hpp"
#include "dryad/Reaction.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create every Reaction from an unparsed ENDF material
   *
   *  This function will produce reaction instances for each MT number defined in
   *  MF3 or MF23 (if MF3 is not present in the file). If neither MF3 or MF23 are
   *  present, the function will return an empty vector.
   */
  std::vector< Reaction >
  createReactions( const ParticleID& projectile, const ParticleID& target,
                   const ENDFtk::tree::Material& material ) {

    std::vector< Reaction > reactions;
    if ( material.hasFile( 3 ) || material.hasFile( 23 ) ) {

      constexpr std::array< int, 8 > derived = { 203, 204, 205, 206, 207, 251, 252, 253 };

      int source = material.hasFile( 3 ) ? 3 : 23;
      reactions.reserve( material.file( source ).sectionNumbers().size() );
      for ( auto mt : material.file( source ).sectionNumbers() ) {

        if ( ! std::binary_search( derived.begin(), derived.end(), mt ) ) {

          Log::info( "Reading data for MT{}", mt );
          reactions.emplace_back( createReaction( projectile, target, material, mt ) );
        }
        else {

          Log::warning( "Skipping data for derived MT{}", mt );
        }
      }
    }
    return reactions;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
