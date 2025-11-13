// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/TabulatedWaveFunction.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapTabulatedWaveFunction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::TabulatedWaveFunction;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedWaveFunction",
    "A tabulated function representing penetrability, shift or phase shift"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "ratios" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the wave function table\n\n"
    "Arguments:\n"
    "    self           the wave function table\n"
    "    ratios.        the ratio values\n"
    "    values         the wave function values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions,\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< double >,
                  InterpolationType >(),
    python::arg( "ratios" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the radius table\n\n"
    "Arguments:\n"
    "    self           the radius table\n"
    "    ratios         the ratio values\n"
    "    values         the wave function values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "ratios",
    &Component::ratios,
    "The ratio values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The wave function values"
  )
  .def_property_readonly(

    "lower_ratio_limit",
    &Component::lowerRatioLimit,
    "The lower ratio limit"
  )
  .def_property_readonly(

    "upper_ratio_limit",
    &Component::upperRatioLimit,
    "The upper ratio limit"
  )
  .def(

    "__call__",
    [] ( const Component& self, double ratio ) -> decltype(auto)
       { return self( ratio ); },
    python::arg( "ratio" ),
    "Evaluate the table for a given ratio value\n\n"
    "Arguments:\n"
    "    self    the table\n"
    "    ratio   the ratio value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
