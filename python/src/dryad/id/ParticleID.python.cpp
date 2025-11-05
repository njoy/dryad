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
    "The particle identifier\n\n"
    "The ParticleID can be used to identify the following particle types (the\n"
    "numbers between parentheses are the internal logic numbers assigned to them):\n"
    "  - fundamental particles: g (0), e- (1), e+ (2), n (10), p (1001), d (1002),\n"
    "    t (1003), h (2003), a (2004)\n"
    "  - elements (z * 1000000)\n"
    "  - nuclides (z * 1000000 + a * 1000 + l, with l = 0 .. 150 with 150 being\n"
    "    defined as the continuum )\n"
    "  - ions (z * 1000000 + s, with s = K(534) .. Q11(580) - basically the ENDF\n"
    "    mt numbers for the subshell ionisation)\n\n"
    "Comparison operators are provided using the logical order given by the\n"
    "element number. A hash function and override for std::hash is also\n"
    "provided.\n\n"
    "For more information on how to create instances of ParticleID, see the\n"
    "Jupyter notebook dryad-identifiers.ipynb under python/examples."
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
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
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