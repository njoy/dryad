// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/TabulatedAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedAngularDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedAngularDistribution",
    "An angular distribution defined by a pdf and cdf using tabulated data\n\n"
    "Parameters\n"
    "----------\n"
    "    cosines : list of float\n"
    "         the cosine values\n"
    "    values : list of float\n"
    "         the probability values\n"
    "    boundaries : list of int\n"
    "         the boundaries of the interpolation regions\n"
    "    interpolants : list of njoy.dryad.InterpolationType\n"
    "         the interpolation types of the interpolation regions\n"
    "    interpolant : njoy.dryad.InterpolationType, default njoy.dryad.InterpolationType.LinearLinear\n"
    "         the interpolation type (default lin-lin)\n"
    "    normalise : bool, default false\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType >,
                  bool >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "normalise" ) = false,
    "Initialise the angular distribution with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType, bool >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "normalise" ) = false,
    "Initialise the angular distribution with a single interpolation zone"
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

    "boundaries",
    &Component::boundaries,
    "The boundaries of the interpolation regions"
  )
  .def_property_readonly(

    "interpolants",
    &Component::interpolants,
    "The interpolation types of the interpolation regions"
  )
  .def_property_readonly(

    "pdf",
    &Component::pdf,
    "The probability distribution function (pdf) of the distribution"
  )
  .def_property_readonly(

    "cdf",
    &Component::cdf,
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
    "    tolerance : njoy.dryad.ToleranceConvergence\n"
    "         the linearisation tolerance\n"
    "    normalise : bool, default false\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data (default: no normalisation)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
