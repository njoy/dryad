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
    "    xs : float\n"
    "         the bound atom cross section\n"
    "    debye_waller_integral : njoy.dryad.thermal.DebyeWallerIntegralData\n"
    "         the Debye-Waller integral data"
  );

  // wrap the component
  component
  .def(

    python::init< double,
                  DebyeWallerIntegralData >(),
    python::arg( "xs" ), python::arg( "debye_waller_integral" ),
    "Initialise the incoherent elastic scattering data"
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
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
