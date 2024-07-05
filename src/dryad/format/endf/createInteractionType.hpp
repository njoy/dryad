#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEINTERACTIONTYPE
#define NJOY_DRYAD_FORMAT_ENDF_CREATEINTERACTIONTYPE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/InteractionType.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the interaction type based of the sublibrary value
   */
  InteractionType createInteractionType( int sublibrary ) {

    switch ( sublibrary ) {

      case     0 : return InteractionType::Nuclear;
      case     3 : return InteractionType::Atomic;
      case    10 : return InteractionType::Nuclear;
      case   113 : return InteractionType::Atomic;
      case 10010 : return InteractionType::Nuclear;
      case 10020 : return InteractionType::Nuclear;
      case 10030 : return InteractionType::Nuclear;
      case 20030 : return InteractionType::Nuclear;
      case 20040 : return InteractionType::Nuclear;
      default : {

        Log::error( "ENDF sublibrary {} does not define projectile-target data",
                    sublibrary );
        throw std::exception();
      }
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
