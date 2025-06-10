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
  using Component = njoy::dryad::id::NewReactionID;
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
    "Initialise the reaction type\n\n"
    "Arguments:\n"
    "    self     the reaction identifier\n"
    "    symbol   the reaction symbol"
  )
  .def_static(

    "size",
    &Component::size,
    "The number of currently registered identifiers"
  )
  .def_property_readonly(

    "interaction_type",
    &Component::interactionType,
    "The interaction type (nuclear or atomic) associated to the reaction"
  )
  .def_property_readonly(

    "reaction_type",
    &Component::reactionType,
    "The reaction type (nuclear or atomic) associated to the reaction"
  )
  .def_property_readonly(

    "symbol",
    &Component::symbol,
    "The reaction type's symbol"
  );

  // add standard comparison definitions
  addStandardComparisonDefinitions< Component >( component );

  // add standard print definitions
  addStandardPrintDefinitions< Component >( component );
}

} // namespace id