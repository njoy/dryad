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
  using ChannelRadii = njoy::dryad::resonances::ChannelRadii;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceParameters",
    "The resonance parameter data\n\n"
    "Parameters\n"
    "----------\n"
    "    resolved : list of njoy.dryad.resonances.CompoundSystem, optional\n"
    "        the resolved resonance compound systems\n"
    "    unresolved : njoy.dryad.resonances.UnresolvedCompoundSystem, optional\n"
    "        the resolved resonance compound systems\n"
    "    lower_energy : float\n"
    "        the lower energy limit for the compound system\n"
    "    upper_energy : float\n"
    "        the upper energy limit for the compound system\n"
    "    radius : float\n"
    "        the scattering radius"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< CompoundSystem >,
                  std::optional< UnresolvedCompoundSystem > >(),
    python::arg( "resolved" ),
    python::arg( "unresolved" ) = std::nullopt,
    "Initialise the resonance parameters with resolved compound systems\n"
    "and an optional unresolved compound system"
  )
  .def(

    python::init< double, double, double >(),
    python::arg( "lower_energy" ),
    python::arg( "upper_energy" ),
    python::arg( "radius" ),
    "Initialise the resonance parameters with a scattering radius"
  )
  .def_property(

    "lower_energy_limit",
    python::overload_cast<>( &Component::lowerEnergyLimit, python::const_ ),
    python::overload_cast< double >( &Component::lowerEnergyLimit ),
    "The lower energy limit"
  )
  .def_property(

    "upper_energy_limit",
    python::overload_cast<>( &Component::upperEnergyLimit, python::const_ ),
    python::overload_cast< double >( &Component::upperEnergyLimit ),
    "The upper energy limit"
  )
  .def_property(

    "scattering_radius",
    python::overload_cast<>( &Component::scatteringRadius, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::scatteringRadius ),
    "The scattering radius"
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
  )
  .def_property_readonly(

    "reactions",
    python::overload_cast<>( &Component::reactions, python::const_ ),
    "The reactions to which the resonance parameters contribute"
  )
  .def_property_readonly(

    "has_parameters",
    python::overload_cast<>( &Component::hasParameters, python::const_ ),
    "Return whether or not resonance parameters are given"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
