// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/BraggEdgeData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapBraggEdgeData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::BraggEdgeData;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "BraggEdgeData",
    "Bragg edge data for a single temperature\n\n"
    "The Bragg edge data consists of edge energies and structure\n"
    "factor values.\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "         the temperature\n"
    "    energies : list of float\n"
    "         the temperature\n"
    "    values : list of float\n"
    "         the structure factor values"
  );

  // wrap the component
  component
  .def(

    python::init< double,
                  std::vector< double >,
                  std::vector< double > >(),
    python::arg( "temperature" ),
    python::arg( "energies" ),
    python::arg( "values" ),
    "Initialise the Bragg edge data"
  )
  .def_property_readonly(

    "temperature",
    &Component::temperature,
    "The temperature of the Bragg edge data"
  )
  .def_property_readonly(

    "number_bragg_edges",
    &Component::numberBraggEdges,
    "The number of Bragg edges"
  )
  .def_property_readonly(

    "energies",
    python::overload_cast<>( &Component::energies, python::const_ ),
    "The energies of the Bragg edges"
  )
  .def_property_readonly(

    "values",
    python::overload_cast<>( &Component::values, python::const_ ),
    "The structure factor values"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
