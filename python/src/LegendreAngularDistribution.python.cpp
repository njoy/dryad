// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/LegendreAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

void wrapLegendreAngularDistribution( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::LegendreAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LegendreAngularDistribution",
    "An angular distribution defined by a pdf and cdf using Legendre expansions"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double > >(),
    python::arg( "coefficients" ),
    "Initialise the angular distribution\n\n"
    "Arguments:\n"
    "    self           the angular distribution\n"
    "    coefficients   the coefficients of the Legendre series (from\n"
    "                   lowest to highest order coefficient) for the pdf"
  )
  .def_property_readonly(

    "pdf",
    &Component::pdf,
    "The probability distribution function (pdf) of the distribution"
  )
  .def_property_readonly(

    "cdf",
    &Component::cdf,
    "The cumulative distribution function (cdf) of the distribution"
  )
  .def_property_readonly(

    "average_cosine",
    &Component::averageCosine,
    "The average cosine defined by the distribution"
  )
  .def(

    "__call__",
    [] ( const Component& self, double cosine ) -> decltype(auto)
       { return self( cosine ); },
    python::arg( "cosine" ),
    "Evaluate the pdf of the distribution for a given cosine value\n\n"
    "Arguments:\n"
    "    self      the distribution\n"
    "    cosine    the cosine value"
  );
}
