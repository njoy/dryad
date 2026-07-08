// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/UnresolvedChannel.hpp"

namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapUnresolvedChannel( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::UnresolvedChannel;
  using Channel = njoy::dryad::resonances::Channel;
  using ChannelID = njoy::dryad::id::ChannelID;
  using ReactionID = njoy::dryad::id::ReactionID;
  using ParticlePair = njoy::dryad::resonances::ParticlePair;
  using ChannelRadii = njoy::dryad::resonances::ChannelRadii;
  using Kinematics = njoy::dryad::resonances::Kinematics;
  using Background = njoy::dryad::resonances::Channel::Background;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedChannel",
    "A resonance reaction channel for use in the unresolved resonance region\n\n"
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
    "    reference_energy : float\n"
    "        the energy at which reduced widths are defined (default is 1 eV)"
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
                  double >(),
    python::arg( "identifier" ), python::arg( "incident" ),
    python::arg( "outgoing" ), python::arg( "q_value" ),
    python::arg( "boundary" ), python::arg( "radii" ),
    python::arg( "reference_energy" ) = 1.,
    "Initialize the unresolved channel"
  )
  .def_property(

    "identifier",
    [] ( const Component& self ) -> decltype(auto)
       { return self.identifier(); },
    [] ( Component& self, ChannelID id )
       { self.identifier( std::move( id ) ); },
    "The channel identifier"
  )
  .def_property_readonly(

    "reaction",
    [] ( const Component& self ) -> decltype(auto)
       { return self.reaction(); },
    "The reaction this channel contributes to"
  )
  .def_property(

    "incident_particle_pair",
    [] ( const Component& self ) -> decltype(auto)
       { return self.incidentParticlePair(); },
    [] ( Component& self, ParticlePair pair )
       { self.incidentParticlePair( std::move( pair ) ); },
    "The outgoing particle pair (if defined)"
  )
  .def_property(

    "outgoing_particle_pair",
    [] ( const Component& self ) -> decltype(auto)
       { return self.outgoingParticlePair(); },
    [] ( Component& self, std::optional< ParticlePair > pair )
       { self.outgoingParticlePair( std::move( pair ) ); },
    "The outgoing particle pair (if defined)"
  )
  .def_property(

    "channel_radii",
    [] ( const Component& self ) -> decltype(auto)
       { return self.channelRadii(); },
    [] ( Component& self, ChannelRadii radii )
       { self.channelRadii( std::move( radii ) ); },
    "The channel radii"
  )
  .def_property(

    "reference_energy",
    python::overload_cast<>( &Component::referenceEnergy, python::const_ ),
    python::overload_cast< double >( &Component::referenceEnergy ),
    "The reference energy"
  )
  .def(

    "wave_number",
    [] ( const Component& self, double energy ) -> decltype(auto)
       { return self.waveNumber( energy ); },
    python::arg( "energy" ),
    "Calculate the channel wave number (given in fm^-1) at a given energy\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy (given in eV)"
  )
  .def(

    "width_conversion_factor",
    &Component::widthConversionFactor,
    python::arg( "energy" ),
    "Calculate the width conversion factor at a given energy\n\n"
    "The reduced width stored for a channel is converted to the physical\n"
    "width at a given energy by multiplying it with this factor.\n\n"
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
