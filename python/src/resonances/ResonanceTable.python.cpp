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
    "A table of resonance parameters for a set of channels\n\n"
    "The table contains resonance energies and reduced amplitude widths,\n"
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
    "Initialise the resonance table\n\n"
    "The ResonanceTable class takes the reduced amplitude widths for a\n"
    "number of channels (at least one channel must be given).\n\n"
    "Arguments:\n"
    "    self         the resonance table\n"
    "    channels     the channel identifiers (nc values)\n"
    "    energies     the resonance energies (ne values)\n"
    "    amplitudes   the reduced amplitude widths (nc arrays of ne values)"
  )
  .def(

    python::init< ChannelID,
                  std::vector< double >,
                  std::vector< double > >(),
    python::arg( "channel" ), python::arg( "energies" ),
    python::arg( "amplitudes" ),
    "Initialise the resonance table\n\n"
    "Arguments:\n"
    "    self         the resonance table\n"
    "    channel      the channel identifier\n"
    "    energies     the resonance energies\n"
    "    amplitudes   the reduced amplitude widths"
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
    &Component::channels,
    "The channel identifiers"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The resonance energies"
  )
  .def_property_readonly(

    "reduced_width_amplitudes",
    &Component::reducedWidthAmplitudes,
    "The reduced width amplitudes"
  )
  .def_property_readonly(

    "number_channels",
    &Component::numberChannels,
    "The number of channels in the table"
  )
  .def_property_readonly(

    "number_resonances",
    &Component::numberResonances,
    "The number of resonance in the table"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
