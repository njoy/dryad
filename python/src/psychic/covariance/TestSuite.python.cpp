// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/psychic/covariance/TestSuite.hpp"

// namespace aliases
namespace python = pybind11;

namespace psychic {
namespace covariance {

void wrapTestSuite( python::module& module ) {

  // type aliases
  using Component = njoy::psychic::covariance::TestSuite;
  using TestStatus = njoy::psychic::TestStatus;
  using CrossSectionCovarianceMatrix = njoy::dryad::covariance::CrossSectionCovarianceMatrix;
  using AngularDistributionCovarianceMatrix = njoy::dryad::covariance::AngularDistributionCovarianceMatrix;
  using ProductMultiplicityCovarianceMatrix = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TestSuite",
    "A comprehensive covariance test suite\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 1e-10\n"
    "        the comparison tolerance\n"
    "    negative : float, default -1e-10\n"
    "        the largest allowed negative eigenvalue\n"
    "    ratio : float, default 1e-8\n"
    "        the smallest allowable positive eigenvalue ratio"
  );
  // wrap the component
  component
  .def(

    python::init< double, double, double >(),
    python::arg( "tolerance" ) = njoy::constants::psychic::tolerance,
    python::arg( "negative" ) = njoy::constants::psychic::largest_allowed_negative_eigenvalue,
    python::arg( "ratio" ) = njoy::constants::psychic::smallest_eigenvalue_ratio,
    "Initialise the test suite"
  )
  .def_property_readonly(

    "name",
    [] ( const Component& self ) { return self.name(); },
    "The test name"
  )
  .def_property_readonly(

    "positive_variances",
    python::overload_cast<>( &Component::positiveVariances, python::const_ ),
    "The positive variance test"
  )
  .def_property_readonly(

    "positive_semi_definite",
    python::overload_cast<>( &Component::positiveSemiDefinite, python::const_ ),
    "The positive semi-definite test"
  )
  .def_property_readonly(

    "eigenvalue_ratio",
    python::overload_cast<>( &Component::eigenvalueRatio, python::const_ ),
    "The eigenvalue ratio test"
  )
  .def_property_readonly(

    "bounded_correlations",
    python::overload_cast<>( &Component::boundedCorrelations, python::const_ ),
    "The correlations between -1 and 1 test"
  )
  .def_property_readonly(

    "diagonal_correlations",
    python::overload_cast<>( &Component::diagonalCorrelations, python::const_ ),
    "The diagonal correlations are all 1 test"
  )
  .def_property_readonly(

    "tolerance",
    &Component::tolerance,
    "The comparison tolerance"
  )
  .def_property_readonly(

    "allowed_negative_eigen_value",
    &Component::allowedNegativeEigenValue,
    "The largest allowed negative eigenvalue"
  )
  .def_property_readonly(

    "smallest_acceptable_eigenvalue_ratio",
    &Component::smallestAcceptableEigenvalueRatio,
    "The  smallest acceptable eigenvalue ratio"
  )
  .def_property(

    "status",
    [] ( const Component& self ) { return self.status(); },
    [] ( Component& self, std::optional< TestStatus > status )
       { self.status( std::move( status ) ); },
    "The test status"
  )
  .def(

    "__call__",
    [] ( Component& self, const CrossSectionCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Perform the test suite on the provided covariance matrix\n\n"
    "Parameters\n"
    "----------\n"
    "    covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.AngularDistributionCovarianceMatrix or njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix\n"
    "        the covariance matrix instance to be tested"
  )
  .def(

    "__call__",
    [] ( Component& self, const AngularDistributionCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Perform the test suite on the provided covariance matrix"
  )
  .def(

    "__call__",
    [] ( Component& self, const ProductMultiplicityCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Perform the test suite on the provided covariance matrix"
  );
}

} // covariance namespace
} // psychic namespace
