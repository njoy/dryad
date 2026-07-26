// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/ThermalScattering.hpp"
#include "njoy/format/endf/read/createThermalScatteringFromFile.hpp"
#include "njoy/format/endf/write/createThermalScatteringFile.hpp"
#include "njoy/format/gnds/read/createThermalScatteringFromFile.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapThermalScattering( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ThermalScattering;
  using Documentation = njoy::dryad::Documentation;
  using CoherentElasticScattering = njoy::dryad::thermal::CoherentElasticScattering;
  using IncoherentElasticScattering = njoy::dryad::thermal::IncoherentElasticScattering;
  using IncoherentInelasticScattering = njoy::dryad::thermal::IncoherentInelasticScattering;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ThermalScattering",
    "Thermal scattering data\n\n"
    "Parameters\n"
    "----------\n"
    "    documentation : njoy.dryad.Documentation\n"
    "        the documentation associated to the thermal scattering data\n"
    "    coherent_elastic : njoy.dryad.thermal.CoherentElasticScattering\n"
    "        coherent elastic scattering data (default: none)\n"
    "    incoherent_elastic : njoy.dryad.thermal.IncoherentElasticScattering\n"
    "        incoherent elastic scattering data (default: none)\n"
    "    incoherent_inelastic : njoy.dryad.thermal.IncoherentInelasticScattering\n"
    "        incoherent inelastic scattering data (default: none)"
  );

  // wrap the component
  component
  .def(

    python::init< Documentation,
                  std::optional< CoherentElasticScattering >,
                  std::optional< IncoherentElasticScattering >,
                  std::optional< IncoherentInelasticScattering > >(),
    python::arg( "documentation" ),
    python::arg( "coherent_elastic" ) = std::nullopt,
    python::arg( "incoherent_elastic" ) = std::nullopt,
    python::arg( "incoherent_inelastic" ) = std::nullopt,
    "Initialise the thermal scattering data with documentation"
  )
  .def(

    python::init< std::optional< CoherentElasticScattering >,
                  std::optional< IncoherentElasticScattering >,
                  std::optional< IncoherentInelasticScattering > >(),
    python::arg( "coherent_elastic" ) = std::nullopt,
    python::arg( "incoherent_elastic" ) = std::nullopt,
    python::arg( "incoherent_inelastic" ) = std::nullopt,
    "Initialise the thermal scattering data without documentation"
  )
  .def_property(

    "documentation",
    python::overload_cast<>( &Component::documentation, python::const_ ),
    python::overload_cast< Documentation >( &Component::documentation ),
    "The documentation"
  )
  .def_property(

    "coherent_elastic_scattering",
    python::overload_cast<>( &Component::coherentElasticScattering, python::const_ ),
    python::overload_cast< std::optional< CoherentElasticScattering > >( &Component::coherentElasticScattering ),
    "The coherent elastic data"
  )
  .def_property(

    "incoherent_elastic_scattering",
    python::overload_cast<>( &Component::incoherentElasticScattering, python::const_ ),
    python::overload_cast< std::optional< IncoherentElasticScattering > >( &Component::incoherentElasticScattering ),
    "The incoherent elastic data"
  )
  .def_property(

    "incoherent_inelastic_scattering",
    python::overload_cast<>( &Component::incoherentInelasticScattering, python::const_ ),
    python::overload_cast< std::optional< IncoherentInelasticScattering > >( &Component::incoherentInelasticScattering ),
    "The incoherent inelastic data"
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

    "has_incoherent_inelastic_scattering",
    &Component::hasIncoherentInelasticScattering,
    "Return whether or not there is incoherent inelastic scattering"
  )
  .def_property_readonly(

    "has_inelastic_scattering",
    &Component::hasInelasticScattering,
    "Return whether or not there is inelastic scattering"
  )
  .def_static(

    "from_endf_file",
    [] ( const std::string& filename, const std::optional< double >& upper ) -> decltype(auto) {

      return njoy::format::endf::read::createThermalScatteringFromFile( filename, upper );
    },
    python::arg( "filename" ),
    python::arg( "upper" ) = std::nullopt,
    "Create ThermalScattering data from an ENDF file\n\n"
    "If there are multiple materials in the ENDF file, only the first material\n"
    "will be transformed into a ThermalScattering instance.\n\n"
    "Parameters\n"
    "----------\n"
    "    filename : string\n"
    "        the ENDF file name\n"
    "    upper : float, default None\n"
    "        the upper energy limit, the upper energy limit of the evaluation is used\n"
    "        if no value is defined"
  )
  .def_static(

    "from_gnds_file",
    [] ( double lower, double upper, const std::string& filename, const std::string& style ) -> decltype(auto) {

      return njoy::format::gnds::read::createThermalScatteringFromFile( lower, upper, filename, style );
    },
    python::arg( "lower" ), python::arg( "upper" ),
    python::arg( "filename" ), python::arg( "style" ) = "eval",
    "Create ThermalScattering data from a GNDS file\n\n"
    "Parameters\n"
    "----------\n"
    "    lower : float\n"
    "        the lower energy limit\n"
    "    upper : float\n"
    "        the upper energy limit\n"
    "    filename : string\n"
    "        the GNDS file name\n"
    "    style : string\n"
    "        the GNDS style to process (default is eval)"
  )
  .def(

    "to_endf_file",
    [] ( const Component& self, int za, int mat, const std::string& filename ) {

      njoy::format::endf::write::createThermalScatteringFile( self, za, mat, filename );
    },
    python::arg( "za" ), python::arg( "mat" ), python::arg( "filename" ),
    "Write the ThermalScattering data to an ENDF file\n\n"
    "Parameters\n"
    "----------\n"
    "    za : int\n"
    "        the ENDF za number to be used\n"
    "    mat : int\n"
    "        the ENDF mat number to be used\n"
    "    filename : string\n"
    "        the ENDF file name\n"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
