// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/TabulatedComptonProfileFunction.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedComptonProfileFunction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedComptonProfileFunction;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedComptonProfileFunction",
    "A Compton profile distribution using tabulated data\n\n"
    "Parameters \n"
    "---------- \n"
    "    momentum : list of float \n"
    "         the momentum values \n"
    "    values : list of float \n"
    "         the probability values \n"
    "    boundaries : list of int \n"
    "         the boundaries of the interpolation regions \n"
    "    interpolants : list of njoy.dryad.InterpolationType \n"
    "         the interpolation types of the interpolation regions \n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear \n"
    "         the interpolation type (default lin-lin) \n"
    "    normalise : bool, default false \n"
    "        option to indicate whether or not to normalise \n"
    "        all probability data (default: no normalisation)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "momentum" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the compton profile function with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< double >,
                  InterpolationType >(),
    python::arg( "momentum" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the compton profile function with a single interpolation zone"
  )
  .def_property_readonly(

    "momentum",
    &Component::momentum,
    "The momentum values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The probability values"
  )
  .def_property_readonly(

    "lower_momentum_limit",
    &Component::lowerMomentumLimit,
    "The lower momentum limit"
  )
  .def_property_readonly(

    "upper_momentum_limit",
    &Component::upperMomentumLimit,
    "The upper momentum limit"
  )
  .def(

    "__call__",
    [] ( const Component& self, double momentum ) -> decltype(auto)
       { return self( momentum ); },
    python::arg( "momentum" ),
    "Evaluate the table for a given momentum value\n\n"
    "Parameters \n"
    "---------- \n"
    "    momentum : float \n"
    "        the momentum value"
  )
  .def_property_readonly(

    "integral",
    [] ( const Component& self ) { return self.integral(); },
    "The integral (zeroth order moment) of the Compton profile function over its domain"
  )
  .def_property_readonly(

    "cumulative_integral",
    [] ( const Component& self ) { return self.cumulativeIntegral(); },
    "The cumulative integral of the Compton profile function over its domain"
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
