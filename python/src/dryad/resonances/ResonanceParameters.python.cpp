// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapResonanceParameters( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::ResonanceParameters;
  using CompoundSystem = njoy::dryad::resonances::CompoundSystem;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceParameters"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< CompoundSystem > >(),
    python::arg( "resolved" ),
    "Initialise the resonance parameters\n\n"
    "Arguments:\n"
    "    self       the resonance parameters\n"
    "    resolved   the resolved resonance compound systems"
  )
  .def_property(

    "resolved",
    python::overload_cast<>( &Component::resolved, python::const_ ),
    python::overload_cast< std::vector< CompoundSystem > >( &Component::resolved ),
    "The compound systems that make up the resolved resonance data"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
