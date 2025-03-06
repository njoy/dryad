// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace covariance {

  // declarations - enumerators
  void wrapScalingType( python::module& );

  // declarations - matrices
  void wrapMatrixFunctions( python::module& );

  // declarations - metadata components
  void wrapCrossSectionMetadata( python::module& );
  void wrapVarianceScaling( python::module& );

  // declarations - covariance components
  void wrapCrossSectionCovarianceBlock( python::module& );
}

void wrapCovariance( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "covariance",
    "Covariance data components"
  );

  // wrap components - enumerators
  covariance::wrapScalingType( submodule );

  // wrap components - matrices
  covariance::wrapMatrixFunctions( submodule );

  // declarations - metadata components
  covariance::wrapCrossSectionMetadata( submodule );
  covariance::wrapVarianceScaling( submodule );

  // declarations - covariance components
  covariance::wrapCrossSectionCovarianceBlock( submodule );
}
