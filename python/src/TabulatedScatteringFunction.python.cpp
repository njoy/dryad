// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/TabulatedScatteringFunction.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedScatteringFunction( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TabulatedScatteringFunction;
  using InterpolationType = njoy::dryad::InterpolationType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedScatteringFunction",
    "A scattering function table"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  std::vector< std::size_t >,
                  std::vector< InterpolationType > >(),
    python::arg( "inverse_lengths" ), python::arg( "values" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    "Initialise the scattering function table\n\n"
    "Arguments:\n"
    "    self              the scattering function table\n"
    "    inverse_lengths   the inverse length values\n"
    "    values            the scattering function values\n"
    "    boundaries        the boundaries of the interpolation regions\n"
    "    interpolants      the interpolation types of the interpolation regions,\n"
    "                      see InterpolationType for all interpolation types"
  )
  .def(

    python::init< std::vector< double >, std::vector< double >,
                  InterpolationType >(),
    python::arg( "inverse_lengths" ), python::arg( "values" ),
    python::arg( "interpolant" ) = InterpolationType::LinearLinear,
    "Initialise the scattering function table\n\n"
    "Arguments:\n"
    "    self              the scattering function table\n"
    "    inverse_lengths   the inverse length values\n"
    "    values            the scattering function values\n"
    "    interpolant       the interpolation type (default lin-lin),\n"
    "                      see InterpolationType for all interpolation types"
  )
  .def_property_readonly(

    "inverse_lengths",
    &Component::inverseLengths,
    "The inverse length values"
  )
  .def_property_readonly(

    "values",
    &Component::values,
    "The scattering function values"
  )
  .def_property_readonly(

    "lower_inverse_length_limit",
    &Component::lowerInverseLengthLimit,
    "The lower inverse length limit"
  )
  .def_property_readonly(

    "upper_inverse_length_limit",
    &Component::upperInverseLengthLimit,
    "The upper inverse length limit"
  )
  .def_property_readonly(

    "inverse_length",
    &Component::inverseLength,
    "The inverse length value associated to an energy,cosine pair\n\n"
    "Arguments:\n"
    "    self     the table\n"
    "    energy   the incident photon energy\n"
    "    cosine   the outgoing photon cosine"
  )
  .def(

    "__call__",
    [] ( const Component& self, double inverse_length ) -> decltype(auto)
       { return self( inverse_length ); },
    python::arg( "inverse_length" ),
    "Evaluate the table for a given inverse length value\n\n"
    "Arguments:\n"
    "    self              the table\n"
    "    inverse_length    the inverse length value"
  )
  .def(

    "__call__",
    [] ( const Component& self, double energy, double cosine ) -> decltype(auto)
       { return self( energy, cosine ); },
    python::arg( "energy" ), python::arg( "cosine" ),
    "Evaluate the table for a given energy,cosine pair\n\n"
    "Arguments:\n"
    "    self     the table\n"
    "    energy   the incident photon energy\n"
    "    cosine   the outgoing photon cosine"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard tabulated data definitions
  addStandardTabulatedDefinitions< Component >( component );
}
