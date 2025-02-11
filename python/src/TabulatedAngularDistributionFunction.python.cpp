// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/TabulatedAngularDistributionFunction.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedAngularDistributionFunction( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::TabulatedAngularDistributionFunction;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedAngularDistributionFunction",
    "An angular distribution function using tabulated data"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the angular distribution function\n\n"
    "Arguments:\n"
    "    self           the angular distribution function\n"
    "    cosines        the cosine values\n"
    "    values         the probability values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions,\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the angular distribution function\n\n"
    "Arguments:\n"
    "    self           the angular distribution function\n"
    "    cosines        the cosine values\n"
    "    values         the probability values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types"
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
    "Evaluate the table for a given cosine value\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    cosine    the cosine value"
  );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );
}
