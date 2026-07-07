// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/CoherentElasticScattering.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapCoherentElasticScattering( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::CoherentElasticScattering;
  using BraggEdgeData = njoy::dryad::thermal::BraggEdgeData;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CoherentElasticScattering",
    "Coherent elastic thermal scattering data\n\n"
    "Parameters\n"
    "----------\n"
    "    lower : float\n"
    "        the lower energy limit\n"
    "    upper : float\n"
    "        the upper energy limit\n"
    "    bragg_edges : list of njoy.dryad.thermal.BraggEdgeData\n"
    "        the Bragg edge data"
  );

  // wrap the component
  component
  .def(

    python::init< double, double, std::vector< BraggEdgeData > >(),
    python::arg( "lower" ), python::arg( "upper" ), python::arg( "bragg_edges" ),
    "Initialise the coherent elastic scattering data"
  )
  .def_property(

    "lower_energy_limit",
    python::overload_cast<>( &Component::lowerEnergyLimit, python::const_ ),
    python::overload_cast< double >( &Component::lowerEnergyLimit ),
    "The lower energy limit"
  )
  .def_property(

    "upper_energy_limit",
    python::overload_cast<>( &Component::upperEnergyLimit, python::const_ ),
    python::overload_cast< double >( &Component::upperEnergyLimit ),
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

    "bragg_edges",
    python::overload_cast<>( &Component::braggEdges, python::const_ ),
    python::overload_cast< std::vector< BraggEdgeData > >( &Component::braggEdges ),
    "The Bragg edge data"
  )
  .def(

    "has_bragg_edge_data",
    &Component::hasBraggEdgeData,
    python::arg( "temperature" ),
    "Return whether or not there is Bragg edge data for a given temperature\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the moderator temperature"
  )
  .def(

    "bragg_edge_data",
    &Component::braggEdgeData,
    python::arg( "temperature" ),
    "Return the Bragg edge data for a given temperature\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the moderator temperature",
    python::return_value_policy::reference_internal
  )
  .def(

    "cross_section",
    &Component::crossSection,
    python::arg( "temperature" ),
    "Return the incoherent elastic scattering cross section for a given temperature\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the moderator temperature for which the cross section is requested"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
