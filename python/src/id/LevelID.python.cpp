// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/id/LevelID.hpp"

// namespace aliases
namespace python = pybind11;

namespace id {

void wrapLevelID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::LevelID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LevelID",
    "The level identifier"
  );

  // wrap the component
  component
  .def(

    python::init< int >(),
    python::arg( "number" ),
    "Initialise the level identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    number   the level number"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the level identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    string   the level symbol"
  )
  .def_property_readonly_static(

    "continuum",
    [] ( python::object ) { return Component::continuum; },
    "The continuum level number"
  )
  .def_property_readonly_static(

    "all",
    [] ( python::object ) { return Component::all; },
    "The all level number"
  )
  .def_property_readonly(

    "number",
    &Component::number,
    "The level number"
  )
  .def_property_readonly(

    "symbol",
    &Component::symbol,
    "The level symbol"
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