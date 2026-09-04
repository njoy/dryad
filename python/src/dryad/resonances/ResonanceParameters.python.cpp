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
    "ResonanceParameters",
    "The resonance parameter data\n\n"
    "Parameters\n"
    "----------\n"
    "    resolved : list of njoy.dryad.resonances.CompoundSystem, optional\n"
    "        the resolved resonance compound systems"
  );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the resonance parameters with default values"
  )
  .def(

    python::init< std::vector< CompoundSystem > >(),
    python::arg( "resolved" ),
    "Initialise the resonance parameters with resolved compound systems"
  )
  .def_property(

    "resolved",
    python::overload_cast<>( &Component::resolved, python::const_ ),
    python::overload_cast< std::vector< CompoundSystem > >( &Component::resolved ),
    "The compound systems that make up the resolved resonance data"
  )
  .def_property_readonly(

    "reactions",
    python::overload_cast<>( &Component::reactions, python::const_ ),
    "The reactions to which the resonance parameters contribute"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
