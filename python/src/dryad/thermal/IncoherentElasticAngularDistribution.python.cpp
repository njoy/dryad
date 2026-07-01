// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/thermal/IncoherentElasticAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapIncoherentElasticAngularDistribution( python::module& module ) {

  // constants
  std::ostringstream tolerance;
  tolerance << std::setprecision( 4 ) << njoy::constants::linearisation::tolerance;

  // type aliases
  using Component = njoy::dryad::thermal::IncoherentElasticAngularDistribution;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IncoherentElasticAngularDistribution",
    "Incoherent elastic thermal scattering angular distribution defined by an\n"
    "analytical pdf and cdf"
  );

  // wrap the component
  component
  .def(

    python::init< double, double >(),
    python::arg( "incident" ),
    python::arg( "debye_waller_integral" ),
    "Initialise the angular distribution\n\n"
    "Parameters\n"
    "----------\n"
    "    incident : float\n"
    "        the incident energy\n"
    "    debye_waller_integral : float\n"
    "        the Debye-Waller integral value"
  )
  .def_property_readonly(

    "incident_energy",
    python::overload_cast<>( &Component::incidentEnergy, python::const_ ),
    "The incident energy value"
  )
  .def_property_readonly(

    "debye_waller_integral",
    python::overload_cast<>( &Component::debyeWallerIntegral, python::const_ ),
    "The Debye-Waller integral value"
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
    std::string( "Linearise the distribution\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    tolerance : float, default " + tolerance.str() + "\n"
                 "        the linearisation tolerance\n"
                 "    normalise : bool, default False\n"
                 "        option to indicate whether or not to normalise\n"
                 "        all probability data (default: no normalisation)" ).c_str()
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
