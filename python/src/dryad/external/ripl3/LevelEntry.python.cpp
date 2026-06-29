// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/external/ripl3/LevelEntry.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace external {
namespace ripl3 {

void wrapLevelEntry( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::external::ripl3::LevelEntry;
  using ParticleID = njoy::dryad::id::ParticleID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LevelEntry",
    "RIPL-3 level entry information\n\n"
    "The LevelEntry class contains level information for a particle from the\n"
    "RIPL-3 database:\n"
    "  - a particle identifier\n"
    "  - an optional level energy value\n"
    "  - an optional spin value\n"
    "  - an optional parity (which is either +1 or -1)\n"
    "  - an optional half life value\n\n"
    "The data is stored in the following units:\n"
    "  - energy values are in eV\n"
    "  - half life values are in seconds\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ParticleID\n"
    "        the particle identifier\n"
    "    energy : float, default None\n"
    "        the level energy (default: None)\n"
    "    spin : float, default None\n"
    "        the level spin (default: None)\n"
    "    parity : int, default None\n"
    "        the level spin parity (default: None)\n"
    "    half_life : float, default None\n"
    "        the level half life (default: None)"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID,
                  std::optional< double >,
                  std::optional< double >,
                  std::optional< short >,
                  std::optional< double > >(),
    python::arg( "id" ),
    python::arg( "energy" ) = std::nullopt,
    python::arg( "spin" ) = std::nullopt,
    python::arg( "parity" ) = std::nullopt,
    python::arg( "half_life" ) = std::nullopt,
    "Initialise the level entry information"
  )
  .def_property(

    "identifier",
    python::overload_cast<>( &Component::identifier, python::const_ ),
    python::overload_cast< ParticleID >( &Component::identifier ),
    "The particle identifier"
  )
  .def_property(

    "energy",
    python::overload_cast<>( &Component::energy, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::energy ),
    "The level energy value"
  )
  .def_property(

    "spin",
    python::overload_cast<>( &Component::spin, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::spin ),
    "The spin of the level"
  )
  .def_property(

    "parity",
    python::overload_cast<>( &Component::parity, python::const_ ),
    python::overload_cast< std::optional< short > >( &Component::parity ),
    "The level spin parity"
  )
  .def_property(

    "half_life",
    python::overload_cast<>( &Component::halfLife, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::halfLife ),
    "The level half life"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // ripl3 namespace
} // external namespace
} // dryad namespace
