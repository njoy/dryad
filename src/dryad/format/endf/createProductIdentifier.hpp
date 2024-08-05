#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPRODUCTID
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPRODUCTID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the product identifier
   */
  id::ParticleID createProductIdentifier( int zap ) {

    switch ( zap ) {

      case    0 : return "g";
      case    1 : return "n";
      case   11 : return "e-";
      case 1001 : return "p";
      case 1002 : return "d";
      case 1003 : return "t";
      case 2003 : return "he3";
      case 2004 : return "a";
      default : return std::to_string( zap );
    };
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
