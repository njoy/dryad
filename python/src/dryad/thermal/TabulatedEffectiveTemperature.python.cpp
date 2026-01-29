// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/TabulatedEffectiveTemperature.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapTabulatedEffectiveTemperature( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::TabulatedEffectiveTemperature;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedEffectiveTemperature",
    "An effective temperature table\n\n"
    "This is a table of effective temperatures (given in K) for the short collision-time\n"
    "approximation given as a function of moderator temperature (given in K) for a scattering\n"
    "atom.\n\n"
    "Parameters\n"
    "----------\n"
    "    moderator_temperatures : list of float\n"
    "         the moderator temperature values\n"
    "    values : list of float\n"
    "         the effective temperature values\n"
    "    boundaries : list of int\n"
    "         the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "         the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "         the interpolation type (default lin-lin)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "moderator_temperatures" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the effective temperature table with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "moderator_temperatures" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the effective temperature table with a single interpolation zone"
  )
  .def_property_readonly(

    "moderator_temperatures",
    &Component::moderatorTemperatures,
    "The moderator temperature values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The effective temperatur values"
  )
  .def_property_readonly(

    "lower_moderator_temperature_limit",
    &Component::lowerModeratorTemperatureLimit,
    "The lower moderator temperature limit"
  )
  .def_property_readonly(

    "upper_moderator_temperature_limit",
    &Component::upperModeratorTemperatureLimit,
    "The upper moderator temperature limit"
  )
  .def(

    "__call__",
    [] ( const Component& self, double temperature ) -> decltype(auto)
       { return self( temperature ); },
    python::arg( "moderator_temperature" ),
    "Evaluate the effective temperature for a given moderator temperature value\n\n"
    "Parameters\n"
    "----------\n"
    "    moderator_temperature : float\n"
    "        the moderator temperature value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // thermal namespace
} // dryad namespace
