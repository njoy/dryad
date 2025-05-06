// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/id/ParticleID.hpp"

// namespace aliases
namespace python = pybind11;

namespace id {

void wrapParticleID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ParticleID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ParticleID",
    "The particle identifier"
  );

  // wrap the component
  component
  .def(

    python::init< int, int >(),
    python::arg( "za" ), python::arg( "number" ) = 0,
    "Initialise the particle identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    za       the particle za number\n"
    "    number   the particle level number or subshell number (default is zero)"
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
  .def_property_readonly(

    "number",
    &Component::number,
    "The particle number"
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

    "subshell",
    &Component::subshell,
    "The particle's subshell"
  )
  .def(

    "__hash__",
    [] ( const Component& self ) { return self.number(); },
    "Hash function"
  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );

  // add standard print definitions
  addStandardPrintDefinitions< Component >( component );
}

} // namespace id