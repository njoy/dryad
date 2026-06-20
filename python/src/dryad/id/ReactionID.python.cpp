// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/id/ReactionID.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace id {

void wrapReactionID( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::id::ReactionID;
  using ParticleID = njoy::dryad::id::ParticleID;
  using ReactionType = njoy::dryad::id::ReactionType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ReactionID",
    "The reaction identifier, with associated symbols, aliases, particles, etc.\n\n"
    "Parameters\n"
    "----------\n"
    "    projectile : njoy.dryad.id.ParticleID\n"
    "        the projectile\n"
    "    target : njoy.dryad.id.ParticleID\n"
    "        the target\n"
    "    type : njoy.dryad.id.ReactionType or int or str\n"
    "        the reaction type, mt number, or string representing the reaction type\n"
    "    symbol : str\n"
    "        the reaction symbol"
  );

  // wrap the component
  component
  .def(

    python::init< const ParticleID&, const ParticleID&,
                  const ReactionType& >(),
    python::arg( "projectile" ), python::arg( "target" ),
    python::arg( "type" ),
    "Initialise the reaction identifier with a projectile, target and reaction type"
  )
  .def(

    python::init< const ParticleID&, const ParticleID&, int >(),
    python::arg( "projectile" ), python::arg( "target" ),
    python::arg( "mt" ),
    "Initialise the reaction identifier with a projectile, target and mt number"
  )
  .def(

    python::init< const ParticleID&, const ParticleID&,
                  const std::string& >(),
    python::arg( "projectile" ), python::arg( "target" ),
    python::arg( "type" ),
    "Initialise the reaction identifier with an reaction type string"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "symbol" ),
    "Initialise the reaction identifier from a symbol string"
  )
  .def_property_readonly(

    "projectile",
    &Component::projectile,
    "The projectile"
  )
  .def_property_readonly(

    "target",
    &Component::target,
    "The target"
  )
  .def_property_readonly(

    "particles",
    &Component::particles,
    "The outgoing particles (excluding the residual)"
  )
  .def_property_readonly(

    "residual",
    &Component::residual,
    "The residual"
  )
  .def_property_readonly(

    "mt",
    &Component::mt,
    "The reaction's mt number (if defined)"
  )
  .def_property_readonly(

    "is_compatible_with_endf",
    &Component::isCompatibleWithENDF,
    "Flag to indicate whether or not the reaction is compatible with ENDF"
  )
  .def_property_readonly(

    "interaction_type",
    &Component::interactionType,
    "The interaction type (nuclear or atomic) associated to the reaction"
  )
  .def_property_readonly(

    "reaction_type",
    &Component::reactionType,
    "The reaction type associated to the reaction"
  )
  .def_property_readonly(

    "symbol",
    &Component::symbol,
    "The reaction identifier's symbol"
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
