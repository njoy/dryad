#ifndef NJOY_DRYAD_FORMAT_ENDF_CREATEENDFSUBLIBRARYTYPE
#define NJOY_DRYAD_FORMAT_ENDF_CREATEENDFSUBLIBRARYTYPE

// system includes

// other includes
#include "tools/Log.hpp"
#include "dryad/InteractionType.hpp"
#include "dryad/id/ParticleID.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {

  /**
   *  @brief Create the ENDF sublibrary type based on the interaction
   *         type and projectile type
   */
  int createEndfSublibraryType( const id::ParticleID& projectile,
                                const InteractionType& interaction ) {

    if ( interaction == InteractionType::Atomic ) {

      if ( ( projectile != id::ParticleID::photon() ) &&
           ( projectile != id::ParticleID::electron() ) ) {

        Log::error( "The ENDF format only handles atomic interactions for photons "
                    "and electrons. Found atomic data for {}", projectile.symbol() );
        throw std::exception();
      }
      return projectile == id::ParticleID::photon() ? 3 : 113;
    }
    else {

      return projectile.za() * 10;
    }
  }

} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
