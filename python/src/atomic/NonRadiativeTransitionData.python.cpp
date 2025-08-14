// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/atomic/NonRadiativeTransitionData.hpp"

// namespace aliases
namespace python = pybind11;

namespace atomic {

void wrapNonRadiativeTransitionData( python::module& module ) {

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

    python::init< ElectronSubshellID, ElectronSubshellID,
                  double, std::optional< double > >(),
    python::arg( "originating_shell" ), python::arg( "emitting_shell" ),
    python::arg( "probability" ), python::arg( "energy" ) = std::nullopt,
    "Initialise the non-radiative transition data\n\n"
    "Arguments:\n"
    "    self                the radiative transition data\n"
    "    originating_shell   the identifier of the subshell from which the\n"
    "                        vacancy filling electron originated\n"
    "    emitting_shell      the identifier of the subshell from which the\n"
    "                        emitted electron originated\n"
    "    probability         the probability of the transition\n"
    "    energy              the energy of the emitted electron (default: undefined)"
  )
  .def_property_readonly(

    "type",
    [] ( const Component& self ) ->decltype(auto) { return self.type(); },
    "The transition type"
  )
  .def_property(

    "originating_shell",
    python::overload_cast<>( &Component::originatingShell, python::const_ ),
    python::overload_cast< ElectronSubshellID >( &Component::originatingShell ),
    "The identifier of the subshell from which the electron filling the vacancy "
    "originated"
  )
  .def_property(

    "emitting_shell",
    python::overload_cast<>( &Component::emittingShell, python::const_ ),
    python::overload_cast< ElectronSubshellID >( &Component::emittingShell ),
    "The identifier of the subshell from which the emitted electron originated"
  )
  .def_property(

    "probability",
    python::overload_cast<>( &Component::probability, python::const_ ),
    python::overload_cast< double >( &Component::probability ),
    "The transition probability"
  )
  .def_property(

    "energy",
    python::overload_cast<>( &Component::energy, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::energy ),
    "The energy of the emitted electron"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // atomic namespace
