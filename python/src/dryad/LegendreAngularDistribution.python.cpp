// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/LegendreAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapLegendreAngularDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::LegendreAngularDistribution;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LegendreAngularDistribution",
    "An angular distribution defined by a pdf and cdf using a Legendre series\n"
    "expansion"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, bool >(),
    python::arg( "coefficients" ), python::arg( "normalise" ) = false,
    "Initialise the angular distribution\n\n"
    "Parameters\n"
    "----------\n"
    "    coefficients : list of float\n"
    "        the coefficients of the Legendre series (from\n"
    "        lowest to highest order coefficient)\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  )
  .def_property_readonly(

    "coefficients",
    &Component::coefficients,
    "The coefficients"
  )
  .def_property_readonly(

    "pdf",
    python::overload_cast<>( &Component::pdf, python::const_ ),
    "The probability distribution function (pdf) of the distribution"
  )
  .def_property_readonly(

    "cdf",
    python::overload_cast<>( &Component::cdf, python::const_ ),
    "The cumulative distribution function (cdf) of the distribution"
  )
  .def(

    "__call__",
    [] ( const Component& self, double cosine ) -> decltype(auto)
       { return self( cosine ); },
    python::arg( "cosine" ),
    "Evaluate the pdf of the distribution for a given cosine value\n\n"
    "Parameters\n"
    "----------\n"
    "    cosine : float\n"
    "        the cosine value"
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
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    python::arg( "normalise" ) = false,
    "Linearise the distribution\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 0.001\n"
    "        the linearisation tolerance\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
