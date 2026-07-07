// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/ParticleDatabase.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapParticleDatabase( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ParticleDatabase;
  using Particle = njoy::dryad::Particle;
  using ParticleID = njoy::dryad::id::ParticleID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ParticleDatabase",
    "The particle database\n\n"
    "Parameters\n"
    "----------\n"
    "    particles : list of njoy.dryad.Particle\n"
    "        the particle information\n"
    "    identifiers : list of njoy.dryad.id.ParticleID\n"
    "        the particle identifiers"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< Particle > >(),
    python::arg( "particles" ),
    "Initialise the particle database"
  )
  .def(

    python::init< std::vector< ParticleID > >(),
    python::arg( "identifiers" ),
    "Initialise the particle database"
  )
  .def_property_readonly(

    "number_particles",
    &Component::numberParticles,
    "The number of particles"
  )
  .def_property(

    "particles",
    python::overload_cast<>( &Component::particles, python::const_ ),
    python::overload_cast< std::vector< Particle > >( &Component::particles ),
    "The available particles"
  )
  .def(

    "has_particle",
    &Component::hasParticle,
    python::arg( "id" ),
    "Return whether or not a particle is present\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "        the particle identifier"
  )
  .def(

    "particle",
    python::overload_cast< const ParticleID& >( &Component::particle, python::const_ ),
    python::arg( "id" ),
    "Return the requested particle\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "        the particle identifier",
    python::return_value_policy::reference_internal
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
