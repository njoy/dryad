// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace resonances {

void wrapSpinGroup( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::resonances::SpinGroup;
  using ChannelData = njoy::dryad::resonances::SpinGroup::ChannelData;
  using Channel = njoy::dryad::resonances::Channel;
  using ResonanceTable = njoy::dryad::resonances::ResonanceTable;
  using Formalism = njoy::dryad::resonances::Formalism;
  using BoundaryCondition = njoy::dryad::resonances::BoundaryCondition;
  using ReactionID = njoy::dryad::id::ReactionID;

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

    python::init< std::vector< Channel >, ResonanceTable,
                  Formalism, BoundaryCondition >(),
    python::arg( "channels" ), python::arg( "resonances" ),
    python::arg( "formalism" ), python::arg( "boundary" ),
    "Initialise the spin group\n\n"
    "If the channels are not sorted, they will get sorted through the order\n"
    "of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical\n"
    "sorting order).\n\n"
    "Arguments:\n"
    "    self         the spin group\n"
    "    channels     the channels in the spin group\n"
    "    resonances   the resonance table of the spin group\n"
    "    formalism    the r matrix formalism option to be applied\n"
    "    boundary     the boundary condition option to be applied"
  )
  .def(

    python::init< std::vector< ChannelData >,
                  Formalism, BoundaryCondition >(),
    python::arg( "channels" ),
    python::arg( "formalism" ),
    python::arg( "boundary" ),
    "Initialise the spin group\n\n"
    "If the channels are not sorted, they will get sorted through the order\n"
    "of the channel identifier (which uses a Jpi,l,s,reaction,partial lexographical\n"
    "sorting order).\n\n"
    "Arguments:\n"
    "    self       the spin group\n"
    "    channels   the channel data in the spin group\n"
    "    formalism    the r matrix formalism option to be applied\n"
    "    boundary     the boundary condition option to be applied"
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
  )
  .def_property_readonly(

    "formalism",
    python::overload_cast<>( &Component::formalism, python::const_ ),
    "The formalism"
  )
  .def_property_readonly(

    "boundary_condition",
    python::overload_cast<>( &Component::boundaryCondition, python::const_ ),
    "The boundary condition option"
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
  .def(

    "cross_sections",
    [] ( Component& self, double energy ) -> std::map< ReactionID, double > {

      std::map< ReactionID, double > xs;
      self.crossSections( energy, xs );
      return xs;
    },
    python::arg( "energy" ),
    "Calculate the cross section values at a given energy\n\n"
    "Arguments:\n"
    "    self     the spin group\n"
    "    energy   the energy"
  );

  // add standard comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // resonances namespace
} // dryad namespace
