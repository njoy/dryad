// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/ResonanceTable.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
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
    "all given as column data.\n\n"
    "The energies and channels do not have to be sorted (they will be sorted\n"
    "upon construction).\n\n"
    "Parameters\n"
    "----------\n"
    "    channels : list of njoy.dryad.id.ChannelID or njoy.dryad.id.ChannelID\n"
    "        the channel identifiers (nc values for multiple channels, single channel)\n"
    "    energies : list of float\n"
    "        the level energies (ne values)\n"
    "    amplitudes : list of list of float or list of float\n"
    "        the reduced width amplitudes (nc arrays of ne values, or single array of ne values)"
   );

  // wrap the component
  component
  .def(

    python::init< std::vector< ChannelID >,
                  std::vector< double >,
                  std::vector< std::vector< double > > >(),
    python::arg( "channels" ), python::arg( "energies" ),
    python::arg( "amplitudes" ),
    "Initialise the table with multiple channels"
  )
  .def(

    python::init< ChannelID,
                  std::vector< double >,
                  std::vector< double > >(),
    python::arg( "channel" ), python::arg( "energies" ),
    python::arg( "amplitudes" ),
    "Initialise the table with a single channel"
  )
  .def(

    python::init< std::vector< ChannelID > >(),
    python::arg( "channels" ),
    "Initialise an empty table with multiple channels"
  )
  .def(

    python::init< ChannelID >(),
    python::arg( "channel" ),
    "Initialise an empty table with a single channel"
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
    "Parameters\n"
    "----------\n"
    "    channel : njoy.dryad.id.CHannelID\n"
    "        the channel identifier"
  )
  .def(

    "has_energy",
    &Component::hasEnergy,
    python::arg( "energy" ),
    "Return whether or not an energy is present\n\n"
    "Parameters\n"
    "----------\n"
    "    energy : float\n"
    "        the energy value"
  )
  .def( python::self += python::self )
  .def( python::self + python::self );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
