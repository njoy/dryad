// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/id/LevelID.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace id {

void wrapLevelID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::LevelID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LevelID",
    "The excited state or level identifier\n\n"
    "Comparison operators are provided using the logical order given by the\n"
    "level number.\n\n"
    "Parameters\n"
    "----------\n"
    "    number : int\n"
    "        the level number\n"
    "    string : str\n"
    "        the level symbol"
  );

  // wrap the component
  component
  .def(

    python::init< int >(),
    python::arg( "number" ),
    "Initialise the level identifier using a level number"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the level identifier using a level symbol"
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
