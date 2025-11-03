// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/Channel.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapChannel( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::Channel;
  using ChannelID = njoy::dryad::id::ChannelID;
  using ParticlePair = njoy::dryad::resonances::ParticlePair;
  using ChannelRadii = njoy::dryad::resonances::ChannelRadii;
  using WaveNumber = njoy::dryad::resonances::Channel::WaveNumber;
  using Penetrability = njoy::dryad::resonances::Channel::Penetrability;
  using ShiftFactor = njoy::dryad::resonances::Channel::ShiftFactor;
  using PhaseShift = njoy::dryad::resonances::Channel::PhaseShift;
  using PhaseShiftDifference = njoy::dryad::resonances::Channel::PhaseShiftDifference;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "Channel",
    "A resonance reaction channel"
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
                  WaveNumber,
                  Penetrability,
                  ShiftFactor,
                  PhaseShift,
                  PhaseShiftDifference >(),
    python::arg( "identifier" ), python::arg( "incident" ),
    python::arg( "outgoing" ), python::arg( "q_value" ),
    python::arg( "boundary" ), python::arg( "radii" ),
    python::arg( "wave_number" ), python::arg( "penetrability" ),
    python::arg( "shift_factor" ), python::arg( "phase_shift" ),
    python::arg( "phase_shift_difference" ),
    "Initialise the channel\n\n"
    "Arguments:\n"
    "    self                     the channel\n"
    "    identifier               the channel identifier\n"
    "    incident                 the current incident particle pair\n"
    "    outgoing                 the outgoing particle pair\n"
    "    q_value                  the Q value associated with the transition from\n"
    "                             the incident to the outgoing particle pair\n"
    "    boundary                 the boundary condition\n"
    "    radii                    the channel radii for the calculation of the\n"
    "                             wave functions\n"
    "    wave_number.             the wave number of the channel\n"
    "    penetrability            the penetrability of the channel\n"
    "    shift_factor             the shift factor of the channel\n"
    "    phase_shift              the phase shift of the channel\n"
    "    phase_shift_difference   the phase shift difference of the channel"
  )
  .def(

    python::init< ChannelID,
                  ParticlePair,
                  std::optional< ParticlePair >,
                  double,
                  std::optional< double >,
                  ChannelRadii >(),
    python::arg( "identifier" ), python::arg( "incident" ),
    python::arg( "outgoing" ), python::arg( "qValue" ),
    python::arg( "boundary" ), python::arg( "radii" ),
    "Initialise the channel\n\n"
    "Arguments:\n"
    "    self            the channel\n"
    "    identifier      the channel identifier\n"
    "    incident        the current incident particle pair\n"
    "    outgoing        the outgoing particle pair\n"
    "    q_value         the Q value associated with the transition from\n"
    "                    the incident to the outgoing particle pair\n"
    "    boundary        the boundary condition\n"
    "    radii           the channel radii for the calculation of the\n"
    "                    wave functions"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "identifier",
    &Component::identifier,
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
  .def_property_readonly(

    "incident_particle_pair",
    &Component::incidentParticlePair,
    "The incident particle pair"
  )
  .def_property_readonly(

    "outgoing_particle_pair",
    &Component::outgoingParticlePair,
    "The outgoing particle pair (if defined)"
  )
  .def_property_readonly(

    "is_incident_channel",
    &Component::isIncidentChannel,
    "Flag to indicate whether or not the channel is an incident channel"
  )
  .def_property_readonly(

    "q_value",
    &Component::qValue,
    "The q value of the transition"
  )
  .def_property_readonly(

    "boundary_condition",
    &Component::boundaryCondition,
    "The boundary condition value (if defined)"
  )
  .def_property_readonly(

    "channel_radii",
    &Component::channelRadii,
    "The channel radii"
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
    "Arguments:\n"
    "    self     the channel\n"
    "    energy   the energy to be tested"
  )
  .def(

    "wave_number",
    &Component::waveNumber,
    python::arg( "energy" ),
    "Calculate the channel wave number (given in fm^-1) at a given energy\n\n"
    "The wave number k is an energy dependent quantity defined as follows:\n"
    "   hbar^2 k^2 = 2 * mu * ( energy * ratio + q )\n"
    "in which mu is the reduced mass of the channel's particle pair and ratio\n"
    "is the mass ratio M / ( m + M ) for the incident particle pair, q is the\n"
    "Q value associated to the transition of the incident particle pair to the\n"
    "channel's particle pair and hbar is the reduced Planck constant.\n\n"
    "Arguments:\n"
    "    self     the channel\n"
    "    energy   the energy (given in eV)"
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
    "Arguments:\n"
    "    self     the channel\n"
    "    energy   the energy (given in eV)"
  )
  .def(

    "penetrability",
    &Component::penetrability,
    python::arg( "energy" ),
    "Calculate the penetrability for the channel at a given energy\n\n"
    "Arguments:\n"
    "    self     the channel\n"
    "    energy   the energy (given in eV)"
  )
  .def(

    "shift_factor",
    &Component::shiftFactor,
    python::arg( "energy" ),
    "Calculate the shift factor for the channel at a given energy\n\n"
    "Arguments:\n"
    "    self     the channel\n"
    "    energy   the energy (given in eV)"
  )
  .def(

    "phase_shift",
    &Component::phaseShift,
    python::arg( "energy" ),
    "Calculate the phase shift for the channel at a given energy\n\n"
    "Arguments:\n"
    "    self     the channel\n"
    "    energy   the energy (given in eV)"
  )
  .def(

    "phase_shift_difference",
    &Component::phaseShiftDifference,
    python::arg( "energy" ),
    "Calculate the phase shift difference for the channel at a given energy\n\n"
    "Arguments:\n"
    "    self     the channel\n"
    "    energy   the energy (given in eV)"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
