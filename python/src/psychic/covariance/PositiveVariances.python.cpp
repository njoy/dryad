// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/psychic/covariance/PositiveVariances.hpp"

// namespace aliases
namespace python = pybind11;

namespace psychic {
namespace covariance {

void wrapPositiveVariances( python::module& module ) {

  // type aliases
  using Component = njoy::psychic::covariance::PositiveVariances;
  using TestStatus = njoy::psychic::TestStatus;
  using CrossSectionCovarianceMatrix = njoy::dryad::covariance::CrossSectionCovarianceMatrix;
  using AngularDistributionCovarianceMatrix = njoy::dryad::covariance::AngularDistributionCovarianceMatrix;
  using ProductMultiplicityCovarianceMatrix = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "PositiveVariances",
    "Test to verify if all variances are strictly positive"
  );
  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the test"
  )
  .def_property_readonly(

    "name",
    [] ( const Component& self ) { return self.name(); },
    "The test name"
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
    "Verify if the provided covariance matrix has variances that are strictly positive\n\n"
    "The test returns the following status values:\n\n"
    "  - Success : all variances are strictly positive\n"
    "  - Warning : all variances are positive\n"
    "  - Fail : some of the variances seem to be negative\n"
    "  - Skipped : the test was skipped\n\n"
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
    "Verify if the provided covariance matrix has variances that are strictly positive"
  )
  .def(

    "__call__",
    [] ( Component& self, const ProductMultiplicityCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix has variances that are strictly positive"
  );
}

} // covariance namespace
} // psychic namespace
