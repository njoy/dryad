#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEPRODUCTID
#define NJOY_DRYAD_FORMAT_ENDF_CREATEPRODUCTID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/format/endf/createTargetIdentifier.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the product identifier
   *
   *  @param[in] zap        the product identifier
   *  @param[in] lip        the isomeric state or multiple emission value
   *  @param[in] multiple   flag to indicate whether or not there is multiple
   *                        emission of the product
   */
  id::ParticleID createProductIdentifier( int zap, int lip, bool multiple = false ) {

    switch ( zap ) {

      case    0 : return multiple == false ? "g"   : "g_" + std::to_string( lip );
      case    1 : return multiple == false ? "n"   : "n_" + std::to_string( lip );
      case   11 : return multiple == false ? "e-"  : "e-_" + std::to_string( lip );
      case 1001 : return multiple == false ? "p"   : "p_" + std::to_string( lip );
      case 1002 : return multiple == false ? "d"   : "d_" + std::to_string( lip );
      case 1003 : return multiple == false ? "t"   : "t_" + std::to_string( lip );
      case 2003 : return multiple == false ? "he3" : "he3_" + std::to_string( lip );
      case 2004 : return multiple == false ? "a"   : "a_" + std::to_string( lip );
      default : return createTargetIdentifier( zap, lip );
    };
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
