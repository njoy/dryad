#ifndef NJOY_FORMAT_ENDF_WRITE_CREATESUBLIBRARYTYPE
#define NJOY_FORMAT_ENDF_WRITE_CREATESUBLIBRARYTYPE

// system includes

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/InteractionType.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace write {

  /**
   *  @brief Create the ENDF sublibrary type based on the interaction
   *         type and projectile type
   *
   *  @param[in] projectile    the projectile identifier
   *  @param[in] interaction   the interaction type
   */
  inline int createSublibraryType( const dryad::id::ParticleID& projectile,
                                   const dryad::InteractionType& interaction ) {

    if ( interaction == dryad::InteractionType::Atomic ) {

      if ( ( projectile != dryad::id::ParticleID::photon() ) &&
           ( projectile != dryad::id::ParticleID::electron() ) ) {

        Log::error( "The ENDF format only handles atomic interactions for photons "
                    "and electrons. Found atomic data for {}", projectile.symbol() );
        throw std::exception();
      }
      return projectile == dryad::id::ParticleID::photon() ? 3 : 113;
    }
    else {

      return projectile.za() * 10;
    }
  }

} // write namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
