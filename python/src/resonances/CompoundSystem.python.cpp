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
  using ReactionID = njoy::dryad::id::ReactionID;

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

    python::init< double, double, std::vector< SpinGroup > >(),
    python::arg( "lower_energy" ),
    python::arg( "upper_energy" ),
    python::arg( "spin_groups" ),
    "Initialise the spin group\n\n"
    "Arguments:\n"
    "    self           the compound system\n"
    "    lower_energy   the lower energy limit for the compound system\n"
    "    upper_energy   the upper energy limit for the compound system\n"
    "    spin_groups    the spin groups that make up the compound system"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
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
    python::overload_cast< std::vector< SpinGroup > >( &Component::spinGroups ),
    "The spin groups that make up the compound system"
  )
  .def(

    "cross_sections",
    [] ( Component& self, double energy ) -> std::map< ReactionID, double > {

      std::map< ReactionID, double > xs;
      self.crossSections( energy, xs );
      return xs;
    },
    python::arg( "energy" ),
    "Calculate the cross section values at a given energy\n\n"
    "Arguments:\n"
    "    self     the spin group\n"
    "    energy   the energy"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
