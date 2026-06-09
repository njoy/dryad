#ifndef NJOY_DRYAD_FORMAT_PARTICLEMASS
#define NJOY_DRYAD_FORMAT_PARTICLEMASS

// system includes

// other includes
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/constants.hpp"

namespace njoy {
namespace dryad {
namespace format {

  /**
   *  @brief Retrieve the mass of a particle in amu
   *
   *  @param[in] id   the particle identifier
   */
  inline double particleMass( const id::ParticleID& id ) {

    if      ( id == id::ParticleID::neutron() )  { return constants::neutron_mass; }
    else if ( id == id::ParticleID::proton() )   { return constants::proton_mass; }
    else if ( id == id::ParticleID::deuteron() ) { return constants::deuteron_mass; }
    else if ( id == id::ParticleID::triton() )   { return constants::deuteron_mass; }
    else if ( id == id::ParticleID::helion() )   { return constants::deuteron_mass; }
    else if ( id == id::ParticleID::alpha() )    { return constants::alpha_mass; }
    else {


    }
  };

} // format namespace
} // dryad namespace
} // njoy namespace

#endif
