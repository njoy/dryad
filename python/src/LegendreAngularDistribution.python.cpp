// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/LegendreAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

void wrapLegendreAngularDistribution( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::LegendreAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LegendreAngularDistribution",
    "An angular distribution table"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double > >(),
    python::arg( "coefficients" ),
    "Initialise the angular distribution table\n\n"
    "Arguments:\n"
    "    self           the angular distribution table\n"
    "    coefficients   the coefficients of the Legendre series (from\n"
    "                   lowest to highest order coefficient)"
  )
  .def_property_readonly(

    "lower_cosine_limit",
    &Component::lowerCosineLimit,
    "The lower cosine limit"
  )
  .def_property_readonly(

    "upper_cosine_limit",
    &Component::upperCosineLimit,
    "The upper cosine limit"
  )
  .def(

    "__call__",
    [] ( const Component& self, double cosine ) -> decltype(auto)
       { return self( cosine ); },
    python::arg( "cosine" ),
    "Evaluate the table for a given cosine value\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    cosine    the cosine value"
  );

  // add standard tabulated data definitions
  addStandardSeriesDefinitions< Component >( component );
}
