// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/atomic/NonRadiativeTransitionData.hpp"

// namespace aliases
namespace python = pybind11;

namespace atomic {

void wrapNonRadiativeTransitionData( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::atomic::NonRadiativeTransitionData;
  using ElectronSubshellID = njoy::dryad::id::ElectronSubshellID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "NonRadiativeTransitionData",
    "A non-radiative transition in atomic relaxation\n\n"
    "In a non-radiative transition, an electron from another shell fills a\n"
    "vacancy in the current shell while another electron () is emitted. The\n"
    "energy of the emitted electron is equal to the binding energy of the\n"
    "subshell with the vacancy minus the binding energy of the subshell from\n"
    "which the electron filling the vacancy originated from and the subshell\n"
    "from which the emitted electron came from."
  );

  // wrap the component
  component
  .def(

    python::init< ElectronSubshellID, ElectronSubshellID, double >(),
    python::arg( "originating_shell" ), python::arg( "emitting_shell" ),
    python::arg( "probability" ),
    "Initialise the non-radiative transition data without transition energy\n\n"
    "Arguments:\n"
    "    self                the radiative transition data\n"
    "    originating_shell   the identifier of the subshell from which the\n"
    "                        vacancy filling electron originated\n"
    "    emitting_shell      the identifier of the subshell from which the\n"
    "                        emitted electron originated\n"
    "    probability         the probability of the transition"
  )
  .def(

    python::init< ElectronSubshellID, ElectronSubshellID, double, double >(),
    python::arg( "originating_shell" ), python::arg( "emitting_shell" ),
    python::arg( "probability" ), python::arg( "energy" ),
    "Initialise the non-radiative transition data with transition energy\n\n"
    "Arguments:\n"
    "    self                the radiative transition data\n"
    "    originating_shell   the identifier of the subshell from which the\n"
    "                        vacancy filling electron originated\n"
    "    emitting_shell      the identifier of the subshell from which the\n"
    "                        emitted electron originated\n"
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

    "emitting_shell",
    &Component::emittingShell,
    "The identifier of the subshell from which the emitted electron originated"
  )
  .def_property_readonly(

    "probability",
    &Component::probability,
    "The transition probability"
  )
  .def_property_readonly(

    "energy",
    &Component::energy,
    "The energy of the emitted electron"
  );
}

} // atomic namespace
