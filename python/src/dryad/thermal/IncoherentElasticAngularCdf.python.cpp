// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/IncoherentElasticAngularCdf.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapIncoherentElasticAngularCdf( python::module& module ) {

  // constants
  std::ostringstream tolerance;
  tolerance << std::setprecision( 4 ) << njoy::constants::linearisation::tolerance;

  // type aliases
  using Component = njoy::dryad::thermal::IncoherentElasticAngularCdf;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IncoherentElasticAngularCdf",
    "Incoherent elastic thermal scattering angular distribution cdf\n\n"
    "Parameters\n"
    "----------\n"
    "    incident : float\n"
    "        the incident energy\n"
    "    debye_waller_integral : float\n"
    "        the Debye-Waller integral value"
  );

  // wrap the component
  component
  .def(

    python::init< double, double >(),
    python::arg( "incident" ), python::arg( "debye_waller_integral" ),
    "Initialise the incoherent elastic scattering angular distribution cdf"
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
  .def(

    "__call__",
    [] ( const Component& self, double energy ) -> decltype(auto)
       { return self( energy ); },
    python::arg( "cosine" ),
    "Evaluate the angular distribution for a given cosine value\n\n"
    "Parameters\n"
    "----------\n"
    "    cosine : float\n"
    "        the cosine value"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    std::string( "Linearise the angular distribution\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    tolerance : float, default " + tolerance.str() + "\n"
                 "        the linearisation tolerance" ).c_str()
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
