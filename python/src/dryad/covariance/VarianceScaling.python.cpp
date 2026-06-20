// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/covariance/VarianceScaling.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

void wrapVarianceScaling( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::VarianceScaling;
  using ScalingType = njoy::dryad::covariance::ScalingType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "VarianceScaling",
    "Variance scaling information\n\n"
    "Some ENDF evaluations provide variance scaling information for cross section\n"
    "covariances. Each factor value for a given group characterises an uncorrelated\n"
    "contribution to the absolute variance of the cross section averaged over any\n"
    "energy subgroup that includes a portion of the energy interval over which the\n"
    "factor is defined.\n\n"
    "Parameters\n"
    "----------\n"
    "    type : njoy.dryad.covariance.ScalingType\n"
    "        the scaling procedure type\n"
    "    energies : list of float\n"
    "        the energy boundary values\n"
    "    factors : list of float\n"
    "        the scaling factor values"
  );

  // wrap the component
  component
  .def(

    python::init< ScalingType, std::vector< double >, std::vector< double > >(),
    python::arg( "type" ), python::arg( "energies" ), python::arg( "factors" ),
    "Initialise the variance scaling information"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy boundaries"
  )
  .def_property_readonly(

    "factors",
    &Component::factors,
    "The scaling factors"
  )
  .def_property_readonly(

    "number_groups",
    &Component::numberGroups,
    "The number of energy groups"
  )
  .def_property_readonly(

    "type",
    &Component::type,
    "The scaling procedure type"
  );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // covariance namespace
} // dryad namespace
