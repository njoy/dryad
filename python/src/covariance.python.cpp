// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace covariance {

  // declarations - matrices
  void wrapMatrixFunctions( python::module& );

  // declarations - metadata components
  void wrapCrossSectionMetaData( python::module& );

  // declarations - covariance components
  void wrapCrossSectionCovarianceBlock( python::module& );
}

void wrapCovariance( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "covariance",
    "Covariance data components"
  );

  // wrap components - matrices
  covariance::wrapMatrixFunctions( submodule );

  // declarations - metadata components
  covariance::wrapCrossSectionMetaData( submodule );

  // declarations - covariance components
  covariance::wrapCrossSectionCovarianceBlock( submodule );
}
