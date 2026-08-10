// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/Channel.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapChannel( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::Channel;
  using ChannelID = njoy::dryad::id::ChannelID;
  using ParticlePair = njoy::dryad::resonances::ParticlePair;
  using ChannelRadii = njoy::dryad::resonances::ChannelRadii;
  using Kinematics = njoy::dryad::resonances::Kinematics;
  using Background = njoy::dryad::resonances::Channel::Background;
  using Penetrability = njoy::dryad::resonances::Channel::Penetrability;
  using ShiftFactor = njoy::dryad::resonances::Channel::ShiftFactor;
  using PhaseShift = njoy::dryad::resonances::Channel::PhaseShift;
  using PhaseShiftDifference = njoy::dryad::resonances::Channel::PhaseShiftDifference;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Channel",
    "A resonance reaction channel\n\n"
    "Parameters\n"
    "----------\n"
    "    identifier : njoy.dryad.id.ChannelID\n"
    "        the channel identifier\n"
    "    incident : njoy.dryad.resonances.ParticlePair\n"
    "        the current incident particle pair\n"
    "    outgoing : njoy.dryad.resonances.ParticlePair, optional\n"
    "        the outgoing particle pair\n"
    "    q_value : float\n"
    "        the Q value associated with the transition from the incident to\n"
    "        the outgoing particle pair\n"
    "    boundary : float, optional\n"
    "        the boundary condition\n"
    "    radii : njoy.dryad.resonances.ChannelRadii\n"
    "        the channel radii for the calculation of the wave functions\n"
    "    calculate_wave_functions : boolean, default=True\n"
    "        the wave function calculation flag (when true will select the\n"
    "        proper function or switch off calculation when appropriate,\n"
    "        when false will switch off calculation regardless and set\n"
    "        penetrability, shift factor, phase shift and phwse shift\n"
    "        difference to 1, 0, 0, 0 respectively)\n"
    "    kinematics : njoy.dryad.resonances.Kinematics, default=Kinematics.NonRelativistic\n"
    "        the kinematics type applied to the channel\n"
    "    background : Channel.Background, optional\n"
    "        the background function\n"
    "    penetrability : Channel.Penetrability, optional\n"
    "        the penetrability of the channel\n"
    "    shift_factor : Channel.ShiftFactor, optional\n"
    "        the shift factor of the channel\n"
    "    phase_shift : Channel.PhaseShift, optional\n"
    "        the phase shift of the channel\n"
    "    phase_shift_difference : Channel.PhaseShiftDifference, optional\n"
    "        the phase shift difference of the channel"
   );

  // wrap the component
  component
  .def(

    python::init< ChannelID,
                  ParticlePair,
                  std::optional< ParticlePair >,
                  double,
                  std::optional< double >,
                  ChannelRadii,
                  Kinematics,
                  std::optional< Background >,
                  Penetrability,
                  ShiftFactor,
                  PhaseShift,
                  PhaseShiftDifference >(),
    python::arg( "identifier" ), python::arg( "incident" ),
    python::arg( "outgoing" ), python::arg( "q_value" ),
    python::arg( "boundary" ), python::arg( "radii" ),
    python::arg( "kinematics" ), python::arg( "background" ),
    python::arg( "penetrability" ), python::arg( "shift_factor" ),
    python::arg( "phase_shift" ), python::arg( "phase_shift_difference" ),
    "Initialise the channel with explicit wave functions"
  )
  .def(

    python::init< ChannelID,
                  ParticlePair,
                  std::optional< ParticlePair >,
                  double,
                  std::optional< double >,
                  ChannelRadii,
                  bool,
                  Kinematics,
                  std::optional< Background > >(),
    python::arg( "identifier" ), python::arg( "incident" ),
    python::arg( "outgoing" ), python::arg( "q_value" ),
    python::arg( "boundary" ), python::arg( "radii" ),
    python::arg( "calculate_wave_functions" ) = true,
    python::arg( "kinematics" ) = Kinematics::NonRelativistic,
    python::arg( "background" ) = std::nullopt,
    "Initialise the channel"
  )
  .def_property(

    "identifier",
    python::overload_cast<>( &Component::identifier, python::const_ ),
    python::overload_cast< ChannelID >( &Component::identifier ),
    "The channel identifier"
  )
  .def_property_readonly(

    "reaction",
    &Component::reaction,
    "The reaction this channel contributes to"
  )
  .def_property_readonly(

    "quantum_numbers",
    &Component::quantumNumbers,
    "The quantum numbers of the channel"
  )
  .def_property(

    "incident_particle_pair",
    python::overload_cast<>( &Component::incidentParticlePair, python::const_ ),
    python::overload_cast< ParticlePair >( &Component::incidentParticlePair ),
    "The incident particle pair"
  )
  .def_property(

    "outgoing_particle_pair",
    python::overload_cast<>( &Component::outgoingParticlePair, python::const_ ),
    python::overload_cast< std::optional< ParticlePair > >( &Component::outgoingParticlePair ),
    "The outgoing particle pair (if defined)"
  )
  .def_property_readonly(

    "is_incident_channel",
    &Component::isIncidentChannel,
    "The flag to indicate whether or not the channel is an incident channel"
  )
  .def_property(

    "q_value",
    python::overload_cast<>( &Component::qValue, python::const_ ),
    python::overload_cast< double >( &Component::qValue ),
    "The q value of the transition"
  )
  .def_property(

    "boundary_condition",
    python::overload_cast<>( &Component::boundaryCondition, python::const_ ),
    python::overload_cast< std::optional< double > >( &Component::boundaryCondition ),
    "The boundary condition value (if defined)"
  )
  .def_property_readonly(

    "has_background",
    &Component::hasBackground,
    "Flag indicating whether or not a background function is defined"
  )
  .def_property(

    "background",
    python::overload_cast<>( &Component::background, python::const_ ),
    python::overload_cast< std::optional< Background > >( &Component::background ),
    "The background function (if defined)"
  )
  .def_property(

    "channel_radii",
    python::overload_cast<>( &Component::channelRadii, python::const_ ),
    python::overload_cast< ChannelRadii >( &Component::channelRadii ),
    "The channel radii"
  )
  .def_property(

    "kinematics_type",
    python::overload_cast<>( &Component::kinematicsType, python::const_ ),
    python::overload_cast< Kinematics >( &Component::kinematicsType ),
    "The kinematics type applied to the channel"
  )
  .def_property_readonly(

    "statistical_spin_factor",
    &Component::statisticalSpinFactor,
    "The statistical spin factor\n\n"
    "The statistical spin factor g of a channel is defined as follows:\n"
    "   g = ( 2 * J + 1 ) / ( 2 * ia + 1 ) / ( 2 * ib + 1 )\n"
    "in which J is the total angular momentum of the channel and ia and ib\n"
    "are the spins of the particles in the outgoing particle pair."
  )
  .def(

    "is_below_threshold",
    &Component::isBelowThreshold,
    python::arg( "energy" ),
    "Return whether or not the energy is below the threshold for this channel\n\n"
    "The incident energy is below the threshold energy for the channel if\n"
    "    energy * ratio + q < 0.0\n"
    "where energy is the incident energy, ratio is the mass ratio M / ( m + M )\n"
    "for the incident particle pair and q is the Q value for this channel.\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy to be tested"
  )
  .def(

    "wave_number",
    &Component::waveNumber,
    python::arg( "energy" ),
    "Calculate the channel wave number (given in fm^-1) at a given energy\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy (given in eV)"
  )
  .def(

    "sommerfeld_parameter",
    &Component::sommerfeldParameter,
    python::arg( "energy" ),
    "Calculate the Sommerfeld parameter for the channel at a given energy\n\n"
    "The Sommerfeld parameter eta is an energy dependent quantity defined as\n"
    "follows:\n"
    "   eta = z * Z * mu / ( 4 * pi * epsilon0 * hbar^2 * k )\n"
    "in which z and Z are the electrical charge of the particles in the\n"
    "particle pair, mu is the reduced mass of the particle pair, hbar is the\n"
    "Planck constant, k is the wave number and epsilon0 is the vacuum\n"
    "permittivity.\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy (given in eV)"
  )
  .def_property_readonly(

    "has_penetrability",
    &Component::hasPenetrability,
    "Flag indicating whether or not there is a penetrability implementation"
  )
  .def(

    "penetrability",
    &Component::penetrability,
    python::arg( "energy" ),
    "Calculate the penetrability for the channel at a given energy\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy (given in eV)"
  )
  .def_property_readonly(

    "has_shift_factor",
    &Component::hasShiftFactor,
    "Flag indicating whether or not there is a shift factor implementation"
  )
  .def(

    "shift_factor",
    &Component::shiftFactor,
    python::arg( "energy" ),
    "Calculate the shift factor for the channel at a given energy\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy (given in eV)"
  )
  .def_property_readonly(

    "has_phase_shift",
    &Component::hasPhaseShift,
    "Flag indicating whether or not there is a phase shift implementation"
  )
  .def(

    "phase_shift",
    &Component::phaseShift,
    python::arg( "energy" ),
    "Calculate the phase shift for the channel at a given energy\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy (given in eV)"
  )
  .def_property_readonly(

    "has_phase_shift_difference",
    &Component::hasPhaseShiftDifference,
    "Flag indicating whether or not there is a phase shift difference implementation"
  )
  .def(

    "phase_shift_difference",
    &Component::phaseShiftDifference,
    python::arg( "energy" ),
    "Calculate the phase shift difference for the channel at a given energy\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy (given in eV)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
