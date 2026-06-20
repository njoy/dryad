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

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedWaveFunction",
    "A tabulated function representing penetrability, shift or phase shift\n\n"
    "Parameters\n"
    "----------\n"
    "    ratios : list of float\n"
    "        the ratio values\n"
    "    values : list of float\n"
    "        the wave function values\n"
    "    boundaries : list of int, optional\n"
    "        the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType, optional\n"
    "        the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default=LinearLinear\n"
    "        the interpolation type for single-region tables"
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
    "Initialise the wave function table with multiple interpolation regions"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< double >,
                  InterpolationType >(),
    python::arg( "ratios" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the wave function table with a single interpolation region"
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
    "Parameters\n"
    "----------\n"
    "    ratio : float\n"
    "        the ratio value"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
