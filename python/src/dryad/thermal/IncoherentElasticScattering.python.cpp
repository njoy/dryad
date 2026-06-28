// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/IncoherentElasticScattering.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapIncoherentElasticScattering( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::IncoherentElasticScattering;
  using DebyeWallerIntegralData = njoy::dryad::thermal::DebyeWallerIntegralData;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IncoherentElasticScattering",
    "Incoherent elastic thermal scattering data\n\n"
    "Parameters\n"
    "----------\n"
    "    lower : float\n"
    "        the lower energy limit\n"
    "    upper : float\n"
    "        the upper energy limit\n"
    "    xs : float\n"
    "        the bound atom cross section\n"
    "    debye_waller_integral : njoy.dryad.thermal.DebyeWallerIntegralData\n"
    "        the Debye-Waller integral data"
  );

  // wrap the component
  component
  .def(

    python::init< double, double, double,
                  DebyeWallerIntegralData >(),
    python::arg( "lower" ), python::arg( "upper" ),
    python::arg( "xs" ), python::arg( "debye_waller_integral" ),
    "Initialise the incoherent elastic scattering data"
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

    "number_moderator_temperatures",
    &Component::numberModeratorTemperatures,
    "The moderator temperature values"
  )
  .def_property_readonly(

    "moderator_temperatures",
    python::overload_cast<>( &Component::moderatorTemperatures, python::const_ ),
    "The moderator temperature values"
  )
  .def_property(

    "bound_cross_section",
    python::overload_cast<>( &Component::boundCrossSection, python::const_ ),
    python::overload_cast< double >( &Component::boundCrossSection ),
    "The bound atom cross section value"
  )
  .def_property(

    "debye_waller_integral",
    python::overload_cast<>( &Component::debyeWallerIntegral, python::const_ ),
    python::overload_cast< DebyeWallerIntegralData >( &Component::debyeWallerIntegral ),
    "The Debye-Waller integral data"
  )
  .def(

    "cross_section",
    &Component::crossSection,
    python::arg( "temperature" ),
    "Return the incoherent elastic scattering cross section\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the moderator temeprature for which the cross section is requested\n"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
