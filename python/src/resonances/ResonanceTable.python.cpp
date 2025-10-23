// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/ResonanceTable.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapResonanceTable( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::ResonanceTable;
  using ChannelID = njoy::dryad::id::ChannelID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceTable",
    "A table of parameters for a set of channels\n\n"
    "The table contains level energies and reduced width amplitudes,\n"
    "all given as column data."
   );

  // wrap the component
  component
  .def(

    python::init< std::vector< ChannelID >,
                  std::vector< double >,
                  std::vector< std::vector< double > > >(),
    python::arg( "channels" ), python::arg( "energies" ),
    python::arg( "amplitudes" ),
    "Initialise the table\n\n"
    "The ResonanceTable class takes the reduced width amplitudes for a\n"
    "number of channels (at least one channel must be given).\n\n"
    "Arguments:\n"
    "    self         the table\n"
    "    channels     the channel identifiers (nc values)\n"
    "    energies     the level energies (ne values)\n"
    "    amplitudes   the reduced width amplitudes (nc arrays of ne values)"
  )
  .def(

    python::init< ChannelID,
                  std::vector< double >,
                  std::vector< double > >(),
    python::arg( "channel" ), python::arg( "energies" ),
    python::arg( "amplitudes" ),
    "Initialise the table\n\n"
    "Arguments:\n"
    "    self         the table\n"
    "    channel      the channel identifier\n"
    "    energies     the level energies\n"
    "    amplitudes   the reduced width amplitudes"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "channels",
    python::overload_cast<>( &Component::channels, python::const_ ),
    "The channel identifiers"
  )
  .def_property_readonly(

    "energies",
    python::overload_cast<>( &Component::energies, python::const_ ),
    "The level energies"
  )
  .def_property_readonly(

    "reduced_width_amplitudes",
    python::overload_cast<>( &Component::reducedWidthAmplitudes, python::const_ ),
    "The reduced width amplitudes"
  )
  .def_property_readonly(

    "number_channels",
    &Component::numberChannels,
    "The number of channels in the table"
  )
  .def_property_readonly(

    "number_energies",
    &Component::numberEnergies,
    "The number of level energies in the table"
  )
  .def(

    "has_channel",
    &Component::hasChannel,
    python::arg( "channel" ),
    "Return whether or not a channel is present\n\n"
    "Arguments:\n"
    "    self      the table\n"
    "    channel   the channel identifier"
  )
  .def(

    "has_energy",
    &Component::hasEnergy,
    python::arg( "energy" ),
    "Return whether or not an energy is present\n\n"
    "Arguments:\n"
    "    self     the table\n"
    "    energy   the energy value"
  )
  .def( python::self += python::self )
  .def( python::self + python::self );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
