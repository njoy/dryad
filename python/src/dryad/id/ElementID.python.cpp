// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/id/ElementID.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace id {

void wrapElementID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ElementID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ElementID",
    "The element identifier"
  );

  // wrap the component
  component
  .def(

    python::init< int >(),
    python::arg( "number" ),
    "Initialise the element identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    number   the element number"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the element identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    string   the element symbol, name or alternative name"
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
