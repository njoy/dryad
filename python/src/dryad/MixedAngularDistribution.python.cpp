// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/MixedAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapMixedAngularDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::MixedAngularDistribution;
  using IsotropicAngularDistributionFunction = njoy::dryad::IsotropicAngularDistributionFunction;
  using LegendreAngularDistributionFunction = njoy::dryad::LegendreAngularDistributionFunction;
  using TabulatedAngularDistributionFunction = njoy::dryad::TabulatedAngularDistributionFunction;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "MixedAngularDistribution",
    "An angular distribution defined by a pdf that is an isotropic, legendre or\n"
    "tabulated distribution function\n\n"
    "Parameters\n"
    "----------\n"
    "    function : Union[njoy.dryad.IsotropicAngularDistributionFunction,\n"
    "               njoy.dryad.LegendreAngularDistributionFunction,\n"
    "               njoy.dryad.TabulatedAngularDistributionFunction]\n"
    "        the distribution function\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // wrap the component
  component
  .def(

    python::init< std::variant< IsotropicAngularDistributionFunction,
                                LegendreAngularDistributionFunction,
                                TabulatedAngularDistributionFunction >,
                  bool >(),
    python::arg( "function" ),
    python::arg( "normalise" ) = false,
    "Initialise the angular distribution"
  )
  .def_property_readonly(

    "pdf",
    python::overload_cast<>( &Component::pdf, python::const_ ),
    "The probability distribution function (pdf) of the distribution"
  )
  .def_property_readonly(

    "cdf",
    python::overload_cast<>( &Component::cdf, python::const_ ),
    "The cumulative distribution function (cdf) of the distribution"
  )
  .def(

    "__call__",
    [] ( const Component& self, double cosine ) -> decltype(auto)
       { return self( cosine ); },
    python::arg( "cosine" ),
    "Evaluate the pdf of the distribution for a given cosine value\n\n"
    "Parameters\n"
    "----------\n"
    "    cosine : float\n"
    "        the cosine value"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution"
  )
  .def_property_readonly(

    "average_cosine",
    &Component::averageCosine,
    "The average cosine defined by the distribution"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    python::arg( "normalise" ) = false,
    "Linearise the distribution\n\n"
    "Parameters\n"
    "----------\n"
    "    tolerance : float, default 0.001\n"
    "        the linearisation tolerance\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
