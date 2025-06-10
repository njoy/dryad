// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/atomic/RadiativeTransitionData.hpp"

// namespace aliases
namespace python = pybind11;

namespace atomic {

void wrapRadiativeTransitionData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::atomic::RadiativeTransitionData;
  using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "RadiativeTransitionData",
    "A radiative transition in atomic relaxation\n\n"
    "In a radiative transition, an electron from another shell fills a\n"
    "vacancy in the current shell while emitting a photon. The energy of\n"
    "the emitted photon is equal to the difference in binding energies\n"
    "between the subshell with the vacancy and the subshell from which the\n"
    "electron filling the vacancy originated from."
  );

  // wrap the component
  component
  .def(

    python::init< ElectronSubshellID, double >(),
    python::arg( "originating_shell" ), python::arg( "probability" ),
    "Initialise the radiative transition data without transition energy\n\n"
    "Arguments:\n"
    "    self                the radiative transition data\n"
    "    originating_shell   the identifier of the subshell from which the\n"
    "                        vacancy filling electron originated\n"
    "    probability         the probability of the transition"
  )
  .def(

    python::init< ElectronSubshellID, double, double >(),
    python::arg( "originating_shell" ), python::arg( "probability" ),
    python::arg( "energy" ),
    "Initialise the radiative transition data with transition energy\n\n"
    "Arguments:\n"
    "    self                the radiative transition data\n"
    "    originating_shell   the identifier of the subshell from which the\n"
    "                        vacancy filling electron originated\n"
    "    probability         the probability of the transition\n"
    "    energy              the energy of the emitted particle"
  )
  .def_property_readonly(

    "type",
    [] ( const Component& self ) ->decltype(auto) { return self.type(); },
    "The transition type"
  )
  .def_property_readonly(

    "originating_shell",
    &Component::originatingShell,
    "The identifier of the subshell from which the electron filling the vacancy "
    "originated"
  )
  .def_property_readonly(

    "probability",
    &Component::probability,
    "The transition probability"
  )
  .def_property_readonly(

    "energy",
    python::overload_cast<>( &Component::energy, python::const_ ),
    "The energy of the emitted photon"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // atomic namespace
