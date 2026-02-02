// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/FrohnerBackground.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapFrohnerBackground( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::FrohnerBackground;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "FrohnerBackground",
    "A channel background using the Frohner parametrisation"
   );

  // wrap the component
  component
  .def(

    python::init< double, double, double,
                  double, double >(),
    python::arg( "distant_level_parameter" ),
    python::arg( "pole_strength" ),
    python::arg( "average_radiation_width" ),
    python::arg( "lower_singularity" ),
    python::arg( "upper_singularity" ),
    "Initialise the background function\n\n"
    "Parameters\n"
    "----------\n"
    "    distant_level_parameter : float\n"
    "       the distant level parameter\n"
    "    pole_strength : list of float\n"
    "       the pole strength\n"
    "    average_radiation_width : float\n"
    "       the average radiation width\n"
    "    lower_singularity : float\n"
    "       the lower logarithmic singularity values\n"
    "    upper_singularity : float\n"
    "       the upper logarithmic singularity values\n"
  )
  .def_property_readonly(

    "distant_level_parameter",
    &Component::distantLevelParameter,
    "The distant level parameter"
  )
  .def_property_readonly(

    "pole_strength",
    &Component::poleStrength,
    "The pole strength"
  )
  .def_property_readonly(

    "average_radiation_width",
    &Component::averageRadiationWidth,
    "The average radiation width"
  )
  .def_property_readonly(

    "lower_singularity",
    &Component::lowerSingularity,
    "The logarithmic singularity below the energy range"
  )
  .def_property_readonly(

    "upper_singularity",
    &Component::upperSingularity,
    "The logarithmic singularity above the energy range"
  )
  .def(

    "__call__",
    [] ( const Component& self, double energy ) -> decltype(auto)
       { return self( energy ); },
    python::arg( "energy" ),
    "Evaluate the background function for a given energy value\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
