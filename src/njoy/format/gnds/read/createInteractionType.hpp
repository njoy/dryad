#ifndef NJOY_FORMAT_GNDS_READ_CREATEINTERACTIONTYPE
#define NJOY_FORMAT_GNDS_READ_CREATEINTERACTIONTYPE

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InteractionType.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create the interpolation type from a GNDS string value
   *
   *  @param[in] type   the interaction type string
   */
  inline dryad::InteractionType createInteractionType( const std::string& type ) {

    if ( type == "nuclear" ) {

      return dryad::InteractionType::Nuclear;
    }
    else if ( type == "atomic" ) {

      return dryad::InteractionType::Atomic;
    }
    else {

      Log::error( "GNDS interaction type \'{}\' is not recognised", type );
      throw std::exception();
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
