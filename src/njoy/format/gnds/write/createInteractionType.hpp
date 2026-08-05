#ifndef NJOY_FORMAT_GNDS_WRITE_CREATEINTERACTIONTYPE
#define NJOY_FORMAT_GNDS_WRITE_CREATEINTERACTIONTYPE

// system includes
#include <string>

// other includes
#include "njoy/dryad/InteractionType.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Create the interpolation string from a dryad interaction enum
   *
   *  @param[in] type   the interaction type
   */
  inline std::string createInteractionType( const dryad::InteractionType& type ) {

    switch ( type ) {

      case dryad::InteractionType::Nuclear : return "nuclear";
      case dryad::InteractionType::Atomic  : return "atomic";
      default : {

        throw std::runtime_error( "You have somehow reached unreachable code, "
                                  "contact an njoy developer to claim your prize - "
                                  "no prizes are guaranteed." );
      }
    }
  }

} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
