// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/id/ParticleID.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace id {

void wrapParticleID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ParticleID;
  using ElementID = njoy::dryad::id::ElementID;
  using LevelID = njoy::dryad::id::LevelID;
  using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ParticleID",
    "The particle identifier\n\n"
    "Comparison operators are provided using the logical order given by the\n"
    "element number. A hash function and override for std::hash is also\n"
    "provided.\n\n"
    "For more information on how to create instances of ParticleID, see the\n"
    "Jupyter notebook dryad-identifiers.ipynb under python/examples.\n\n"
    "Parameters\n"
    "----------\n"
    "    element_identifier : njoy.dryad.id.ElementID \n "
    "           the particle element \n"
    "    mass : int \n "
    "           the particle mass number \n"
    "    level_identifier : njoy.dryad.id.LevelID \n "
    "           he particle level \n"
    "    subshell_identifier : njoy.dryad.id.ElectronSubshellID \n"
    "         the particle subshell \n"
    "    string : str \n"
    "         Initialise the particle identifier with the particle symbol, name or alternative \n\n"
  );

  // wrap the component
  component
  .def(

    python::init< ElementID, int, LevelID >(),
    python::arg( "element_identifier" ), python::arg( "mass" ), python::arg( "level_identifier" ),
    "Initialise a nuclear particle identifier with a level number\n\n"
  )
  .def(

    python::init< ElementID, ElectronSubshellID >(),
    python::arg( "element_identifier" ), python::arg( "subshell_identifier" ),
    "Initialise a electron subshell particle identifier\n\n"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the particle identifier with the particle symbol, name or alternative"
  )
  .def_static(

    "size",
    &Component::size,
    "The number of currently registered identifiers"
  )
  .def_static( "photon",   &Component::photon,   "The particle identifier for photons" )
  .def_static( "electron", &Component::electron, "The particle identifier for electrons" )
  .def_static( "positron", &Component::positron, "The particle identifier for positrons" )
  .def_static( "neutron",  &Component::neutron,  "The particle identifier for neutrons" )
  .def_static( "proton",   &Component::proton,   "The particle identifier for protons" )
  .def_static( "deuteron", &Component::deuteron, "The particle identifier for deuterons" )
  .def_static( "triton",   &Component::triton,   "The particle identifier for tritons" )
  .def_static( "helion",   &Component::helion,   "The particle identifier for helions" )
  .def_static( "alpha",    &Component::alpha,    "The particle identifier for alphas" )
  .def_static(

    "nuclide",
    &Component::nuclide,
    python::arg( "za" ), python::arg( "level" ) = 0,
    "Create a particle identifier for a nuclide\n\n"
    "Parameters\n"
    "----------\n"
    "    za : int \n"
    "         the za number of the nuclide \n"
    "    level : int, default 0 \n"
    "         the level number of the nuclide. the default value 0 indicates the ground state\n"
  )
  .def(

    "ground_state",
    &Component::groundState,
    "Return the identifier for the particle's ground state\n\n"
  )
  .def_property_readonly(

    "symbol",
    &Component::symbol,
    "The particle's symbol"
  )
  .def_property_readonly(

    "z",
    &Component::z,
    "The particle's element number"
  )
  .def_property_readonly(

    "a",
    &Component::a,
    "The particle's mass number"
  )
  .def_property_readonly(

    "e",
    &Component::e,
    "The particle's level number"
  )
  .def_property_readonly(

    "za",
    &Component::za,
    "The particle's za number"
  )
  .def_property_readonly(

    "subshell_identifier",
    &Component::subshellIdentifier,
    "The particle's subshell identifier"
  )
  .def(

    "__hash__",
    &Component::hash,
    "Hash function"
  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );

  // add standard print definitions
  addStandardPrintDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // namespace id
} // dryad namespace
