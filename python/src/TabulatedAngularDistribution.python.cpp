// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/TabulatedAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedAngularDistribution( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::TabulatedAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedAngularDistribution",
    "An angular distribution table"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the angular distribution table\n\n"
    "Arguments:\n"
    "    self           the angular distribution table\n"
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
    "Initialise the multiplicity table\n\n"
    "Arguments:\n"
    "    self           the multiplicity table\n"
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
  );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );
}
