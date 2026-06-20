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
    "The resonance formalism for resonance reconstruction\n\n"
    "This enum differentiates between different resonance formalisms used\n"
    "in resonance reconstruction calculations.\n\n"
    "Values\n"
    "------\n"
    "    ReichMoore : 1\n"
    "         the Reich-Moore formalism using a single eliminated capture channel\n"
    "    GeneralRMatrix : 2\n"
    "         the general R-matrix formalism",
    python::arithmetic()
  );

  // wrap the component
  component
  .value( "ReichMoore", Component::ReichMoore,
          "Reich-Moore formalism with single eliminated capture channel" )
  .value( "GeneralRMatrix", Component::GeneralRMatrix,
          "General R-matrix formalism" );
}

} // resonances namespace
} // dryad namespace
