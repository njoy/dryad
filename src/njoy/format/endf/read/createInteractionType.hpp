#ifndef NJOY_FORMAT_ENDF_READ_CREATEINTERACTIONTYPE
#define NJOY_FORMAT_ENDF_READ_CREATEINTERACTIONTYPE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InteractionType.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create the interaction type based of the sublibrary value
   */
  inline dryad::InteractionType
  createInteractionType( int sublibrary ) {

    switch ( sublibrary ) {

      case     0 : return dryad::InteractionType::Nuclear;
      case     3 : return dryad::InteractionType::Atomic;
      case    10 : return dryad::InteractionType::Nuclear;
      case   113 : return dryad::InteractionType::Atomic;
      case 10010 : return dryad::InteractionType::Nuclear;
      case 10020 : return dryad::InteractionType::Nuclear;
      case 10030 : return dryad::InteractionType::Nuclear;
      case 20030 : return dryad::InteractionType::Nuclear;
      case 20040 : return dryad::InteractionType::Nuclear;
      default : {

        Log::error( "ENDF sublibrary {} does not define projectile-target data",
                    sublibrary );
        throw std::exception();
      }
    }
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
