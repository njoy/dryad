// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/external/ame/Masses.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace external {
namespace ame {

void wrapMasses( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::external::ame::Masses;
  using MassEntry = njoy::dryad::external::ame::MassEntry;
  using ParticleID = njoy::dryad::id::ParticleID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Masses",
    "AME2020 mass data\n\n"
    "The Masses class allows a user to interact with the AME2020 mass data."
  );

  // wrap the component
  component
  .def_static(

    "size",
    &Component::size,
    "Return the current size of the AME2020 mass data"
  )
  .def_static(

    "has_entry",
    &Component::hasEntry,
    python::arg( "id" ),
    "Verify whether or not a given particle is present\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "        the particle identifier"
  )
  .def_static(

    "entry",
    &Component::entry,
    python::arg( "id" ),
    "Retrieve a mass entry for a given particle\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "        the particle identifier"
  );
}

} // ame namespace
} // external namespace
} // dryad namespace
