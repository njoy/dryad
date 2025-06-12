// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/LegendreAngularDistributionFunction.hpp"

// namespace aliases
namespace python = pybind11;

void wrapLegendreAngularDistributionFunction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::LegendreAngularDistributionFunction;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LegendreAngularDistributionFunction",
    "An angular distribution function using a Legendre expansion defined by a\n"
    "set of coefficients\n\n"
    "Note: ENDF and GNDS Legendre expansions use Legendre moments for the angular\n"
    "distributions in MF4 and MF6 LAW=1 & LAW=2 so an additional ( 2 * n + 1 ) / 2\n"
    "factor for the coefficient of order n needs to be applied to obtain the series\n"
    "coefficients. This distribution function assumes those factors are already\n"
    "integrated in the coefficients.\n\n"
    "A distribution function does not have to normalised as this class can be used\n"
    "to represent both a pdf and cdf. Proper normalisation should be applied after\n"
    "construction using the normalise() function if required."
   );

  // wrap the component
  component
  .def(

    python::init< std::vector< double > >(),
    python::arg( "coefficients" ),
    "Initialise the angular distribution\n\n"
    "Arguments:\n"
    "    self           the angular distribution\n"
    "    coefficients   the coefficients of the Legendre series (from\n"
    "                   lowest to highest order coefficient)"
  )
  .def_property_readonly(

    "lower_cosine_limit",
    [] ( const Component& self ) -> decltype(auto)
       { return self.lowerCosineLimit(); },
    "The lower cosine limit"
  )
  .def_property_readonly(

    "upper_cosine_limit",
    [] ( const Component& self ) -> decltype(auto)
       { return self.upperCosineLimit(); },
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
  )
  .def_property_readonly(

    "integral",
    [] ( const Component& self ) { return self.integral(); },
    "The integral (zeroth order moment) of the distribution function over its domain"
  )
  .def_property_readonly(

    "mean",
    [] ( const Component& self ) { return self.mean(); },
    "The mean (first order raw moment) of the distribution function over its domain"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardSeriesDefinitions< Component >( component );
}
