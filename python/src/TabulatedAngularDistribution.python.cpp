// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/TabulatedAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedAngularDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedAngularDistribution;
  using InterpolationType = njoy::dryad::InterpolationType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedAngularDistribution",
    "An angular distribution defined by a pdf and cdf using tabulated data"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the angular distribution\n\n"
    "Arguments:\n"
    "    self           the angular distribution\n"
    "    cosines        the cosine values\n"
    "    values         the probability values\n"
    "    boundaries     the boundaries of the interpolation regions\n"
    "    interpolants   the interpolation types of the interpolation regions,\n"
    "                   see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "cosines" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the angular distribution\n\n"
    "Arguments:\n"
    "    self           the angular distribution\n"
    "    cosines        the cosine values\n"
    "    values         the probability values\n"
    "    interpolant    the interpolation type (default lin-lin),\n"
    "                   see InterpolationType for all interpolation types"
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
  .def_property_readonly(

    "has_cdf",
    &Component::hasCdf,
    "Flag to indicate whether or not the cumulative distribution function (cdf) "
    "is defined"
  )
  .def(

    "__call__",
    [] ( const Component& self, double cosine ) -> decltype(auto)
       { return self( cosine ); },
    python::arg( "cosine" ),
    "Evaluate the pdf of the distribution for a given cosine value\n\n"
    "Arguments:\n"
    "    self      the distribution\n"
    "    cosine    the cosine value"
  );
}
