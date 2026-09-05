#ifndef NJOY_FORMAT_NDI_READ_CREATEPROJECTILEIDENTIFIER
#define NJOY_FORMAT_NDI_READ_CREATEPROJECTILEIDENTIFIER

// system includes
#include <algorithm>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace ndi {
namespace read {

  /**
   *  @brief Create a projectile identifier from a zaid
   *
   *  This function cannot be used for atomic data
   *
   *  @param[in] zaid   the target zaid name
   */
  inline dryad::id::ParticleID createProjectileIdentifier( const std::string& zaid ) {

    if ( zaid.size() > 2 ) {

      std::string extension = zaid.substr( zaid.size() - 2, 2 );
      if ( extension == "nm" || extension == "nd" ) {

        return dryad::id::ParticleID::neutron();
      }
    }

    // if you get to this point, you have a problem
    Log::error( "The zaid \'{}\' does not define incident neutron data", zaid );
    throw std::exception();
  }

} // read namespace
} // ndi namespace
} // format namespace
} // njoy namespace

#endif
