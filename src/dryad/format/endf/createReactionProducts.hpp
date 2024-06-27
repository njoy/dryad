#ifndef NJOY_DRYAD_FORMAT_ENDF_REACTIONPRODUCTS
#define NJOY_DRYAD_FORMAT_ENDF_REACTIONPRODUCTS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ReactionProduct.hpp"
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create a Reaction from an unparsed ENDF material
   */
  std::vector< ReactionProduct >
  createReactionProducts( const id::ParticleID& projectile, const id::ParticleID& target,
                          const ENDFtk::tree::Material& material, int mt ) {

    return {};
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
