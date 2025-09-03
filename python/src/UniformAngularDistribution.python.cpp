// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/UniformAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

void wrapUniformAngularDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::UniformAngularDistribution;
  using UniformDistributionType = njoy::dryad::UniformDistributionType;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UniformAngularDistribution",
    "A uniform or equally probable angular distribution"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, UniformDistributionType >(),
    python::arg( "cosines" ), python::arg( "type" ),
    "Initialise the angular distribution\n\n"
    "Arguments:\n"
    "    self       the angular distribution\n"
    "    cosines    the cosine values\n"
    "    type       the uniform distribution type"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "type",
    [] ( const Component& self ) { return self.type(); },
    "The distribution type"
  )
  .def_property_readonly(

    "cosines",
    &Component::cosines,
    "The cosine values for the distribution"
  )
  .def_property_readonly(

    "number_cosines",
    &Component::numberCosines,
    "The number of discrete cosines or intervals"
  )
  .def_property_readonly(

    "average_cosine",
    &Component::averageCosine,
    "The average cosine defined by the distribution"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}
