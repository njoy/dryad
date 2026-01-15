// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/atomic/NonRadiativeTransitionData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
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
    "from which the emitted electron came from.\n\n"
    "Parameters\n"
    "----------\n"
    "    originating_shell :  njoy.dryad.id.ElectronSubshellID\n"
    "        the identifier of the subshell from which the vacancy filling electron originated\n"
    "    emitting_shell : njoy.dryad.id.ElectronSubshellID\n"
    "        the identifier of the subshell from which the emitted electron originated\n"
    "    probability : float\n"
    "        the probability of the transition\n"
    "    energy : float, default none\n"
    "        the energy of the emitted electron\n\n"
  );

  // wrap the component
  component
  .def(

    python::init< ElectronSubshellID, ElectronSubshellID,
                  double, std::optional< double > >(),
    python::arg( "originating_shell" ), python::arg( "emitting_shell" ),
    python::arg( "probability" ), python::arg( "energy" ) = std::nullopt,
    ""
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

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // atomic namespace
} // namespace dryad
