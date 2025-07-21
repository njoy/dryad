// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "definitions.hpp"
#include "dryad/ProjectileTarget.hpp"
#include "dryad/format/ace/createProjectileTargetFromFile.hpp"
#include "dryad/format/endf/createProjectileTargetFromFile.hpp"
#include "dryad/format/gnds/createProjectileTargetFromFile.hpp"

// namespace aliases
namespace python = pybind11;

void wrapProjectileTarget( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::ProjectileTarget;
  using ParticleID = njoy::dryad::id::ParticleID;
  using Reaction = njoy::dryad::Reaction;
  using ResonanceParameters = njoy::dryad::resonances::ResonanceParameters;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;
  using InteractionType = njoy::dryad::InteractionType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ProjectileTarget",
    "Data associated to a given projectile and target"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID, ParticleID, InteractionType,
                  std::vector< Reaction > >(),
    python::arg( "projectile" ), python::arg( "target" ),
    python::arg( "type" ), python::arg( "reactions" ),
    "Initialise the ProjectileTarget\n\n"
    "Arguments:\n"
    "    self         the reaction\n"
    "    projectile   the particle identifier\n"
    "    target       the target identifier\n"
    "    type         the interaction type\n"
    "    reactions    the reaction data"
  )
  .def_property_readonly(

    "projectile_identifier",
    &Component::projectileIdentifier,
    "The projectile identifier"
  )
  .def_property_readonly(

    "target_identifier",
    &Component::targetIdentifier,
    "The target identifier"
  )
  .def_property_readonly(

    "interaction_type",
    &Component::interactionType,
    "The interaction type (atomic or nuclear)"
  )
  .def_property(

    "resonances",
    python::overload_cast<>( &Component::resonances, python::const_ ),
    python::overload_cast< std::optional< ResonanceParameters > >( &Component::resonances ),
    "The resonance parameters"
  )
  .def_property(

    "reactions",
    python::overload_cast<>( &Component::reactions, python::const_ ),
    python::overload_cast< std::vector< Reaction > >( &Component::reactions ),
    "The reactions"
  )
  .def(

    "has_reaction",
    &Component::hasReaction,
    python::arg( "id" ),
    "Return whether or not a reaction is present\n\n"
    "Arguments:\n"
    "    self   the ProjectileTarget data\n"
    "    id     the reaction identifier"
  )
  .def(

    "reaction",
    &Component::reaction,
    python::arg( "id" ),
    "Return the requested reaction\n\n"
    "Arguments:\n"
    "    self   the ProjectileTarget data\n"
    "    id     the reaction identifier",
    python::return_value_policy::reference_internal
  )
  .def(

    "calculate_summation_cross_sections",
    &Component::calculateSummationCrossSections,
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Calculate summation cross sections\n\n"
    "Arguments:\n"
    "    self        the ProjectileTarget data\n"
    "    tolerance   the linearisation tolerance"
  )
  .def_property_readonly(

    "is_linearised",
    &Component::isLinearised,
    "Flag indicating whether or not the data is linearised"
  )
  .def_static(

    "from_endf_file",
    [] ( const std::string& filename ) -> decltype(auto) {

      return njoy::dryad::format::endf::createProjectileTargetFromFile( filename );
    },
    python::arg( "filename" ),
    "Create ProjectileTarget data from an ENDF file\n\n"
    "If there are multiple materials in the ENDF file, only the first material\n"
    "will be transformed into a ProjectileTarget.\n\n"
    "Arguments:\n"
    "    filename   the ENDF file name"
  )
  .def_static(

    "from_gnds_file",
    [] ( const std::string& filename ) -> decltype(auto) {

      return njoy::dryad::format::gnds::createProjectileTargetFromFile( filename );
    },
    python::arg( "filename" ),
    "Create ProjectileTarget data from a GNDS file\n\n"
    "Arguments:\n"
    "    filename   the GNDS file name"
  )
  .def_static(

    "from_ace_file",
    [] ( const std::string& filename ) -> decltype(auto) {

      return njoy::dryad::format::ace::createProjectileTargetFromFile( filename );
    },
    python::arg( "filename" ),
    "Create ProjectileTarget data from an ACE file\n\n"
    "Most files will produce a single ProjectileTarget. The exception here is the\n"
    "photoatomic ACE file which may yield one ProjectileTarget (pre-eprdata) or two\n"
    "ProjectileTarget for eprdata files.\n\n"
    "Arguments:\n"
    "    filename   the ENDF file name"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}
