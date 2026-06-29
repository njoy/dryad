// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

//local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/UnresolvedChannel.hpp"

namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapUnresolvedChannel( python::module& module ){

 // type aliases
 using Component = njoy::dryad::resonances::UnresolvedChannel;
 using Channel = njoy::dryad::resonances::Channel;
 using ChannelID = njoy::dryad::id::ChannelID;
 using ParticlePair = njoy::dryad::resonances::ParticlePair;
 using ChannelRadii = njoy::dryad::resonances::ChannelRadii;
 using Kinematics = njoy::dryad::resonances::Kinematics;
 using Background = njoy::dryad::resonances::Channel::Background;
 
 // wrap views created by this component
 
 // create the component
 python::class_< Component > component(

     module,
     "UnresolvedChannel",
     "A resonance reaction channel for use in the unresolved resonance region"
     );

   // wrap the component
   component
  .def(

    python::init< ChannelID,
                  std::optional< ParticlePair >,
                  double,
                  std::optional< double >,
                  ChannelRadii,
                  Kinematics,
                  std::optional< Background >,
                  double >(),
    python::arg( "identifier" ), python::arg( "incident" ),
    python::arg( "outgoing" ), python::arg( "q_value" ),
    python::arg( "boundary" ), python::arg( "radii" ),
    python::arg( "kinematics" ) = Kinematics::NonRelativistic,
    python::arg( "background" ) = std::nullopt,
    python::arg( "reference_energy" ) = 1.,
    "Initialize the unresolved channel\n\n"
    "The underlying channel is constructed from its components.\n\n"
    "Arguments:\n"
    "    self               the unresolved channel\n"
    "    identifier         the channel identifier\n"
    "    incident           the current incident particle pair\n"
    "    outgoing           the outgoing particle pair\n"
    "    q_value            the Q value associated with the transition from\n"
    "                       the incident to the outgoing particle pair\n"
    "    boundary           the boundary condition\n"
    "    radii              the channel radii for the calculation of the\n"
    "                       wave functions\n"
    "    kinematics         the kinematics type applied to the channel (default\n"
    "                       is non-relativistic)\n"
    "    background         the background function (if defined)\n"
    "    reference_energy   the energy at which reduced widths are defined\n"
    "                       (default is 1 eV)"
  )
  .def(

    python::init< Channel, double >(),
    python::arg( "channel" ),
    python::arg( "reference_energy" ) = 1.,
    "Initialise the unresolved channel using an existing channel\n\n"
    "Arguments:\n"
    "    self               the unresolved channel\n"
    "    channel            the underlying channel\n"
    "    reference_energy   the energy at which reduced widths are defined\n"
    "                       (default is 1 eV)"
  )
  .def_property_readonly(
 
    "channel",
    &Component::channel,
    "The underlying channel"
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
 
    "outgoing_particle_pair",
    &Component::outgoingParticlePair,
    "The outgoing particle pair (if defined)"
  )
  .def_property_readonly(
 
    "channel_radii",
    &Component::channelRadii,
    "The channel radii"
  )
  .def_property_readonly(
 
    "reference_energy",
    &Component::referenceEnergy,
    "The reference energy at which the reduced widths are defined"
  )
  .def_property_readonly(
 
    "conversion_factor",
    &Component::conversionFactor,
    "The width conversion strategy applied to the channel"
  )
  .def(
 
    "wave_number",
    &Component::waveNumber,
    python::arg( "energy" ),
    "Calculate the channel wave number (given in fm^-1) at a given energy\n\n"
    "Arguments:\n"
    "    self     the unresolved channel\n"
    "    energy   the energy (given in eV)"
  )
  .def(
 
    "width_conversion_factor",
    &Component::widthConversionFactor,
    python::arg( "energy" ),
    "Calculate the width conversion factor at a given energy\n\n"
    "The reduced width stored for a channel is converted to the physical\n"
    "width at a given energy by multiplying it with this factor. For a\n"
    "neutron channel the factor is ( P_l(E) / P_0(E) ) * sqrt( E / E_ref );\n"
    "for any other channel the factor is 1.\n\n"
    "Arguments:\n"
    "    self     the unresolved channel\n"
    "    energy   the energy (given in eV)"
  );

 // add standard equality comparison definitions
 addStandardEqualityComparisonDefinitions< Component >( component );

 // add standard copy definitions
 addStandardCopyDefinitions< Component >( component );
}


}
}
