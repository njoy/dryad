// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/UnresolvedResonanceTable.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapUnresolvedResonanceTable( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::UnresolvedResonanceTable;
  using ChannelID = njoy::dryad::id::ChannelID;
  using TabulatedAverageWidths = njoy::dryad::resonances::TabulatedAverageWidths;
  using TabulatedLevelSpacing = njoy::dryad::resonances::TabulatedLevelSpacing;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedResonanceTable",
    "A table of unresolved average parameters for a set of channels\n\n"
    "Parameters\n"
    "----------\n"
    "    channels : list of njoy.dryad.id.ChannelID\n"
    "        the channel identifiers (nc values)\n"
    "    widths : list of njoy.dryad.resonances.TabulatedAverageWidths\n"
    "        the tabulated average widths (nc values)\n"
    "    spacings : njoy.dryad.id.TabulatedLevelSpacing\n"
    "        the average level spacing"
  );

  // wrap the component
  component
  .def(


    python::init< std::vector< ChannelID >,
                  std::vector< TabulatedAverageWidths >,
                  TabulatedLevelSpacing >(),
    python::arg( "channels" ),
    python::arg( "average_widths" ),
    python::arg( "level_spacings" ),
    "Initialise the table"
  )
  .def_property_readonly(

    "channels",
    python::overload_cast<>( &Component::channels, python::const_ ),
    "The channel identifiers"
  )
  .def_property_readonly(

    "widths",
    python::overload_cast<>( &Component::widths, python::const_ ),
    "The average widths"
  )
  .def_property_readonly(

    "spacings",
    python::overload_cast<>( &Component::spacings, python::const_ ),
    "The level spacings"
  )
  .def_property_readonly(

    "number_channels",
    &Component::numberChannels,
    "The number of channels in the table"
  )
  .def(

    "has_channel",
    &Component::hasChannel,
    python::arg( "channel" ),
    "Return whether or not a channel is present\n\n"
    "Parameters\n"
    "----------\n"
    "    channel : njoy.dryad.id.ChannelID\n"
    "        the channel identifier"
  )
  .def(

    "channel_widths",
    python::overload_cast< const ChannelID& >( &Component::channelWidths, python::const_ ),
    python::arg( "channel" ),
    "Return the average widths for a given channel\n\n"
    "Parameters\n"
    "----------\n"
    "    channel : njoy.dryad.id.ChannelID\n"
    "        the channel identifier"
  );

  addStandardEqualityComparisonDefinitions< Component >( component );
  addStandardCopyDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
