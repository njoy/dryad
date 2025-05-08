#ifndef NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPROJECTILETARGET
#define NJOY_DRYAD_FORMAT_ACE_ELECTROATOMIC_CREATEPROJECTILETARGET

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "dryad/format/ace/createTargetIdentifier.hpp"
#include "dryad/format/ace/electroatomic/createReactions.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace electroatomic {

  /**
   *  @brief Create a ProjectileTarget for electroatomic data
   */
  ProjectileTarget createProjectileTarget( const ACEtk::PhotoatomicTable& table ) {

    return ProjectileTarget( id::ParticleID( "e-" ),
                             createTargetIdentifier( table.ZAID() ),
                             InteractionType::Atomic,
                             createReactions( table ) );
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
