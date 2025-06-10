// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/TwoBodyDistributionData.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTwoBodyDistributionData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::TwoBodyDistributionData;
  using ReferenceFrame = njoy::dryad::ReferenceFrame;
  using AngularDistributions = Component::AngularDistributions;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "TwoBodyDistributionData",
    "The energy-angle distribution data for a two-body output channel\n\n"
    "In this representation, only the angular distributions as a function of\n"
    "incident energy is given and the outgoing particle's energy can be derived\n"
    "through kinematics.\n\n"
    "For incident neutron data, this corresponds with elastic and inelastic\n"
    "scattering data given in MF4 (none of these will have corresponding MF5\n"
    "data). In the more general MF6 representation, this corresponds with\n"
    "LAW = 2 (discrete two-body scattering). This is also the representation for\n"
    "elastic scattering data in MF26 for electro-atomic interactions."
  );

  // wrap the component
  component
  .def(

    python::init< ReferenceFrame, AngularDistributions >(),
    python::arg( "frame" ), python::arg( "angle" ),
    "Initialise the two-body distribution data\n\n"
    "Arguments:\n"
    "    self    the reaction product distribution data\n"
    "    frame   the reference frame of the distribution data\n"
    "    angle   the angular distributions"
  )
  .def_property_readonly(

    // static constexpr function needs lambda
    "type",
    [] ( const Component& self ) { return self.type(); },
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
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}
