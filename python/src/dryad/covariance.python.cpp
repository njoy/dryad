// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

  // declarations - enumerators
  void wrapScalingType( python::module& );

  // declarations - metadata components
  void wrapVarianceScaling( python::module& );

  // declarations - covariance components
  void wrapCrossSectionMetadata( python::module& );
  void wrapCrossSectionCovarianceMatrix( python::module& );
  void wrapProductMultiplicityMetadata( python::module& );
  void wrapProductMultiplicityCovarianceMatrix( python::module& );
  void wrapLinearCombinationCovariance( python::module& );
  void wrapCrossSectionCovarianceData( python::module& );
  void wrapCovarianceData( python::module& );
}

void wrapCovariance( python::module& module ) {

  // create the submodule
  python::module submodule = module.def_submodule(

    "covariance",
    "Covariance data components"
  );

  // wrap components - enumerators
  covariance::wrapScalingType( submodule );

  // declarations - metadata components
  covariance::wrapVarianceScaling( submodule );

  // declarations - covariance components
  covariance::wrapCrossSectionMetadata( submodule );
  covariance::wrapCrossSectionCovarianceMatrix( submodule );
  covariance::wrapProductMultiplicityMetadata( submodule );
  covariance::wrapProductMultiplicityCovarianceMatrix( submodule );
  covariance::wrapLinearCombinationCovariance( submodule );
  covariance::wrapCrossSectionCovarianceData( submodule );
  covariance::wrapCovarianceData( submodule );
}

} // dryad namespace
