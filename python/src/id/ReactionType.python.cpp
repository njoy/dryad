// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/id/ReactionType.hpp"
#include "dryad/InteractionType.hpp"

// namespace aliases
namespace python = pybind11;

namespace id {

void wrapReactionType( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ReactionType;
  using ParticleID = njoy::dryad::id::ParticleID;
  using InteractionType = njoy::dryad::InteractionType;

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
    python::arg( "mt" ),
    "Initialise the reaction type\n\n"
    "Arguments:\n"
    "    self   the reaction type\n"
    "    mt     the mt number"
  )
  .def(

    python::init< ParticleID, int, int >(),
    python::arg( "projectile" ), python::arg( "mt" ),
    python::arg( "level" ) = 0,
    "Initialise the reaction type\n\n"
    "Arguments:\n"
    "    self         the reaction type\n"
    "    projectile   the projectile\n"
    "    mt           the mt number\n"
    "    level        the level number of the target (default = 0)"
  )
  .def(

    python::init< std::map< ParticleID, short >, int >(),
    python::arg( "particles" ), python::arg( "level" ),
    "Initialise the reaction type\n\n"
    "Arguments:\n"
    "    self        the reaction type\n"
    "    particles   the outgoing particles (excluding the residual)\n"
    "    level       the level number of the residual"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the reaction type\n\n"
    "Arguments:\n"
    "    self     the reaction type\n"
    "    string   the reaction type string"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_static(

    "total",
    &Component::total,
    python::arg( "type" ) = InteractionType::Nuclear,
    "The total reaction type\n\n"
    "Arguments:\n"
    "    type   the interaction type (nuclear or atomic)"
  )
  .def_static(

    "elastic",
    &Component::elastic,
    python::arg( "projectile" ),
    python::arg( "level" ) = 0,
    "The elastic reaction type\n\n"
    "Arguments:\n"
    "    projectile   the projectile\n"
    "    level.       the level number of the target (default = 0)"
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

    "is_compatible_with_endf",
    &Component::isCompatibleWithENDF,
    "Flag to indicate whether or not the reaction type is compatible with ENDF"
  )
  .def(

    "resolve",
    &Component::resolve,
    python::arg( "projectile" ), python::arg( "target" ),
    "Return the residual produced by this reaction type\n\n"
    "Arguments:\n"
    "    self         the reaction type\n"
    "    projectile   the projectile\n"
    "    target       the target"
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