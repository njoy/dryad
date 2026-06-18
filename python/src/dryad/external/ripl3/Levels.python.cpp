// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/external/ripl3/Levels.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace external {
namespace ripl3 {

void wrapLevels( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::external::ripl3::Levels;
  using LevelEntry = njoy::dryad::external::ripl3::LevelEntry;
  using ParticleID = njoy::dryad::id::ParticleID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Levels",
    "RIPL-3 level data\n\n"
    "The Levels class allows a user to interact with the  nuclear levels part of the RIPL-3\n"
    "database."
  );

  // wrap the component
  component
  .def_static(

    "size",
    &Component::size,
    "Return the current size of the RIPL-3 levels data"
  )
  .def_static(

    "has_particle",
    &Component::hasParticle,
    python::arg( "id" ),
    "Verify whether or not a given particle is present\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "         the particle identifier"
  )
  .def_static(

    "level",
    &Component::level,
    python::arg( "id" ),
    "Retrieve a level entry for a given particle\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "         the particle identifier"
  );
}

} // ripl3 namespace
} // external namespace
} // dryad namespace
