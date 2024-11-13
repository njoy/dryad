#ifndef NJOY_DRYAD_FORMAT_GNDS_CREATEINTERACTIONTYPE
#define NJOY_DRYAD_FORMAT_GNDS_CREATEINTERACTIONTYPE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/InteractionType.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Create the interpolation type from a GNDS string value
   */
  static InteractionType createInteractionType( const std::string& type ) {

    if ( type == "nuclear" ) {

      return InteractionType::Nuclear;
    }
    else if ( type == "atomic" ) {

      return InteractionType::Atomic;
    }
    else {

      Log::error( "GNDS interaction type \'{}\' is not recognised", type );
      throw std::exception();
    }
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
