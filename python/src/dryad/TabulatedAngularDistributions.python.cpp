// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/TabulatedAngularDistributions.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapTabulatedAngularDistributions( python::module& module ) {

  // constants
  std::ostringstream tolerance;
  tolerance << std::setprecision( 4 ) << njoy::constants::linearisation::tolerance;

  // type aliases
  using Component = njoy::dryad::TabulatedAngularDistributions;
  using TabulatedAngularDistribution = njoy::dryad::TabulatedAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedAngularDistributions",
    "Angular distribution data given as tabulated data\n\n"
    "Parameters\n"
    "----------\n"
    "    grid : list of float\n"
    "        the grid values\n"
    "    distributions : list of njoy.dryad.TabulatedAngularDistribution\n"
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
                  std::vector< TabulatedAngularDistribution >,
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
                  std::vector< TabulatedAngularDistribution >,
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
    "Normalise the distributions\n\n"
    "Note: all distributions should have the same integral over their domain\n"
    "      to avoid changing the full distribution (ie the normalisation moves\n"
    "      every distribution up or down by the same amount to avoid changing\n"
    "      the full distribution shape)."
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
    std::string( "Linearise the distributions\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    tolerance : float, default " + tolerance.str() + "\n"
                 "        the linearisation tolerance\n"
                 "    normalise : bool, default False\n"
                 "        option to indicate whether or not to normalise\n"
                 "        all probability data (default: no normalisation)" ).c_str()
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardInterpolationTableDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
