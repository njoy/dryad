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
    python::arg( "za" ), python::arg( "level" ) = 0,
    "Initialise the particle identifier\n\n"
    "Arguments:\n"
    "    self    the identifier\n"
    "    za      the particle za number\n"
    "    level   the particle level number (default is zero)"
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