// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/id/ReactionType.hpp"

// namespace aliases
namespace python = pybind11;

namespace id {

void wrapReactionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ReactionType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ReactionType",
    "The reaction type\n\n"
    "The ReactionType can be used to identify reaction types. For the moment, only\n"
    "registered types can be used. In the future, we will extend this so that users\n"
    "can create types other than the ones currently registered.\n\n"
    "For more information on how to create instances of ReactionType, see the\n"
    "Jupyter notebook dryad-identifiers.ipynb under python/examples."
  );

  // wrap the component
  component
  .def(

    python::init< int >(),
    python::arg( "mt" ) = 0,
    "Initialise the reaction type\n\n"
    "Arguments:\n"
    "    self   the identifier\n"
    "    mt     the mt number"
     )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the reaction type\n\n"
    "Arguments:\n"
    "    self     the identifier\n"
    "    string   the reaction type string"
  )
  .def_static(

    "size",
    &Component::size,
    "The number of currently registered types"
  )
  .def_property_readonly(

    "interaction_type",
    &Component::interactionType,
    "The interaction type (nuclear or atomic) associated to the reaction type"
  )
  .def_property_readonly(

    "mt",
    &Component::mt,
    "The interaction type's mt number"
  )
  .def_property_readonly(

    "symbol",
    &Component::symbol,
    "The reaction type's symbol"
  )
  .def_property_readonly(

    "particles",
    &Component::particles,
    "The reaction type's outgoing particles"
  )
  .def_property_readonly(

    "level",
    &Component::level,
    "The level or subshell number for the residual"
  )
  .def_property_readonly(

    "is_special",
    &Component::isSpecial,
    "Flag to indicate whether or not the reaction type is considered a special type\n\n"
    "A special type is a reaction type for which no outgoing particles types can be\n"
    "defined because it is a summation reaction or because the outgoing particles\n"
    "are not known due to complexity (e.g. anything or fission)"
  )
  .def_property_readonly(

    "is_endf_compatible",
    &Component::isCompatibleWithENDF,
    "Flag to indicate whether or not the reaction type is compatible with ENDF"
  )
  .def(

    "__hash__",
    [] ( const Component& self ) { return self.number(); },
    "Hash function"
  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );

  // add standard print definitions
  addStandardPrintDefinitions< Component >( component );
}

} // namespace id