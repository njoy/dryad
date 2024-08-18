#ifndef NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEREACTIONS
#define NJOY_DRYAD_FORMAT_ACE_PHOTOATOMIC_CREATEREACTIONS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/Reaction.hpp"
#include "ACEtk/PhotoatomicTable.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {
namespace photoatomic {

  /**
   *  @brief Create the reactions for photoatomic data
   */
  std::vector< Reaction > createReactions( const ACEtk::PhotoatomicTable& table ) {

    std::vector< Reaction > reactions;

    return reactions;
  }

} // electroatomic namespace
} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
