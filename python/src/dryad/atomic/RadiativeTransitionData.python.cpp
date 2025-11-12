// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/atomic/RadiativeTransitionData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
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
    "electron filling the vacancy originated from.\n\n"
    "\n"
    "Parameters\n"
    "----------\n"
    "    originating_shell: njoy.dryad.id.ElectronSubshellID \n"
    "                       the identifier of the subshell from which the\n"
    "                       vacancy filling electron originated\n"
    "    probability: float\n"
    "                  the probability of the transition\n"
    "    energy: float,  default: None\n"
    "              the energy of the emitted photon (default: undefined)\n\n"
    "Attributes\n"
    "----------\n"
    "    type : njoy.dryad.atomic.TransitionType\n"
    "          The transition type\n"
    "    originating_shell : njoy.dryad.id.ElectronSubshellID\n"
    "          The identifier of the subshell from which the electron filling the vacancy originated\n"
    "    probability : float\n"
    "           The transition probability\n"
    "    energy : float or None\n"
    "            The energy of the emitted photon\n"
  );

  // wrap the component
  component
  .def(

    python::init< ElectronSubshellID, double, std::optional< double > >(),
    python::arg( "originating_shell" ), python::arg( "probability" ),
    python::arg( "energy" ) = std::nullopt,
    "Initialise the radiative transition data\n\n"
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

    "probability",
    python::overload_cast<>( &Component::probability, python::const_ ),
    python::overload_cast< double >( &Component::probability ),
    "The transition probability"
  )
  .def_property(

    "energy",
    python::overload_cast<>( &Component::energy, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::energy ),
    "The energy of the emitted photon"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // atomic namespace
} // namespace dryad
