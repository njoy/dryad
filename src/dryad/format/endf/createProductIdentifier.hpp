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
   *
   *  @param[in] zap   the product identifier
   *  @param[in] lip   the isomeric state or multiple emission value
   */
  id::ParticleID createProductIdentifier( int zap, int lip ) {

    switch ( zap ) {

      case    0 : return lip == 0 ? "g"   : "g_" + std::to_string( lip );
      case    1 : return lip == 0 ? "n"   : "n_" + std::to_string( lip );
      case   11 : return lip == 0 ? "e-"  : "e-_" + std::to_string( lip );
      case 1001 : return lip == 0 ? "p"   : "p_" + std::to_string( lip );
      case 1002 : return lip == 0 ? "d"   : "d_" + std::to_string( lip );
      case 1003 : return lip == 0 ? "t"   : "t_" + std::to_string( lip );
      case 2003 : return lip == 0 ? "he3" : "he3_" + std::to_string( lip );
      case 2004 : return lip == 0 ? "a"   : "a_" + std::to_string( lip );
      default : return std::to_string( zap ) + "_e" + std::to_string( lip );
    };
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
