// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/dryad/resonances/Formalism.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapFormalism( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::Formalism;

  // wrap views created by this component

  // create the component
  python::enum_< Component > component(

    module,
    "Formalism",
    "The resonance formalism",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "ReichMoore", Component::ReichMoore )
  .value( "GeneralRMatrix", Component::GeneralRMatrix );
}

} // resonances namespace
} // dryad namespace
