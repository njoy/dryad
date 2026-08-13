// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/MultigroupProjectileTarget.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapMultigroupProjectileTarget( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::MultigroupProjectileTarget;
  using Documentation = njoy::dryad::Documentation;
  using ParticleID = njoy::dryad::id::ParticleID;
  using ReactionID = njoy::dryad::id::ReactionID;
  using MultigroupReaction = njoy::dryad::MultigroupReaction;
  using CovarianceData = njoy::dryad::covariance::CovarianceData;
  using InteractionType = njoy::dryad::InteractionType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "MultigroupProjectileTarget",
    "The multigroup data associated to a given projectile and target\n\n"
    "Parameters\n"
    "----------\n"
    "    documentation : njoy.dryad.Documentation, optional\n"
    "        the documentation\n"
    "    projectile : njoy.dryad.id.ParticleID\n"
    "        the projectile identifier\n"
    "    target : njoy.dryad.id.ParticleID\n"
    "        the target identifier\n"
    "    type : njoy.dryad.InteractionType\n"
    "        the interaction type\n"
    "    reactions : list of njoy.dryad.MultigroupReaction\n"
    "        the reaction data\n"
    "    covariances : njoy.dryad.covariance.CovarianceData, default None\n"
    "        the optional covariance data"
  );

  // wrap the component
  component
  .def(

    python::init< Documentation,
                  ParticleID,
                  ParticleID,
                  InteractionType,
                  std::vector< MultigroupReaction >,
                  std::optional< CovarianceData > >(),
    python::arg( "documentation" ), python::arg( "projectile" ),
    python::arg( "target" ), python::arg( "type" ),
    python::arg( "reactions" ),
    python::arg( "covariances" ) = std::nullopt,
    "Initialise the MultigroupProjectileTarget with documentation"
  )
  .def(

    python::init< ParticleID,
                  ParticleID,
                  InteractionType,
                  std::vector< MultigroupReaction >,
                  std::optional< CovarianceData > >(),
    python::arg( "projectile" ),
    python::arg( "target" ),
    python::arg( "type" ),
    python::arg( "reactions" ),
    python::arg( "covariances" ) = std::nullopt,
    "Initialise the MultigroupProjectileTarget without documentation"
  )
  .def_property(

    "documentation",
    python::overload_cast<>( &Component::documentation, python::const_ ),
    python::overload_cast< Documentation >( &Component::documentation ),
    "The documentation"
  )
  .def_property(

    "projectile_identifier",
    python::overload_cast<>( &Component::projectileIdentifier, python::const_ ),
    python::overload_cast< ParticleID >( &Component::projectileIdentifier ),
    "The projectile identifier"
  )
  .def_property(

    "target_identifier",
    python::overload_cast<>( &Component::targetIdentifier, python::const_ ),
    python::overload_cast< ParticleID >( &Component::targetIdentifier ),
    "The target identifier"
  )
  .def_property(

    "interaction_type",
    python::overload_cast<>( &Component::interactionType, python::const_ ),
    python::overload_cast< InteractionType >( &Component::interactionType ),
    "The interaction type (atomic or nuclear)"
  )
  .def_property(

    "reactions",
    python::overload_cast<>( &Component::reactions, python::const_ ),
    python::overload_cast< std::vector< MultigroupReaction > >( &Component::reactions ),
    "The reactions"
  )
  .def_property_readonly(

    "number_reactions",
    &Component::numberReactions,
    "The number of reactions"
  )
  .def(

    "has_reaction",
    &Component::hasReaction,
    python::arg( "id" ),
    "Return whether or not a reaction is present\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ReactionID\n"
    "        the reaction identifier"
  )
  .def(

    "reaction",
    python::overload_cast< const ReactionID& >( &Component::reaction, python::const_ ),
    python::arg( "id" ),
    "Return the requested reaction\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ReactionID\n"
    "        the reaction identifier",
    python::return_value_policy::reference_internal
  )
  .def_property(

    "covariance_data",
    python::overload_cast<>( &Component::covarianceData, python::const_ ),
    python::overload_cast< std::optional< CovarianceData > >( &Component::covarianceData ),
    "The covariance data"
  )
  .def(

    "calculate_summation_cross_sections",
    &Component::calculateSummationCrossSections,
    "Calculate summation cross sections\n\n"
    "This function recalculates the cross section of all summation reactions\n"
    "by summing the cross sections of the partials together. The partials are\n"
    "assumed to share the same group structure as the summation reaction."
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
