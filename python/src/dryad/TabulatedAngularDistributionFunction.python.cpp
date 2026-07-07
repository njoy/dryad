// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/TabulatedAngularDistributionFunction.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedAngularDistributionFunction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedAngularDistributionFunction;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedAngularDistributionFunction",
    "An angular distribution function using tabulated data\n\n"
    "Parameters\n"
    "----------\n"
    "    cosines : list of float\n"
    "        the cosine values\n"
    "    values : list of float\n"
    "        the probability values\n"
    "    boundaries : list of int\n"
    "        the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "        the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "        the interpolation type (default lin-lin)\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the angular distribution function with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the angular distribution function with a single interpolation zone"
  )
  .def_property_readonly(

    "cosines",
    &Component::cosines,
    "The cosine values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The probability values"
  )
  .def_property_readonly(

    "lower_cosine_limit",
    &Component::lowerCosineLimit,
    "The lower cosine limit"
  )
  .def_property_readonly(

    "upper_cosine_limit",
    &Component::upperCosineLimit,
    "The upper cosine limit"
  )
  .def(

    "__call__",
    [] ( const Component& self, double cosine ) -> decltype(auto)
       { return self( cosine ); },
    python::arg( "cosine" ),
    "Evaluate the distribution for a given cosine value\n\n"
    "Parameters\n"
    "----------\n"
    "    cosine : float\n"
    "        the cosine value"
  )
  .def_property_readonly(

    "integral",
    [] ( const Component& self ) { return self.integral(); },
    "The integral of the distribution function over its domain"
  )
  .def_property_readonly(

    "mean",
    [] ( const Component& self ) { return self.mean(); },
    "The mean value of the distribution function over its domain"
  )
  .def_property_readonly(

    "cumulative_integral",
    [] ( const Component& self ) { return self.cumulativeIntegral(); },
    "The cumulative integral of the distribution function over its domain"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution function"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
