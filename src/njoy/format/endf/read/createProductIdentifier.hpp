#ifndef NJOY_FORMAT_ENDF_READ_CREATEPRODUCTID
#define NJOY_FORMAT_ENDF_READ_CREATEPRODUCTID

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/format/endf/read/createTargetIdentifier.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {

  /**
   *  @brief Create the product identifier
   *
   *  @param[in] zap        the product identifier
   *  @param[in] lip        the isomeric state or multiple emission value
   *  @param[in] multiple   flag to indicate whether or not there is multiple
   *                        emission of the product
   */
  inline dryad::id::ParticleID createProductIdentifier( int zap, int lip ) {

    switch ( zap ) {

      case  0 : return dryad::id::ParticleID::photon();
      case  1 : return dryad::id::ParticleID::neutron();
      case 11 : return dryad::id::ParticleID::electron();
      default : return createTargetIdentifier( zap, lip );
    };
  }

} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
