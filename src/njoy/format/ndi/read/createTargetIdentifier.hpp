#ifndef NJOY_FORMAT_NDI_READ_CREATETARGETIDENTIFIER
#define NJOY_FORMAT_NDI_READ_CREATETARGETIDENTIFIER

// system includes
#include <algorithm>

// other includes
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace ndi {
namespace read {

  /**
   *  @brief Create a target identifier from a zaid
   *
   *  @param[in] zaid   the target zaid name
   */
  inline dryad::id::ParticleID createTargetIdentifier( const std::string& zaid ) {

    //! @todo we're currently storing metastable state as an excited state

    int number = std::stoi( std::string( zaid.begin(), std::find( zaid.begin(), zaid.end(), '.' ) ) );
    dryad::id::ElementID element( std::round( number%100000 / 1000 ) );
    int mass = number%1000;
    dryad::id::LevelID level( std::round( number / 1000000 ) );
    return dryad::id::ParticleID( std::move( element ), mass, level );
  }

} // read namespace
} // ndi namespace
} // format namespace
} // njoy namespace

#endif
