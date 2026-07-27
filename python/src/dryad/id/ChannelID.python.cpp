// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/id/ChannelID.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
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
    "ordering.\n\n"
    "Parameters\n"
    "----------\n"
    "    reaction : njoy.dryad.id.ReactionID\n"
    "        the reaction\n"
    "    quantum_numbers : njoy.dryad.resonances.ChannelQuantumNumbers\n"
    "        the channel quantum numbers\n"
    "    partial : int, optional\n"
    "        the optional partial index\n"
    "    symbol : str\n"
    "        the channel symbol"
  );

  // wrap the component
  component
  .def(

    python::init< const ReactionID&, const ChannelQuantumNumbers&,
                  const std::optional< std::size_t >& >(),
    python::arg( "reaction" ), python::arg( "quantum_numbers" ),
    python::arg( "partial" ) = std::nullopt,
    "Initialise the channel identifier with a reaction and quantum numbers"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "symbol" ),
    "Initialise the channel identifier from a symbol string"
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

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // namespace id
} // dryad namespace
