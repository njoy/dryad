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
    "Jupyter notebook dryad-identifiers.ipynb under python/examples."
  );

  // wrap the component
  component
  .def(

    python::init< ElementID, int, LevelID >(),
    python::arg( "element" ), python::arg( "mass" ), python::arg( "level" ),
    "Initialise the particle identifier\n\n"
    "Arguments:\n"
    "    self      the identifier\n"
    "    element   the particle element\n"
    "    mass      the particle mass number\n"
    "    level     the particle level"
  )
  .def(

    python::init< ElementID, ElectronSubshellID >(),
    python::arg( "element" ), python::arg( "vacancy" ),
    "Initialise the particle identifier\n\n"
    "Arguments:\n"
    "    self      the identifier\n"
    "    element   the particle element\n"
    "    vacancy   the subshell with a vacancy"
  )
  .def(

    python::init< ElementID, std::vector< ElectronSubshellID > >(),
    python::arg( "element" ), python::arg( "vacancies" ),
    "Initialise the particle identifier\n\n"
    "Arguments:\n"
    "    self        the identifier\n"
    "    element     the particle element\n"
    "    vacancies   the subshells with a vacancy"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the particle identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    string   the particle symbol, name or alternative"
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
    "Arguments:\n"
    "    za      the za number of the nuclide\n"
    "    level   the level number of the nuclide"
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

    "vacancies",
    &Component::vacancies,
    "The particle's subshell vacancies"
  )
  .def(

    "__hash__",
    [] ( const Component& self ) { return std::hash< Component >{}( self ); },
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
