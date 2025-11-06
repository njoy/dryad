// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/id/EnergyGroup.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace id {

void wrapEnergyGroup( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::EnergyGroup;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "EnergyGroup",
    "An energy group defined by two energy values"
  );

  // wrap the component
  component
  .def(

    python::init< double, double >(),
    python::arg( "lower" ), python::arg( "upper" ),
    "Initialise the energy\n\n"
    "Arguments:\n"
    "    self    the identifier\n"
    "    lower   the lower energy value of the group\n"
    "    upper   the upper energy value of the group"
  )
  .def_property_readonly(

    "lower_energy",
    &Component::lowerEnergy,
    "The lower energy value"
  )
  .def_property_readonly(

    "upper_energy",
    &Component::upperEnergy,
    "The upper energy value"
  )
  .def(

    "__hash__",
    [] ( const Component& self ) { return std::hash< Component >()( self ); },
    "Hash function"
  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // namespace id
} // dryad namespace
