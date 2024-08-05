// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/LegendreAngularDistributions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapLegendreAngularDistributions( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::LegendreAngularDistributions;
  using LegendreAngularDistribution = njoy::dryad::LegendreAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "LegendreAngularDistributions",
    "Angular distribution data given using Legendre expansions"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< LegendreAngularDistribution >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "grid" ), python::arg( "distributions" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the angular distributions\n\n"
    "Arguments:\n"
    "    self            the angular distribution table\n"
    "    grid            the grid values\n"
    "    distributions   the distributions\n"
    "    boundaries      the boundaries of the interpolation regions\n"
    "    interpolants    the interpolation types of the interpolation regions,\n"
    "                    see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >,
                  std::vector< LegendreAngularDistribution >,
                  InterpolationType >(),
    python::arg( "grid" ), python::arg( "distributions" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the angular distributions\n\n"
    "Arguments:\n"
    "    self            the multiplicity table\n"
    "    grid            the grid values\n"
    "    distributions   the distributions\n"
    "    interpolant     the interpolation type (default lin-lin),\n"
    "                    see InterpolationType for all interpolation types"
  )
  .def_property_readonly(

    "grid",
    &Component::grid,
    "The grid values for which distributions are given"
  )
  .def_property_readonly(

    "distributions",
    &Component::distributions,
    "The associated distributions"
  )
  .def(

    "__call__",
    [] ( const Component& self, double value, double cosine ) -> decltype(auto)
       { return self( value, cosine ); },
    python::arg( "value" ), python::arg( "cosine" ),
    "Evaluate the angular distributions\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    value     the grid value\n"
    "    cosine    the cosine value"
  );

  // add standard tabulated data definitions
  addStandardInterpolationTableDefinitions< Component >( component );
}
