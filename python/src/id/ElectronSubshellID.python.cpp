// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/id/ElectronSubshellID.hpp"

// namespace aliases
namespace python = pybind11;

namespace id {

void wrapElectronSubshellID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ElectronSubshellID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ElectronSubshellID",
    "The electron subshell identifier"
  );

  // wrap the component
  component
  .def(

    python::init< int >(),
    python::arg( "number" ),
    "Initialise the subshell identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    number   the subshell number"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the subshell identifier\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    string   the subshell symbol, name or alternative name"
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

  // add standard print definitions
  addStandardPrintDefinitions< Component >( component );
}

} // namespace id