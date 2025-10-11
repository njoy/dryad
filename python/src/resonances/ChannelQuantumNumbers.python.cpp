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
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
