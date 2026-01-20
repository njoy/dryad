// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/thermal/TabulatedDebyeWallerIntegral.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace thermal {

void wrapTabulatedDebyeWallerIntegral( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::thermal::TabulatedDebyeWallerIntegral;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedDebyeWallerIntegral",
    "A Debye-Waller integral table\n\n"
    "Parameters\n"
    "----------\n"
    "    temperatures : list of float\n"
    "         the temperature values\n"
    "    values : list of float\n"
    "         the intergal values\n"
    "    boundaries : list of int\n"
    "         the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "         the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "         the interpolation type (default lin-lin)\n"
    "    normalise : bool, default false\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "temperatures" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the Debye-Waller integral table with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "temperatures" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the Debye-Waller integral table with a single interpolation zone"
  )
  .def_property_readonly(

    "temperatures",
    &Component::temperatures,
    "The temperature values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The form factor values"
  )
  .def_property_readonly(

    "lower_temperature_limit",
    &Component::lowerTemperatureLimit,
    "The lower temperature limit"
  )
  .def_property_readonly(

    "upper_temperature_limit",
    &Component::upperTemperatureLimit,
    "The upper temperature limit"
  )
  .def(

    "__call__",
    [] ( const Component& self, double temperature ) -> decltype(auto)
       { return self( temperature ); },
    python::arg( "temperature" ),
    "Evaluate the integral for a given temperature value\n\n"
    "Parameters\n"
    "----------\n"
    "    temperature : float\n"
    "        the temperature value"
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
