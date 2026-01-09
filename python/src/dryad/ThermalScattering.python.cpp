// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/ThermalScattering.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapThermalScattering( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ThermalScattering;
  using Documentation = njoy::dryad::Documentation;
  using IncoherentElasticScattering = njoy::dryad::thermal::IncoherentElasticScattering;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ThermalScattering",
    "Thermal scattering data\n\n"
    "Parameters\n"
    "----------\n"
    "    cosines : njoy.dryad.Documentation\n"
    "         the documentation associated to the thermal sacttering data\n"
    "    incoherent : njoy.dryad.thermal.IncoherentElasticScattering\n"
    "         incoherent elastic scattering data (default: none)"
  );

  // wrap the component
  component
  .def(

    python::init< Documentation,
                  std::optional< IncoherentElasticScattering > >(),
    python::arg( "documentation" ),
    python::arg( "incoherent" ) = std::nullopt,
    "Initialise the thermal scattering data with documentation"
  )
  .def(

    python::init< std::optional< IncoherentElasticScattering > >(),
    python::arg( "incoherent" ) = std::nullopt,
    "Initialise the thermal scattering data without documentation"
  )
  .def_property(

    "documentation",
    python::overload_cast<>( &Component::documentation, python::const_ ),
    python::overload_cast< Documentation >( &Component::documentation ),
    "The documentation"
  )
  .def_property(

    "incoherent_elastic_scattering",
    python::overload_cast<>( &Component::incoherentElasticScattering, python::const_ ),
    python::overload_cast< std::optional< IncoherentElasticScattering > >( &Component::incoherentElasticScattering ),
    "The incoherent elastic data"
  )
  .def_property_readonly(

    "has_coherent_elastic_scattering",
    &Component::hasCoherentElasticScattering,
    "Return whether or not there is coherent elastic scattering"
  )
  .def_property_readonly(

    "has_incoherent_elastic_scattering",
    &Component::hasIncoherentElasticScattering,
    "Return whether or not there is incoherent elastic scattering"
  )
  .def_property_readonly(

    "has_elastic_scattering",
    &Component::hasElasticScattering,
    "Return whether or not there is elastic scattering (coherent and/or incoherent)"
  )
  .def_property_readonly(

    "has_inelastic_scattering",
    &Component::hasInelasticScattering,
    "Return whether or not there is inelastic scattering"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
