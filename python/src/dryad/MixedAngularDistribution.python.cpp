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
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "MixedAngularDistribution",
    "An angular distribution defined by a pdf that is an isotropic, legendre or\n"
    "tabulated distribution function\n\n"
    "Parameters\n"
    "----------\n"
    "    pdf : Union[njoy.dryad.IsotropicAngularDistributionFunction,\n"
    "                njoy.dryad.LegendreAngularDistributionFunction,\n"
    "                njoy.dryad.TabulatedAngularDistributionFunction]\n"
    "        the distribution function\n"
    "    value : float\n"
    "        the value of the distribution (0.5 for a normalised distribution)\n"
    "    coefficients : list of float\n"
    "        the coefficients of the Legendre series (from\n"
    "        lowest to highest order coefficient)\n"
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

    python::init< std::variant< IsotropicAngularDistributionFunction,
                                LegendreAngularDistributionFunction,
                                TabulatedAngularDistributionFunction >,
                  bool >(),
    python::arg( "pdf" ),
    python::arg( "normalise" ) = false,
    "Initialise the angular distribution"
  )
  .def(

    python::init< double, bool >(),
    python::arg( "value" ),
    python::arg( "normalise" ) = false,
    "Initialise the angular distribution as isotropic"
  )
  .def(

    python::init< std::vector< double >, bool >(),
    python::arg( "coefficients" ),
    python::arg( "normalise" ) = false,
    "Initialise the angular distribution with Legendre coefficients"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType >,
                  bool >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "normalise" ) = false,
    "Initialise the angular distribution with tabulated data with multiple\n"
    "interpolation zones"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType, bool >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "normalise" ) = false,
    "Initialise the angular distribution with tabulated data with a single\n"
    "interpolation zone"
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
