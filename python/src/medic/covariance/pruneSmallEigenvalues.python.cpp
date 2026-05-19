// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "njoy/medic/covariance/pruneSmallEigenvalues.hpp"

// namespace aliases
namespace python = pybind11;

namespace medic {
namespace covariance {

  void wrapPruneSmallEigenvalues( python::module& module ) {

    // type aliases
    using CrossSectionCovarianceMatrix = njoy::dryad::covariance::CrossSectionCovarianceMatrix;
    using ProductMultiplicityCovarianceMatrix = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;

    // wrap the function
    module
    .def(

      "prune_small_eigenvalues",
      python::overload_cast< CrossSectionCovarianceMatrix >( &njoy::medic::covariance::pruneSmallEigenvalues ),
      python::arg( "eigenvalue" ),
      python::arg( "covariance" ),
      "Prune eigenvalues below a given value from the covariance matrix\n\n"
      "Parameters\n"
      "----------\n"
      "    eigenvalue : float\n"
      "        the smallest allowed eigenvalue\n"
      "    covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix\n"
      "        the covariance matrix to be modified"
    )
    .def(

      "prune_small_eigenvalues",
      python::overload_cast< ProductMultiplicityCovarianceMatrix >( &njoy::medic::covariance::pruneSmallEigenvalues ),
      python::arg( "eigenvalue" ),
      python::arg( "covariance" ),
      "Prune eigenvalues below a given value from the covariance matrix"
    );
  }
} // covariance namespace
} // medic namespace
