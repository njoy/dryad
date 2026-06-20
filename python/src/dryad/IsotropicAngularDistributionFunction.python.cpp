// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/IsotropicAngularDistributionFunction.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapIsotropicAngularDistributionFunction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::IsotropicAngularDistributionFunction;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "IsotropicAngularDistributionFunction",
    "An isotropic angular distribution function\n\n"
    "In this distribution, all cosines are equally probable. The equivalent\n"
    "tabulated distribution is 0.5 on the [-1, 1] domain and the equivalent\n"
    "Legendre distribution uses 0.5 as the P0 coefficient."
   );

  // wrap the component
  component
  .def(

    python::init<>(),
    "Initialise the isotropic angular distribution"
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
    "Evaluate the distribution for a given cosine value\n\n"
    "Parameters\n"
    "----------\n"
    "    cosine : float\n"
    "        the cosine value"
  )
  .def_property_readonly(

    "integral",
    &Component::integral,
    "The integral of the distribution function over its domain"
  )
  .def_property_readonly(

    "mean",
    &Component::mean,
    "The mean value of the distribution function over its domain"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution function"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    python::arg( "normalise" ) = false,
    "Linearise the distribution function\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 0.001\n"
    "         the linearisation tolerance\n"
    "    normalise : bool, default False\n"
    "         option to indicate whether or not to normalise\n"
    "         all probability data (default: no normalisation)"
  )
  .def(

    "to_legendre_distribution",
    &Component::toLegendreDistribution,
    "Convert to the equivalent Legendre distribution"
  )
  .def(

    "to_tabulated_distribution",
    &Component::toTabulatedDistribution,
    "Convert to the equivalent tabulated distribution"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
