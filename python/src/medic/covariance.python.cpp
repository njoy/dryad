// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace medic {
namespace covariance {

  // declarations - covariance related functions
  void wrapPruneSmallEigenvalues( python::module& );
}

void wrapCovariance( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "covariance",
    "Covariance functions"
  );

  // declarations - covariance functions
  covariance::wrapPruneSmallEigenvalues( submodule );
}

} // medic namespace
