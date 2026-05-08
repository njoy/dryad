// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/psychic/covariance/BoundedCorrelations.hpp"

// namespace aliases
namespace python = pybind11;

namespace psychic {
namespace covariance {

void wrapBoundedCorrelations( python::module& module ) {

  // type aliases
  using Component = njoy::psychic::covariance::BoundedCorrelations;
  using TestStatus = njoy::psychic::TestStatus;
  using CrossSectionCovarianceMatrix = njoy::dryad::covariance::CrossSectionCovarianceMatrix;
  using ProductMultiplicityCovarianceMatrix = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "BoundedCorrelations",
    "Test to verify if all correlation values are between -1 and 1\n\n"
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
  .def_property(

    "smallest_correlation",
    python::overload_cast<>( &Component::smallestCorrelation, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::smallestCorrelation ),
    "The smallest correlation value that was found"
  )
  .def_property(

    "largest_correlation",
    python::overload_cast<>( &Component::largestCorrelation, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::largestCorrelation ),
    "The largest correlation value that was found"
  )
  .def(

    "__call__",
    [] ( Component& self, const CrossSectionCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix has correlations between -1 and 1\n\n"
    "The test returns the following status values:\n"
    "  - Success : the correlations are between -1 and 1\n"
    "  - Warning : the correlations are between -1 and 1, taking into account a tolerance\n"
    "  - Fail : the correlations matrix are outside the -1 and 1 range\n"
    "  - Skipped : the covariance matrix provided is not on-diagonal\n\n"
    "The smallest and largest correlation values are available for the Warning and Fail state.\n\n"
    "Parameters\n"
    "----------\n"
    "    covariance : njoy.dryad.covariance.CrossSectionCovarianceMatrix, njoy.dryad.covariance.ProductMultiplicityCovarianceMatrix\n"
    "        the covariance matrix instance to be tested"
  )
  .def(

    "__call__",
    [] ( Component& self, const ProductMultiplicityCovarianceMatrix& covariance ) -> decltype(auto)
       { return self( covariance ); },
    python::arg( "covariance" ),
    "Verify if the provided covariance matrix has correlations between -1 and 1"
  );
}

} // covariance namespace
} // psychic namespace
