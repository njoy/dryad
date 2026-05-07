// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace psychic {
namespace covariance {

  // declarations - covariance tests
  void wrapPositiveSemiDefinite( python::module& );
}

void wrapCovariance( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "covariance",
    "Covariance data verification"
  );

  // declarations - covariance tests
  covariance::wrapPositiveSemiDefinite( submodule );
}

} // psychic namespace
