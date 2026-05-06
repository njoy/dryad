// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/psychic/covariance/IsPositiveSemiDefinite.hpp"

// namespace aliases
namespace python = pybind11;

namespace psychic {
namespace covariance {

void wrapIsPositiveSemiDefinite( python::module& module ) {

  // type aliases
  using Component = njoy::psychic::covariance::IsPositiveSemiDefinite;
  using TestStatus = njoy::psychic::TestStatus;
  using CrossSectionCovarianceMatrix = njoy::dryad::covariance::CrossSectionCovarianceMatrix;
  using ProductMultiplicityCovarianceMatrix = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IsPositiveSemiDefinite",
    "Test to verify if a covariance matrix is positive semi-definite\n\n"
    "Parameters\n"
    "----------\n"
    "    negative : float, default -1e-10\n"
    "         the largest allowed negative eigenvalue"
  );
  // wrap the component
  component
  .def(

    python::init< double >(),
    python::arg( "negative" ) = njoy::constants::psychic::largest_allowed_negative_eigenvalue,
    "Initialise the test"
  )
  .def_property_readonly(

    "name",
    [] ( const Component& self ) { return self.name(); },
    "The test name"
  )
  .def_property_readonly(

    "allowed_negative_eigen_value",
    &Component::allowedNegativeEigenValue,
    "The largest allowed negative eigenvalue"
  )
  .def_property(

    "status",
    [] ( const Component& self ) { return self.status(); },
    [] ( Component& self, std::optional< TestStatus > status )
       { self.status( std::move( status ) ); },
    "The test status"
  )
  .def_property(

    "largest_negative_eigen_value",
    python::overload_cast<>( &Component::largestNegativeEigenValue, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::largestNegativeEigenValue ),
    "The largest negative eigenvalue that was found"
  )
  .def(

    "__call__",
    [] ( Component& self, const CrossSectionCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix is positive semi-definite\n\n"
    "A covariance matrix is positive semi-definite if it is a square symmetric matrix\n"
    "that has eigenvalues that are larger than or equal to zero. Construction of\n"
    "on-diagonal covariance matrices already requires square and symmetric matrices so\n"
    "this particular aspect is not tested here.\n\n"
    "The test returns the following status values:\n"
    "  - Success : the on-diagonal covariance matrix is positive semi-definite\n"
    "  - Warning : the on-diagonal covariance matrix is can be considered positive\n"
    "              semi-definite by accepting small negative eigenvalues\n"
    "  - Fail : the on-diagonal covariance matrix is not positive semi-definite\n"
    "  - Skipped : the covariance matrix provided is not on-diagonal (ie its eigenvalues)\n"
    "              cannot be calculated\n\n"
    "The largest negative eigenvalue is available for the Warning and Fail state.\n"
    "Parameters\n"
    "----------\n"
    "    covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix\n"
    "        the covariance matrix instance to be tested"
  )
  .def(

    "__call__",
    [] ( Component& self, const ProductMultiplicityCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix is positive semi-definite\n\n"
    "A covariance matrix is positive semi-definite if it is a square symmetric matrix\n"
    "that has eigenvalues that are larger than or equal to zero. Construction of\n"
    "on-diagonal covariance matrices already requires square and symmetric matrices so\n"
    "this particular aspect is not tested here.\n\n"
    "The test returns the following status values:\n"
    "  - Success : the on-diagonal covariance matrix is positive semi-definite\n"
    "  - Warning : the on-diagonal covariance matrix is can be considered positive\n"
    "              semi-definite by accepting small negative eigenvalues\n"
    "  - Fail : the on-diagonal covariance matrix is not positive semi-definite\n"
    "  - Skipped : the covariance matrix provided is not on-diagonal (ie its eigenvalues)\n"
    "              cannot be calculated\n\n"
    "The largest negative eigenvalue is available for the Warning and Fail state.\n"
    "Parameters\n"
    "----------\n"
    "    covariance : njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix\n"
    "        the covariance matrix instance to be tested"
  );
}

} // covariance namespace
} // psychic namespace
