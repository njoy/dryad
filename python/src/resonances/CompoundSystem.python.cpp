// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/CompoundSystem.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapCompoundSystem( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::CompoundSystem;
  using SpinGroup = njoy::dryad::resonances::SpinGroup;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CompoundSystem",
    "The compound nucleus system"
   );

  // wrap the component
  component
  .def(

    python::init< std::vector< SpinGroup > >(),
    python::arg( "spin_groups" ),
    "Initialise the spin group\n\n"
    "Arguments:\n"
    "    self          the compound system\n"
    "    spin_groups   the spin groups that make up the compound system"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property(

    "spin_groups",
    python::overload_cast<>( &Component::spinGroups, python::const_ ),
    python::overload_cast< std::vector< SpinGroup > >( &Component::spinGroups ),
    "The spin groups that make up the compound system"
  )
  .def(

    "cross_sections",
    &Component::crossSections,
    python::arg( "energy" ),
    python::arg( "xs" ),
    "Calculate the cross section values at a given energy\n\n"
    "Arguments:\n"
    "    self     the spin group\n"
    "    energy   the energy\n"
    "    xs       the cross section values"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
