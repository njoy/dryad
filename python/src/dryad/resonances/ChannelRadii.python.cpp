// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "dryad/resonances/ChannelRadii.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapChannelRadii( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::ChannelRadii;
  using TabulatedRadius = njoy::dryad::resonances::TabulatedRadius;
  using Radius = std::variant< double, TabulatedRadius >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ChannelRadii",
    "Channel radii used in wave function calculations\n\n"
    "The penetrability P, shift factor S and phase shift phi require knowledge\n"
    "of the channel radius in their calculation. The ChannelRadii class provides\n"
    "these radii for each one of these."
   );

  // wrap the component
  component
  .def(

    python::init< Radius >(),
    python::arg( "radius" ),
    "Initialise the channel radii\n\n"
    "Arguments:\n"
    "    self     the radii\n"
    "    radius   the channel radius to be used for P, S and phi"
  )
  .def(

    python::init< Radius, Radius >(),
    python::arg( "true_radius" ),
    python::arg( "effective_radius" ),
    "Initialise the channel radii\n\n"
    "Arguments:\n"
    "    self               the radii\n"
    "    true_radius        the channel radius to be used for P and S\n"
    "    effective_radius   the channel radius to be used for phi"
  )
  .def(

    python::init< Radius, Radius, Radius >(),
    python::arg( "penetrability" ),
    python::arg( "shift_factor" ),
    python::arg( "phase_shift" ),
    "Initialise the channel radii\n\n"
    "Arguments:\n"
    "    self                  the radii\n"
    "    penetrability         the channel radius to be used for P\n"
    "    shift_factor          the channel radius to be used for S\n"
    "    phase_shift           the channel radius to be used for phi"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "has_shift_factor_radius",
    &Component::hasShiftFactorRadius,
    "Flag indicating whether or not a shift factor radius is defined"
  )
  .def_property_readonly(

    "has_phase_shift_radius",
    &Component::hasPhaseShiftRadius,
    "Flag indicating whether or not a phase shift radius is defined"
  )
  .def_property(

    "penetrability_radius",
    python::overload_cast<>( &Component::penetrabilityRadius, python::const_ ),
    python::overload_cast< Radius >( &Component::penetrabilityRadius ),
    "The penetrability radius"
  )
  .def_property(

    "shift_factor_radius",
    python::overload_cast<>( &Component::shiftFactorRadius, python::const_ ),
    python::overload_cast< std::optional< Radius > >( &Component::shiftFactorRadius ),
    "The shift factor radius"
  )
  .def_property(

    "phase_shift_radius",
    python::overload_cast<>( &Component::phaseShiftRadius, python::const_ ),
    python::overload_cast< std::optional< Radius > >( &Component::phaseShiftRadius ),
    "The phase shift radius"
  )
  .def(

    "calculate_penetrability_radius",
    &Component::calculatePenetrabilityRadius,
    python::arg( "energy" ),
    "Return the channel radius for the penetrability P\n\n"
    "Arguments:\n"
    "    self     the radii\n"
    "    energy   the energy for which the radius must be given"
  )
  .def(

    "calculate_shift_factor_radius",
    &Component::calculateShiftFactorRadius,
    python::arg( "energy" ),
    "Return the channel radius for the shift factor S\n\n"
    "Arguments:\n"
    "    self     the radii\n"
    "    energy   the energy for which the radius must be given"
  )
  .def(

    "calculate_phase_shift_radius",
    &Component::calculatePhaseShiftRadius,
    python::arg( "energy" ),
    "Return the channel radius for the phase shift phi\n\n"
    "Arguments:\n"
    "    self     the radii\n"
    "    energy   the energy for which the radius must be given"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
