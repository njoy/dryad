// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/resonances/Kinematics.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapKinematics( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::Kinematics;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "Kinematics",
    "The kinematics option for resonance reconstruction\n\n"
    "This enum differentiates between relativistic and non-relativistic\n"
    "kinematics in resonance reconstruction calculations.\n\n"
    "Values\n"
    "------\n"
    "    NonRelativistic : 0\n"
    "        use non-relativistic kinematics\n"
    "    Relativistic : 1\n"
    "        use relativistic kinematics",
    python::arithmetic()
  );

  // wrap the component
  component
  .value(

    "NonRelativistic",
    Component::NonRelativistic,
    "Non-relativistic kinematics"
  )
  .value(

    "Relativistic",
    Component::Relativistic,
    "Relativistic kinematics"
  );
}

} // resonances namespace
} // dryad namespace
