// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/TabulatedComptonProfile.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedComptonProfile( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedComptonProfile;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedComptonProfile",
    "A Compton profile using tabulated data"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "momentum" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the Compton profile\n\n"
    "Arguments:\n"
    "    self           the compton profile\n"
    "    momentum       the momentum values\n"
    "    values         the probability values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions,\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "momentum" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the Compton profile\n\n"
    "Arguments:\n"
    "    self           the Compton profile\n"
    "    momentum       the momentum values\n"
    "    values         the probability values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types"
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
    "Arguments:\n"
    "    self        the table\n"
    "    momentum    the momentum value"
  )
  .def_property_readonly(

    "integral",
    [] ( const Component& self ) { return self.integral(); },
    "The integral (zeroth order moment) of the Compton profile over its domain"
  )
  .def_property_readonly(

    "cumulative_integral",
    [] ( const Component& self ) { return self.cumulativeIntegral(); },
    "The cumulative integral of the Compton profile over its domain"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
