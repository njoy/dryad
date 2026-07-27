// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/IncoherentElasticCrossSection.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapIncoherentElasticCrossSection( python::module& module ) {

  // constants
  std::ostringstream tolerance;
  tolerance << std::setprecision( 4 ) << njoy::constants::linearisation::tolerance;

  // type aliases
  using Component = njoy::dryad::thermal::IncoherentElasticCrossSection;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IncoherentElasticCrossSection",
    "Incoherent elastic thermal scattering cross section\n\n"
    "Parameters\n"
    "----------\n"
    "    lower : float\n"
    "        the lower energy limit\n"
    "    upper : float\n"
    "        the upper energy limit\n"
    "    xs : float\n"
    "        the bound atom cross section\n"
    "    debye_waller_integral : float\n"
    "        the Debye-Waller integral value"
  );

  // wrap the component
  component
  .def(

    python::init< double, double, double, double >(),
    python::arg( "lower" ), python::arg( "upper" ),
    python::arg( "xs" ), python::arg( "debye_waller_integral" ),
    "Initialise the incoherent elastic scattering cross section"
  )
  .def_property_readonly(

    "lower_energy_limit",
    &Component::lowerEnergyLimit,
    "The lower energy limit"
  )
  .def_property_readonly(

    "upper_energy_limit",
    &Component::upperEnergyLimit,
    "The upper energy limit"
  )
  .def_property_readonly(

    "bound_cross_section",
    python::overload_cast<>( &Component::boundCrossSection, python::const_ ),
    "The bound atom cross section value"
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
    "Evaluate the cross section for a given energy value\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy value"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    std::string( "Linearise the cross section\n\n"
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
