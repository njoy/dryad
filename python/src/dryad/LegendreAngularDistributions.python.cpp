// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/LegendreAngularDistributions.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapLegendreAngularDistributions( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::LegendreAngularDistributions;
  using LegendreAngularDistribution = njoy::dryad::LegendreAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LegendreAngularDistributions",
    "Angular distribution data given using Legendre expansions\n\n"
    "Parameters\n"
    "----------\n"
    "    grid : list of float\n"
    "        the grid values\n"
    "    distributions : list of njoy.dryad.LegendreAngularDistribution\n"
    "        the angular distributions\n"
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

    python::init< std::vector< double >,
                  std::vector< LegendreAngularDistribution >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType >,
                  bool >(),
    python::arg( "grid" ), python::arg( "distributions" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "normalise" ) = false,
    "Initialise the angular distributions with multiple interpolation zones"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< LegendreAngularDistribution >,
                  InterpolationType, bool >(),
    python::arg( "grid" ), python::arg( "distributions" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    python::arg( "normalise" ) = false,
    "Initialise the angular distributions with a single interpolation zone"
  )
  .def_property_readonly(

    "grid",
    [] ( const Component& self ) -> decltype(auto)
       { return self.grid(); },
    "The grid values for which distributions are given"
  )
  .def_property_readonly(

    "distributions",
    [] ( const Component& self ) -> decltype(auto)
       { return self.distributions(); },
    "The associated distributions"
  )
  .def(

    "__call__",
    [] ( const Component& self, double value, double cosine ) -> decltype(auto)
       { return self( value, cosine ); },
    python::arg( "value" ), python::arg( "cosine" ),
    "Evaluate the angular distribution for a given grid and cosine value\n\n"
    "Parameters\n"
    "----------\n"
    "    value : float\n"
    "        the grid value\n"
    "    cosine : float\n"
    "        the cosine value"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distributions"
  )
  .def_property_readonly(

    "average_cosines",
    &Component::averageCosines,
    "The average cosine values"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    python::arg( "normalise" ) = false,
    "Linearise the distributions\n\n"
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

  // add standard tabulated data definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
