// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/id/ReactionType.hpp"
#include "njoy/dryad/InteractionType.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
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
    "The reaction types, with associated symbol, aliases, particles, etc.\n\n"
    "The ReactionType can be used to identify reaction types. For the moment, only\n"
    "registered types can be used. In the future, we will extend this so that users\n"
    "can create types other than the ones currently registered.\n\n"
    "For more information on how to create instances of ReactionType, see the\n"
    "Jupyter notebook dryad-identifiers.ipynb under python/examples.\n\n"
    "Parameters\n"
    "----------\n"
    "    mt : int\n"
    "         the mt number\n"
    "    projectile : njoy.dryad.id.ParticleID\n"
    "         the projectile\n"
    "    level : int, default=0\n"
    "         the level number of the target or residual\n"
    "    particles : dict\n"
    "         the outgoing particles (excluding the residual)\n"
    "    string : str\n"
    "         the reaction type string"
  );

  // wrap the component
  component
  .def(

    python::init< int >(),
    python::arg( "mt" ),
    "Initialise the reaction type using an mt number"
  )
  .def(

    python::init< ParticleID, int, int >(),
    python::arg( "projectile" ), python::arg( "mt" ),
    python::arg( "level" ) = 0,
    "Initialise the reaction type using a projectile and level number"
  )
  .def(

    python::init< std::map< ParticleID, short >, int >(),
    python::arg( "particles" ), python::arg( "level" ),
    "Initialise the reaction type using outgoing particles and a level"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "string" ),
    "Initialise the reaction type from a string"
  )
  .def_static(

    "total",
    &Component::total,
    python::arg( "type" ) = InteractionType::Nuclear,
    "The total reaction type\n\n"
    "Parameters\n"
    "----------\n"
    "    type : njoy.dryad.InteractionType, default=InteractionType.Nuclear\n"
    "         the interaction type (nuclear or atomic)"
  )
  .def_static(

    "elastic",
    &Component::elastic,
    python::arg( "projectile" ),
    python::arg( "level" ) = 0,
    "The elastic reaction type\n\n"
    "Parameters\n"
    "----------\n"
    "    projectile : njoy.dryad.id.ParticleID\n"
    "         the projectile\n"
    "    level : int, default=0\n"
    "         the level number of the target"
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
    "The reaction type's mt number"
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
    "Parameters\n"
    "----------\n"
    "    projectile : njoy.dryad.id.ParticleID\n"
    "         the projectile\n"
    "    target : njoy.dryad.id.ParticleID\n"
    "         the target"
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
