// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/TabulatedAngularDistributions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedAngularDistributions( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedAngularDistributions;
  using TabulatedAngularDistribution = njoy::dryad::TabulatedAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedAngularDistributions",
    "Angular distribution data given as tables"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >,
                  std::vector< TabulatedAngularDistribution >,
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
                  std::vector< TabulatedAngularDistribution >,
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
    "Evaluate the angular distributions\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    value     the grid value\n"
    "    cosine    the cosine value"
  )
  .def_property_readonly(

    "average_cosines",
    &Component::averageCosines,
    "The average cosine values"
  )
  .def(

    "linearise",
    &Component::linearise,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the distribution\n\n"
    "Arguments:\n"
    "    self        the angular distributions\n"
    "    tolerance   the linearisation tolerance"
  );

  // add standard tabulated data definitions
  addStandardInterpolationTableDefinitions< Component >( component );
}
