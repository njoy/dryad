// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/id/ElementID.hpp"

// namespace aliases
namespace python = pybind11;

namespace id {

void wrapElementID( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::id::ElementID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ElementID",
    "The element identifier, with associated element symbol, name and aliases"
  );

  // wrap the component
  component
  .def(

    python::init< int >(),
    python::arg( "number" ),
    "Initialise the element identifier\n\n"
    "Arguments:\n"
    "    self     the reaction\n"
    "    number   the element number"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "number" ),
    "Initialise the reaction\n\n"
    "Arguments:\n"
    "    self     the reaction\n"
    "    symbol   the element symbol or name"
  )
  .def_property_readonly(

    "number",
    &Component::number,
    "The element number"
  )
  .def_property_readonly(

    "symbol",
    &Component::symbol,
    "The element symbol"
  )
  .def_property_readonly(

    "name",
    &Component::name,
    "The element name"
  )
  .def(

    "__hash__",
    [] ( const Component& self ) { return self.number(); },
    "Hash function"
  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );
}

} // namespace id