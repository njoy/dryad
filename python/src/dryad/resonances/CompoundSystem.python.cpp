// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
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
    "The compound nucleus system for resonance reconstruction\n\n"
    "Parameters\n"
    "----------\n"
    "    lower_energy : float\n"
    "        the lower energy limit for the compound system\n"
    "    upper_energy : float\n"
    "        the upper energy limit for the compound system\n"
    "    spin_groups : list of njoy.dryad.resonances.SpinGroup\n"
    "        the spin groups that make up the compound system"
   );

  // wrap the component
  component
  .def(

    python::init< double, double, std::vector< SpinGroup > >(),
    python::arg( "lower_energy" ),
    python::arg( "upper_energy" ),
    python::arg( "spin_groups" ),
    "Initialise the compound system"
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
  .def_property_readonly(

    "reactions",
    python::overload_cast<>( &Component::reactions, python::const_ ),
    "The reactions to which this compound system contributes"
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
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy value"
  )
  .def(

    "cross_sections",
    [] ( Component& self, std::vector<double> energies ) -> std::map< ReactionID, std::vector<double> > {

      std::map< ReactionID, std::vector<double> > xs;
      self.crossSections( energies, xs );
      return xs;
    },
    python::arg( "energies" ),
    "Calculate the cross section values for a list of energies\n\n"
    "Parameters\n"
    "----------\n"
    "    energies : list of float\n"
    "        the energy values"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
