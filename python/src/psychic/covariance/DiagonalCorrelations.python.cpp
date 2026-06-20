// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/psychic/covariance/DiagonalCorrelations.hpp"

// namespace aliases
namespace python = pybind11;

namespace psychic {
namespace covariance {

void wrapDiagonalCorrelations( python::module& module ) {

  // type aliases
  using Component = njoy::psychic::covariance::DiagonalCorrelations;
  using TestStatus = njoy::psychic::TestStatus;
  using CrossSectionCovarianceMatrix = njoy::dryad::covariance::CrossSectionCovarianceMatrix;
  using AngularDistributionCovarianceMatrix = njoy::dryad::covariance::AngularDistributionCovarianceMatrix;
  using ProductMultiplicityCovarianceMatrix = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "DiagonalCorrelations",
    "Test to verify if all diagonal correlation values are equal to 1\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 1e-10\n"
    "         the comparison tolerance"
  );
  // wrap the component
  component
  .def(

    python::init< double >(),
    python::arg( "tolerance" ) = njoy::constants::psychic::tolerance,
    "Initialise the test"
  )
  .def_property_readonly(

    "name",
    [] ( const Component& self ) { return self.name(); },
    "The test name"
  )
  .def_property_readonly(

    "tolerance",
    &Component::tolerance,
    "The comparison tolerance"
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
    "Verify if the provided covariance matrix has diagonal correlations equal to 1\n\n"
    "The test returns the following status values:\n"
    "  - Success : all diagonal correlations are equal to 1\n"
    "  - Warning : all diagonal correlations are equal to 1, taking into account a tolerance\n"
    "  - Fail : not all diagonal correlations are equal to 1\n"
    "  - Skipped : the test was skipped\n\n"
    "Parameters\n"
    "----------\n"
    "    covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix,\n"
    "                 njoy.dryad.covariance.AngularDistributionCovarianceMatrix or\n"
    "                 njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix\n"
    "         the covariance matrix instance to be tested"
  )
  .def(

    "__call__",
    [] ( Component& self, const AngularDistributionCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix has diagonal correlations equal to 1"
  )
  .def(

    "__call__",
    [] ( Component& self, const ProductMultiplicityCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix has diagonal correlations equal to 1"
  );
}

} // covariance namespace
} // psychic namespace
