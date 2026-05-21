// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace psychic {
namespace covariance {

  // declarations - covariance tests
  void wrapPositiveVariances( python::module& );
  void wrapPositiveSemiDefinite( python::module& );
  void wrapEigenvalueRatio( python::module& );
  void wrapBoundedCorrelations( python::module& );
  void wrapDiagonalCorrelations( python::module& );
  void wrapTestSuite( python::module& );
}

void wrapCovariance( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "covariance",
    "Covariance data verification"
  );

  // declarations - covariance tests
  covariance::wrapPositiveVariances( submodule );
  covariance::wrapPositiveSemiDefinite( submodule );
  covariance::wrapEigenvalueRatio( submodule );
  covariance::wrapBoundedCorrelations( submodule );
  covariance::wrapDiagonalCorrelations( submodule );
  covariance::wrapTestSuite( submodule );
}

} // psychic namespace
