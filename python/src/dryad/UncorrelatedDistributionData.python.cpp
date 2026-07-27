// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/UncorrelatedDistributionData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapUncorrelatedDistributionData( python::module& module ) {

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
    "for electro-atomic interactions.\n\n"
    "Parameters\n"
    "----------\n"
    "    frame : njoy.dryad.ReferenceFrame\n"
    "        the reference frame of the distribution data\n"
    "    angle : njoy.dryad.IsotropicAngularDistributions, njoy.dryad.LegendreAngularDistributions, or njoy.dryad.TabulatedAngularDistributions\n"
    "        the angular distributions\n"
    "    energy : njoy.dryad.MultiEnergyDistributions or njoy.dryad.TabulatedEnergyDistributions\n"
    "        the energy distributions\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise all probability data"
  );

  // wrap the component
  component
  .def(

    python::init< ReferenceFrame, AngularDistributions, EnergyDistributions,
                  bool >(),
    python::arg( "frame" ), python::arg( "angle" ), python::arg( "energy" ),
    python::arg( "normalise" ) = false,
    "Initialise the uncorrelated distribution data"
  )
  .def_property_readonly(

    // static constexpr function needs lambda
    "type",
    [] ( const Component& self ) { return self.type(); },
    "The distribution data type"
  )
  .def_property(

    "frame",
    python::overload_cast<>( &Component::frame, python::const_ ),
    python::overload_cast< ReferenceFrame >( &Component::frame ),
    "The reference frame"
  )
  .def_property(

    "angle",
    python::overload_cast<>( &Component::angle, python::const_ ),
    python::overload_cast< AngularDistributions >( &Component::angle ),
    "The angular distributions"
  )
  .def_property(

    "energy",
    python::overload_cast<>( &Component::energy, python::const_ ),
    python::overload_cast< EnergyDistributions >( &Component::energy ),
    "The energy distributions"
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution data"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
