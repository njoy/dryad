// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/ChannelQuantumNumbers.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapChannelQuantumNumbers( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::ChannelQuantumNumbers;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ChannelQuantumNumbers",
    "The l,S,Jpi quantum numbers of a reaction channel\n\n"
    "The ChannelQuantumNumbers class contains the quantum numbers associated to\n"
    "a given reaction channel. Only channels that have the same Jpi contribute\n"
    "to the cross section of a given reaction."
   );

  // wrap the component
  component
  .def(

    python::init< unsigned int, double, double, short >(),
    python::arg( "l" ), python::arg( "s" ),
    python::arg( "J" ), python::arg( "parity" ),
    "Initialise the channel quantum numbers\n\n"
    "Arguments:\n"
    "    self     the quantum numbers\n"
    "    l        the orbital angular momentum\n"
    "    s        the channel spin\n"
    "    J        the total angular momentum\n"
    "    parity   the parity"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "orbital_angular_momentum",
    &Component::orbitalAngularMomentum,
    "The orbital angular momentum l of the channel"
  )
  .def_property_readonly(

    "spin",
    &Component::spin,
    "The channel spin"
  )
  .def_property_readonly(

    "total_angular_momentum",
    &Component::totalAngularMomentum,
    "The total angular momentum J of the channels"
  )
  .def_property_readonly(

    "parity",
    &Component::parity,
    "The parity"
  )
  .def_static(

    "allowed_channel_spin_values",
    &Component::allowedChannelSpinValues,
    python::arg( "i" ), python::arg( "I" ),
    "Calculate allowed values for the channel spin s\n\n"
    "The channel spin s can only have values between abs(i - I) and i + I\n"
    "where i is the spin of the incident particle (for a neutron that\n"
    "would be 0.5) and I is the spin of the target nucleus.\n\n"
    "Arguments:\n"
    "    i   the spin of the incident particle\n"
    "    I   the spin of the target nucleus"

  )
  .def_static(

    "allowed_total_angular_momentum_values",
    python::overload_cast< unsigned int, double, double >( &Component::allowedTotalAngularMomentumValues ),
    python::arg( "l" ), python::arg( "i" ), python::arg( "I" ),
    "Calculate possible values for the total angular momentum J\n\n"
    "The total angular momentum J for a channel can only have values between\n"
    "abs(abs(l - I) - i) and l + I +i where l is the orbital angular momentum\n"
    "of the incoming wave, i is the spin of the incident particle and I is the\n"
    "spin of the target nucleus.\n\n"
    "Arguments:\n"
    "    l   the orbital angular momentum\n"
    "    i   the spin of the incident particle\n"
    "    I   the spin of the target nucleus"
  )
  .def_static(

    "allowed_total_angular_momentum_values",
    python::overload_cast< unsigned int, double >( &Component::allowedTotalAngularMomentumValues ),
    python::arg( "l" ), python::arg( "s" ),
    "Calculate possible values for the total angular momentum J\n\n"
    "The total angular momentum J for a channel can only have values between\n"
    "abs(l - s) and l + s where l is the orbital momentum of the incoming wave\n"
    "and s is the channel spin (which in turn depends on the spin i of the\n"
    "incident particle and spin I of the target nucleus).\n\n"
    "Arguments:\n"
    "    l   the orbital angular momentum\n"
    "    s   the channel spin"

  )
  .def_static(

    "allowed_channel_quantum_numbers",
    &Component::allowedChannelQuantumNumbers,
    python::arg( "i" ), python::arg( "I" ), python::arg( "lmax" ),
    "Calculate possible combinations of channel quantum numbers\n\n"
    "Arguments:\n"
    "    i      the spin of the incident particle\n"
    "    I      the spin of the target nucleus\n"
    "    lmax   the max value of the orbital angular momentum"

  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );
}

} // resonances namespace
