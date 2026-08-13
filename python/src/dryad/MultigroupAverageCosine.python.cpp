// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/MultigroupAverageCosine.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapMultigroupAverageCosine( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::MultigroupAverageCosine;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "MultigroupAverageCosine",
    "A multigroup average cosine table\n\n"
    "Parameters\n"
    "----------\n"
    "    boundaries : list of float\n"
    "        the energy boundaries\n"
    "    values : list of float\n"
    "        the average cosine values"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double > >(),
    python::arg( "boundaries" ), python::arg( "values" ),
    "Initialise the multigroup average cosine table"
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
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard arithmetic definitions
  addStandardMultigroupDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
