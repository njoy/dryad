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
  using UnresolvedCompoundSystem = njoy::dryad::resonances::UnresolvedCompoundSystem;

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

    python::init< std::vector< CompoundSystem >,
                  std::optional< UnresolvedCompoundSystem > >(),
    python::arg( "resolved" ),
    python::arg( "unresolved" ) = std::nullopt,
    "Initialise the resonance parameters with resolved compound systems\n"
    "and an optional unresolved compound system"
  )
  .def_property(

    "resolved",
    python::overload_cast<>( &Component::resolved, python::const_ ),
    python::overload_cast< std::vector< CompoundSystem > >( &Component::resolved ),
    "The compound systems that make up the resolved resonance data"
  )
  .def_property(

    "unresolved",
    python::overload_cast<>( &Component::unresolved, python::const_ ),
    python::overload_cast< UnresolvedCompoundSystem >( &Component::unresolved ),
    "The compound system that makes up the unresolved resonance data"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
