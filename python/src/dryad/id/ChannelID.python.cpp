// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/definitions.hpp"
#include "dryad/id/ChannelID.hpp"

// namespace aliases
namespace python = pybind11;

namespace id {

void wrapChannelID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ChannelID;
  using ReactionID = njoy::dryad::id::ReactionID;
  using ChannelQuantumNumbers = njoy::dryad::resonances::ChannelQuantumNumbers;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ChannelID",
    "The channel identifier, with associated reaction and quantum numbers\n\n"
    "When using comparison on the channel identifier, we use a Jpi,l,s,reaction,partial\n"
    "ordering."
  );

  // wrap the component
  component
  .def(

    python::init< const ReactionID&, const ChannelQuantumNumbers&,
                  const std::optional< std::size_t >& >(),
    python::arg( "reaction" ), python::arg( "quantum_numbers" ),
    python::arg( "partial" ) = std::nullopt,
    "Initialise the channel identifier\n\n"
    "Arguments:\n"
    "    self              the channel identifier\n"
    "    reaction          the reaction\n"
    "    quantum_numbers   the channel quantum numbers\n"
    "    partial           the optional partial index"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "symbol" ),
    "Initialise the channel identifier\n\n"
    "Arguments:\n"
    "    self     the channel identifier\n"
    "    symbol   the channel symbol"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "reaction",
    &Component::reaction,
    "The reaction"
  )
  .def_property_readonly(

    "quantum_numbers",
    &Component::quantumNumbers,
    "The quantum numbers"
  )
  .def_property_readonly(

    "partial",
    &Component::partial,
    "The partial number (if defined)"
  )
  .def_property_readonly(

    "symbol",
    &Component::symbol,
    "The channel identifier's symbol"
  )
  .def(

    "__hash__",
    [] ( const Component& self ) { return std::hash< Component >{}( self ); },
    "Hash function"
  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );

  // add standard print definitions
  addStandardPrintDefinitions< Component >( component );
}

} // namespace id