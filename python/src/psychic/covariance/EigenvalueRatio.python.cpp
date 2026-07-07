// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>
#include <iomanip>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/psychic/covariance/EigenvalueRatio.hpp"

// namespace aliases
namespace python = pybind11;

namespace psychic {
namespace covariance {

void wrapEigenvalueRatio( python::module& module ) {

  // constants
  std::ostringstream ratio;
  ratio << std::setprecision( 1 ) << njoy::constants::psychic::smallest_eigenvalue_ratio;

  // type aliases
  using Component = njoy::psychic::covariance::EigenvalueRatio;
  using TestStatus = njoy::psychic::TestStatus;
  using CrossSectionCovarianceMatrix = njoy::dryad::covariance::CrossSectionCovarianceMatrix;
  using AngularDistributionCovarianceMatrix = njoy::dryad::covariance::AngularDistributionCovarianceMatrix;
  using ProductMultiplicityCovarianceMatrix = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "EigenvalueRatio",
    ( "Test to verify if the positive eigenvalue ratio looks reasonable\n\n"
      "Parameters\n"
      "----------\n"
      "    ratio : float, default " + ratio.str() + "\n"
      "        the smallest allowable positive eigenvalue ratio" ).c_str()
  );
  // wrap the component
  component
  .def(

    python::init< double >(),
    python::arg( "ratio" ) = njoy::constants::psychic::smallest_eigenvalue_ratio,
    "Initialise the test"
  )
  .def_property_readonly(

    "name",
    [] ( const Component& self ) { return self.name(); },
    "The test name"
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
  .def_property(

    "smallest_positive_eigenvalue",
    python::overload_cast<>( &Component::smallestPositiveEigenvalue, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::smallestPositiveEigenvalue ),
    "The smallest positive eigenvalue that was found"
  )
  .def_property(

    "largest_positive_eigenvalue",
    python::overload_cast<>( &Component::largestPositiveEigenvalue, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::largestPositiveEigenvalue ),
    "The largest positive eigenvalue that was found"
  )
  .def_property(

    "eigenvalue_ratio",
    python::overload_cast<>( &Component::eigenvalueRatio, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::eigenvalueRatio ),
    "The positive eigenvalue ratio"
  )
  .def(

    "__call__",
    [] ( Component& self, const CrossSectionCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix has a reasonable eigenvalue ratio\n\n"
    "The test returns the following status values:\n\n"
    "  - Success : the eigenvalue ratio is larger than or equal to the smallest allowed ratio\n"
    "  - Fail    : the eigenvalue ratio is smaller than the smallest allowed ratio\n"
    "  - Skipped : the test was skipped\n\n"
    "The smallest and largest positive eigenvalue and their ratio is always available.\n\n"
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
    "Verify if the provided covariance matrix has a reasonable eigenvalue ratio"
  )
  .def(

    "__call__",
    [] ( Component& self, const ProductMultiplicityCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix has a reasonable eigenvalue ratio"
  );
}

} // covariance namespace
} // psychic namespace
