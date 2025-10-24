// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/resonances/SpinGroup.hpp"

// namespace aliases
namespace python = pybind11;

namespace resonances {

void wrapSpinGroup( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::SpinGroup;
  using ChannelData = njoy::dryad::resonances::SpinGroup::ChannelData;
  using Channel = njoy::dryad::resonances::Channel;
  using ResonanceTable = njoy::dryad::resonances::ResonanceTable;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "SpinGroup",
    "A spin group corresponding to a Jpi quantum number set"
   );

  // wrap the component
  component
  .def(

    python::init< std::vector< Channel >, ResonanceTable >(),
    python::arg( "channels" ), python::arg( "resonances" ),
    "Initialise the spin group\n\n"
    "Arguments:\n"
    "    self         the spin group\n"
    "    channels     the channels in the spingroup\n"
    "    resonances   the resonance table of the spingroup"
  )
  .def(

    python::init< std::vector< ChannelData > >(),
    python::arg( "channels" ),
    "Initialise the spin group\n\n"
    "Arguments:\n"
    "    self       the spin group\n"
    "    channels   the channel data in the spingroup"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property(

    "channels",
    python::overload_cast<>( &Component::channels, python::const_ ),
    python::overload_cast< std::vector< Channel > >( &Component::channels ),
    "The channels in the spin group"
  )
  .def_property(

    "resonance_table",
    python::overload_cast<>( &Component::resonanceTable, python::const_ ),
    python::overload_cast< ResonanceTable >( &Component::resonanceTable ),
    "The resonance table of the spin group"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
