// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/covariance/CovarianceData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

void wrapCovarianceData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::CovarianceData;
  using CrossSectionCovarianceData = njoy::dryad::covariance::CrossSectionCovarianceData;
  using AngularDistributionCovarianceData = njoy::dryad::covariance::AngularDistributionCovarianceData;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CovarianceData",
    "The covariance data\n\n"
    "Parameters\n"
    "----------\n"
    "    xs : njoy.dryad.covariance.CrossSectionCovarianceData \n"
    "        the cross section covariance data\n"
    "    angular : njoy.dryad.covariance.AngularDistributionCovarianceData \n"
    "        the angular distribution covariance data"
  );

  // wrap the component
  component
  .def(

    python::init< std::optional< CrossSectionCovarianceData >,
                  std::optional< AngularDistributionCovarianceData > >(),
    python::arg( "xs" ),
    python::arg( "angular" ),
    "Initialise the covariance data"
  )
  .def_property_readonly(

    "has_cross_section_covariances",
    &Component::hasCrossSectionCovariances,
    "Return whether or not there are cross section covariances"
  )
  .def_property_readonly(

    "has_angular_distribution_covariances",
    &Component::hasAngularDistributionCovariances,
    "Return whether or not there are angular distribution covariances"
  )
  .def_property_readonly(

    "cross_section",
    python::overload_cast<>( &Component::crossSection, python::const_ ),
    "The cross section covariances"
  )
  .def_property_readonly(

    "angular_distribution",
    python::overload_cast<>( &Component::angularDistribution, python::const_ ),
    "The angular distribution covariances"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // covariance namespace
} // dryad namespace
