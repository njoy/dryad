// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/UnresolvedCompoundSystem.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapUnresolvedCompoundSystem( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::UnresolvedCompoundSystem;
  using UnresolvedSpinGroup = njoy::dryad::resonances::UnresolvedSpinGroup;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedCompoundSystem",
    "The compound nucleus system for the unresolved resonance region"
  );

  // wrap the component
  component
  .def(

    python::init< double, double, std::vector< UnresolvedSpinGroup > >(),
    python::arg( "lower_energy" ),
    python::arg( "upper_energy" ),
    python::arg( "spin_groups" ),
    "Initialise the unresolved compound system\n\n"
    "If the spin groups are not sorted, they will get sorted using a J,parity,l\n"
    "ordering.\n\n"
    "Arguments:\n"
    "    self           the unresolved compound system\n"
    "    lower_energy   the lower energy limit for the unresolved compound system\n"
    "    upper_energy   the upper energy limit for the unresolved compound system\n"
    "    spin_groups    the unresolved spin groups that make up the compound system"
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

    "spin_groups",
    python::overload_cast<>( &Component::spinGroups, python::const_ ),
    python::overload_cast< std::vector< UnresolvedSpinGroup > >( &Component::spinGroups ),
    "The unresolved spin groups that make up the compound system"
  )
  .def_property_readonly(

    "reactions",
    python::overload_cast<>( &Component::reactions, python::const_ ),
    "The reactions to which this compound system contributes"
  );

  // TODO: wrap cross_sections once UnresolvedCompoundSystem::crossSections
  //       exists (see the TODO in UnresolvedCompoundSystem.hpp).

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
