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
    using AngularDistributionCovarianceMatrix = njoy::dryad::covariance::AngularDistributionCovarianceMatrix;
    using ProductMultiplicityCovarianceMatrix = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;

    // wrap the function
    module
    .def(

      "prune_small_eigenvalues",
      [] ( double eigenvalue, CrossSectionCovarianceMatrix& covariance ) -> void
         { return njoy::medic::covariance::pruneSmallEigenvalues( eigenvalue, covariance ); },
      python::arg( "eigenvalue" ),
      python::arg( "covariance" ),
      "Prune eigenvalues below a given value from the covariance matrix\n\n"
      "Parameters\n"
      "----------\n"
      "    eigenvalue : float\n"
      "        the smallest allowed eigenvalue\n"
      "    covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix,\n"
      "                 njoy.dryad.covariance.AngularDistributionCovarianceMatrix or\n"
      "                 njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix"
      "        the covariance matrix to be modified"
    )
    .def(

      "prune_small_eigenvalues",
      [] ( double eigenvalue, AngularDistributionCovarianceMatrix& covariance ) -> void
         { return njoy::medic::covariance::pruneSmallEigenvalues( eigenvalue, covariance ); },
      python::arg( "eigenvalue" ),
      python::arg( "covariance" ),
      "Prune eigenvalues below a given value from the covariance matrix"
    )
    .def(

      "prune_small_eigenvalues",
      [] ( double eigenvalue, ProductMultiplicityCovarianceMatrix& covariance ) -> void
         { return njoy::medic::covariance::pruneSmallEigenvalues( eigenvalue, covariance ); },
      python::arg( "eigenvalue" ),
      python::arg( "covariance" ),
      "Prune eigenvalues below a given value from the covariance matrix"
    );
  }
} // covariance namespace
} // medic namespace
