// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/atomic/TransitionType.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace atomic {

void wrapTransitionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::atomic::TransitionType;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "TransitionType",
    "The type of transition in an atomic relaxation",
    python::arithmetic()
  );

  // wrap the component
  component
  .value(

    "Radiative",
    Component::Radiative,
    "A radiative transition, an electron from another shell fills a vacancy in the current\n"
    "shell while emitting a photon"
  )
  .value(

    "NonRadiative",
    Component::NonRadiative,
    "An electron from another shell fills a vacancy in the current shell while another electron\n"
    "is emitted"
  );
}

} // namespace atomic
} // namespace dryad
