// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/UnresolvedSpinGroup.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {
void wrapUnresolvedSpinGroup( python::module& module ) {
 
  // type aliases
  using Component = njoy::dryad::resonances::UnresolvedSpinGroup;
  using Channel = njoy::dryad::resonances::Channel;
  using UnresolvedResonanceTable = njoy::dryad::resonances::UnresolvedResonanceTable;
  using ReactionID = njoy::dryad::id::ReactionID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(
 
    module,
    "UnresolvedSpinGroup",
    "A spin group corresponding to a Jpi quantum number set in the\n"
    "unresolved resonance region"
   );
  // wrap the component
  component
  .def(
 
    python::init< std::vector< Channel >, UnresolvedResonanceTable >(),
    python::arg( "channels" ), python::arg( "resonances" ),
    "Initialise the unresolved spin group\n\n"
    "If the channels are not sorted, they will get sorted through the order\n"
    "of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical\n"
    "sorting order).\n\n"
    "Arguments:\n"
    "    self         the spin group\n"
    "    channels     the channels in the spin group\n"
    "    resonances   the unresolved resonance table of the spin group"
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
    python::overload_cast< UnresolvedResonanceTable >( &Component::resonanceTable ),
    "The unresolved resonance table of the spin group"
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
  .def_property_readonly(
 
    "reactions",
    python::overload_cast<>( &Component::reactions, python::const_ ),
    "The reactions to which this spin group contributes"
  )
  .def_property_readonly(
 
    "kinematics_type",
    &Component::kinematicsType,
    "The kinematics type applied to the spin group"
  )
  .def_property_readonly(
 
    "has_channels_with_background",
    &Component::hasChannelsWithBackground,
    "Flag to indicate whether or not the channels in the spin group have backgrounds"
  );
  addStandardEqualityComparisonDefinitions< Component >( component );

  addStandardCopyDefinitions< Component >( component );

}


}
}