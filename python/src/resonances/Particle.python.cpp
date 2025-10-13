// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/Particle.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapParticle( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::Particle;
  using ParticleID = njoy::dryad::id::ParticleID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Particle",
    "Particle information for resonance reconstruction\n\n"
    "The Particle class contains specific information for a particle as used\n"
    "during resonance reconstruction. The Particle has an atomic mass, an\n"
    "electrical charge, a spin and a parity (either + or -).\n\n"
    "These variables are used to calculate quantities like the wave number k."
   );

  // wrap the component
  component
  .def(

    python::init< ParticleID, double, double, short >(),
    python::arg( "id" ), python::arg( "mass" ),
    python::arg( "spin" ), python::arg( "parity" ),
    "Initialise the particle information\n\n"
    "Arguments:\n"
    "    self     the particle information\n"
    "    mass     the atomic mass\n"
    "    spin     the channel spin\n"
    "    parity   the parity"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "identifier",
    &Component::identifier,
    "The particle identifier"
  )
  .def_property_readonly(

    "mass",
    &Component::mass,
    "The atomic mass of the particle (in atomic mass units)"
  )
  .def_property_readonly(

    "charge",
    &Component::charge,
    "The electrical charge of the particle (in units of the "
    "elementary charge)"
  )
  .def_property_readonly(

    "spin",
    &Component::spin,
    "The particle spin"
  )
  .def_property_readonly(

    "parity",
    &Component::parity,
    "The parity"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
