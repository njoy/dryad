// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/AtomicRelaxation.hpp"

// namespace aliases
namespace python = pybind11;

void wrapAtomicRelaxation( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::AtomicRelaxation;
  using ElementID = njoy::dryad::id::ElementID;
  using ElectronSubshellConfiguration = njoy::dryad::atomic::ElectronSubshellConfiguration;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "AtomicRelaxation",
    "Atomic relaxation data for a given element"
  );

  // wrap the component
  component
  .def(

    python::init< ElementID, std::vector< ElectronSubshellConfiguration > >(),
    python::arg( "element" ), python::arg( "subshells" ),
    "Initialise the atomic relaxation data\n\n"
    "Arguments:\n"
    "    self         the reaction\n"
    "    element      the element identifier\n"
    "    subshells    the electron subshell configuration data"
  )
  .def_property_readonly(

    "element_identifier",
    &Component::elementIdentifier,
    "The element identifier"
  )
  .def_property_readonly(

    "subshells",
    &Component::subshells,
    "The electron shell configuration data"
  );
}
