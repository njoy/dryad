// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/LegendreAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

void wrapLegendreAngularDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::LegendreAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LegendreAngularDistribution",
    "An angular distribution defined by a pdf and cdf using a Legendre series\n"
    "expansion\n\n"
    "The pdf is normalised to 1 upon construction and the associated cdf is\n"
    "calculated upon construction (after the pdf has been normalised)."
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, bool >(),
    python::arg( "coefficients" ), python::arg( "normalise" ) = false,
    "Initialise the angular distribution\n\n"
    "Arguments:\n"
    "    self           the angular distribution\n"
    "    coefficients   the coefficients of the Legendre series (from\n"
    "                   lowest to highest order coefficient) for the pdf\n"
    "    normalise      option to indicate whether or not to normalise\n"
    "                   all probability data (default: no normalisation)"
  )
  .def_property_readonly(

    "coefficients",
    &Component::coefficients,
    "The coefficients"
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
  .def(

    "__call__",
    [] ( const Component& self, double cosine ) -> decltype(auto)
       { return self( cosine ); },
    python::arg( "cosine" ),
    "Evaluate the pdf of the distribution for a given cosine value\n\n"
    "Arguments:\n"
    "    self      the angular distribution\n"
    "    cosine    the cosine value"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution"
  )
  .def_property_readonly(

    "average_cosine",
    &Component::averageCosine,
    "The average cosine defined by the distribution"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the distribution\n\n"
    "Arguments:\n"
    "    self        the angular distribution\n"
    "    tolerance   the linearisation tolerance"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}
