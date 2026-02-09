// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/InelasticScattering.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapInelasticScattering( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::InelasticScattering;
  using TabulatedScatteringFunctions = njoy::dryad::thermal::TabulatedScatteringFunctions;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "InelasticScattering",
    "Inelastic thermal scattering data\n\n"
    "Parameters\n"
    "----------\n"
    "    xs : float\n"
    "         the bound atom cross section\n"
    "    self_scatter : njoy.dryad.thermal.TabulatedScatteringFunctions\n"
    "         the self-scattering S(a,b) function"
  );

  // wrap the component
  component
  .def(

    python::init< double,
                  TabulatedScatteringFunctions >(),
    python::arg( "xs" ), python::arg( "self_scatter" ),
    "Initialise the inelastic scattering data"
  )
  .def_property(

    "bound_cross_section",
    python::overload_cast<>( &Component::boundCrossSection, python::const_ ),
    python::overload_cast< double >( &Component::boundCrossSection ),
    "The bound atom cross section value"
  )
  .def_property(

    "self_scattering_function",
    python::overload_cast<>( &Component::selfScatteringFunction, python::const_ ),
    python::overload_cast< TabulatedScatteringFunctions >( &Component::selfScatteringFunction ),
    "The self-scattering S(a,b) function"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
