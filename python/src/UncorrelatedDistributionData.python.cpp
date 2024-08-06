// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/UncorrelatedDistributionData.hpp"

// namespace aliases
namespace python = pybind11;

void wrapUncorrelatedDistributionData( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::UncorrelatedDistributionData;
  using ReferenceFrame = njoy::dryad::ReferenceFrame;
  using AngularDistributions = Component::AngularDistributions;
  using EnergyDistributions = Component::EnergyDistributions;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UncorrelatedDistributionData",
    "Uncorrelated energy and angle distribution data for a reaction product\n\n"
    "In this representation, there is no correlation given between the outgoing\n"
    "angle and energy of the reaction product. As a result, the angular and energy\n"
    "distributions of the reaction product depend only on the incident energy of the\n"
    "projectile.\n\n"
    "For incident neutron data, this is used for reactions that have both MF4 and MF5\n"
    "data. For reaction products given in MF6, this corresponds to LAW = 1 (continuum\n"
    "energy-angle distributions) in which the angular dependence is fully isotropic.\n"
    "This is also the representation for Brehmstrahlung and excitation data in MF26\n"
    "for electro-atomic interactions."
  );

  // wrap the component
  component
  .def(

    python::init< ReferenceFrame, AngularDistributions, EnergyDistributions >(),
    python::arg( "frame" ), python::arg( "angle" ), python::arg( "energy" ),
    "Initialise the reaction\n\n"
    "Arguments:\n"
    "    self     the reaction product distribution data\n"
    "    frame    the reference frame of the distribution data\n"
    "    angle    the angular distributions\n"
    "    energy   the energy distributions"
  )
  .def_property_readonly(

    "type",
    &Component::type,
    "The distribution data type"
  )
  .def_property_readonly(

    "frame",
    &Component::frame,
    "The reference frame"
  )
  .def_property_readonly(

    "angle",
    &Component::angle,
    "The angular distributions"
  )
  .def_property_readonly(

    "energy",
    &Component::energy,
    "The energy distributions"
  );
}
