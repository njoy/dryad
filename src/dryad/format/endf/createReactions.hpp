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
   */
  std::vector< Reaction >
  createReactions( const ENDFtk::tree::Material& material ) {

    std::vector< Reaction > reactions;
    reactions.reserve( material.file( 3 ).sectionNumbers().size() );
    for ( auto mt : material.file( 3 ).sectionNumbers() ) {

      reactions.emplace_back( createReaction( material, mt ) );
    }
    return reactions;
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
