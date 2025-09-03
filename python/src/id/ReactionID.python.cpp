// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

// local includes
#include "definitions.hpp"
#include "dryad/id/ReactionID.hpp"

// namespace aliases
namespace python = pybind11;

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
    "The reaction identifier"
  );

  // wrap the component
  component
  .def(

    python::init< const ParticleID&, const ParticleID&,
                  const ReactionType& >(),
    python::arg( "projectile" ), python::arg( "target" ),
    python::arg( "type" ),
    "Initialise the reaction identifier\n\n"
    "Arguments:\n"
    "    self         the reaction identifier\n"
    "    projectile   the projectile\n"
    "    target       the target\n"
    "    type         the reaction type"
  )
  .def(

    python::init< const std::string& >(),
    python::arg( "symbol" ),
    "Initialise the reaction identifier\n\n"
    "Arguments:\n"
    "    self     the reaction identifier\n"
    "    symbol   the reaction symbol"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
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
}

} // namespace id