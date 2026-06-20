// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/UniformAngularDistribution.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapUniformAngularDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::UniformAngularDistribution;
  using UniformDistributionType = njoy::dryad::UniformDistributionType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UniformAngularDistribution",
    "A uniform or equally probable angular distribution\n\n"
    "The uniform distribution can be defined for discrete values\n"
    "(e.g. as used in inelastic thermal scattering ACE files) or\n"
    "cosine intervals (e.g. as used in older incident neutron ACE\n"
    "files).\n\n"
    "Parameters\n"
    "----------\n"
    "    cosines : list of float\n"
    "         the cosine values\n"
    "    type : njoy.dryad.UniformDistributionType\n"
    "         the uniform distribution type"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< double >, UniformDistributionType >(),
    python::arg( "cosines" ), python::arg( "type" ),
    "Initialise the angular distribution"
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

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
