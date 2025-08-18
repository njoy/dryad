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
  id::ParticleID createProductIdentifier( int zap, int lip ) {

    switch ( zap ) {

      case    0 : return id::ParticleID::photon();
      case    1 : return id::ParticleID::neutron();
      case   11 : return id::ParticleID::electron();
      case 1001 : return id::ParticleID::proton();
      case 1002 : return id::ParticleID::deuteron();
      case 1003 : return id::ParticleID::triton();
      case 2003 : return id::ParticleID::helion();
      case 2004 : return id::ParticleID::alpha();
      default : return createTargetIdentifier( zap, lip );
    };
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
