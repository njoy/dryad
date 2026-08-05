// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/format/ace/read/createProjectileTargetFromFile.hpp"
#include "njoy/format/endf/read/createProjectileTargetFromFile.hpp"
#include "njoy/format/endf/write/createProjectileTargetFile.hpp"
#include "njoy/format/gnds/StyleType.hpp"
#include "njoy/format/gnds/read/createProjectileTargetFromFile.hpp"
#include "njoy/format/gnds/write/createProjectileTargetFile.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {

void wrapProjectileTarget( python::module& module ) {

  // constants
  std::ostringstream integration_tolerance;
  integration_tolerance << std::setprecision( 1 ) << njoy::constants::integration::tolerance;
  std::ostringstream linearisation_tolerance;
  linearisation_tolerance << std::setprecision( 4 ) << njoy::constants::linearisation::tolerance;

  // type aliases
  using Component = njoy::dryad::ProjectileTarget;
  using Documentation = njoy::dryad::Documentation;
  using ParticleID = njoy::dryad::id::ParticleID;
  using ReactionID = njoy::dryad::id::ReactionID;
  using Reaction = njoy::dryad::Reaction;
  using ParticleDatabase = njoy::dryad::ParticleDatabase;
  using ResonanceParameters = njoy::dryad::resonances::ResonanceParameters;
  using CovarianceData = njoy::dryad::covariance::CovarianceData;
  using InteractionType = njoy::dryad::InteractionType;
  using StyleType = njoy::format::gnds::StyleType;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ProjectileTarget",
    "Data associated to a given projectile and target\n\n"
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
    "    reactions : list of njoy.dryad.Reaction\n"
    "        the reaction data\n"
    "    particles : njoy.dryad.ParticleDatabase, default None\n"
    "        the optional particle data\n"
    "    resonances : njoy.dryad.resonances.ResonanceParameters, default None\n"
    "        the optional resonance parameters\n"
    "    covariances : njoy.dryad.covariance.CovarianceData, default None\n"
    "        the optional covariance data\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data"
  );

  // wrap the component
  component
  .def(

    python::init< Documentation,
                  ParticleID,
                  ParticleID,
                  InteractionType,
                  std::vector< Reaction >,
                  std::optional< ParticleDatabase >,
                  std::optional< ResonanceParameters >,
                  std::optional< CovarianceData >,
                  bool >(),
    python::arg( "documentation" ), python::arg( "projectile" ),
    python::arg( "target" ), python::arg( "type" ),
    python::arg( "reactions" ),
    python::arg( "particles" ) = std::nullopt,
    python::arg( "resonances" ) = std::nullopt,
    python::arg( "covariances" ) = std::nullopt,
    python::arg( "normalise" ) = false,
    "Initialise the ProjectileTarget with documentation"
  )
  .def(

    python::init< ParticleID,
                  ParticleID,
                  InteractionType,
                  std::vector< Reaction >,
                  std::optional< ParticleDatabase >,
                  std::optional< ResonanceParameters >,
                  std::optional< CovarianceData >,
                  bool >(),
    python::arg( "projectile" ),
    python::arg( "target" ),
    python::arg( "type" ),
    python::arg( "reactions" ),
    python::arg( "particles" ) = std::nullopt,
    python::arg( "resonances" ) = std::nullopt,
    python::arg( "covariances" ) = std::nullopt,
    python::arg( "normalise" ) = false,
    "Initialise the ProjectileTarget without documentation"
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

    "particle_data",
    python::overload_cast<>( &Component::particleData, python::const_ ),
    python::overload_cast< std::optional< ParticleDatabase > >( &Component::particleData ),
    "The particle data"
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

    "calculate_average_energy",
    &Component::calculateAverageEnergy,
    python::arg( "tolerance" ) = njoy::constants::integration::tolerance,
    std::string( "Calculate average outgoing energies for all reaction products\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    tolerance : float, default " + integration_tolerance.str() + "\n"
                 "        the integration tolerance" ).c_str()
  )
  .def(

    "unionise_cross_sections",
    &Component::unioniseCrossSections,
    python::arg( "exclude_summation" ) = false,
    "Unionise cross section data\n\n"
    "This function takes all cross section data and unionises the cross section\n"
    "grids. It does not linearise the data but reevaluates the data using the\n"
    "proper interpolation types of the cross section data.\n\n"
    "By default, summation cross sections are included in the unionisation process\n"
    "unless explicitly excluded by the user. Switching on the exclusion of summation\n"
    "cross sections may be useful when the user is going to recalculate the summation\n"
    "cross sections after unionisation.\n\n"
    "Parameters\n"
    "----------\n"
    "    exclude_summation : bool, default False\n"
    "        option to exclude summation reactions in the unionisation"
  )
  .def(

    "calculate_summation_cross_sections",
    &Component::calculateSummationCrossSections,
    python::arg( "tolerance" ) = njoy::constants::linearisation::tolerance,
    std::string( "Calculate summation cross sections\n\n"
                 "Parameters\n"
                 "----------\n"
                 "    tolerance : float, default " + linearisation_tolerance.str() + "\n"
                 "        the linearisation tolerance" ).c_str()
  )
  .def(

    "normalise",
    &Component::normalise,
    "Normalise the distribution data"
  )
  .def_static(

    "from_endf_file",
    [] ( const std::string& filename, bool normalise ) -> decltype(auto) {

      return njoy::format::endf::read::createProjectileTargetFromFile( filename, normalise );
    },
    python::arg( "filename" ),
    python::arg( "normalise" ) = false,
    "Create ProjectileTarget data from an ENDF file\n\n"
    "If there are multiple materials in the ENDF file, only the first material\n"
    "will be transformed into a ProjectileTarget.\n\n"
    "Parameters\n"
    "----------\n"
    "    filename : str\n"
    "        the ENDF file name\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data"
  )
  .def_static(

    "from_gnds_file",
    [] ( const std::string& filename, bool normalise, const StyleType& style ) -> decltype(auto) {

      return njoy::format::gnds::read::createProjectileTargetFromFile( filename, normalise, style );
    },
    python::arg( "filename" ),
    python::arg( "normalise" ) = false,
    python::arg( "style" ) = StyleType::Evaluation,
    "Create ProjectileTarget data from a GNDS file\n\n"
    "Parameters\n"
    "----------\n"
    "    filename : str\n"
    "        the GNDS file name\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data"
  )
  .def_static(

    "from_ace_file",
    [] ( const std::string& filename, bool normalise ) -> decltype(auto) {

      return njoy::format::ace::read::createProjectileTargetFromFile( filename, normalise );
    },
    python::arg( "filename" ), python::arg( "normalise" ) = false,
    "Create ProjectileTarget data from an ACE file\n\n"
    "Most files will produce a single ProjectileTarget. The exception here is the\n"
    "photoatomic ACE file which may yield one ProjectileTarget (pre-eprdata) or two\n"
    "ProjectileTarget for eprdata files.\n\n"
    "Parameters\n"
    "----------\n"
    "    filename : str\n"
    "        the ACE file name\n"
    "    normalise : bool, default False\n"
    "        option to indicate whether or not to normalise\n"
    "        all probability data"
  )
  .def(

    "to_endf_file",
    [] ( const Component& self,
         int mat,
         const std::string& filename,
         bool use_reduced_width_amplitudes ) {

      njoy::format::endf::write::createProjectileTargetFile( self, mat, filename,
                                                             use_reduced_width_amplitudes );
    },
    python::arg( "mat" ), python::arg( "filename" ),
    python::arg( "use_reduced_width_amplitudes" ) = true,
    "Write the ProjectileTarget data to an ENDF file\n\n"
    "Parameters\n"
    "----------\n"
    "    mat : int\n"
    "        the ENDF mat number to be used\n"
    "    filename : str\n"
    "        the ENDF file name\n"
    "    use_reduced_width_amplitudes : bool, default True\n"
    "        if there are resonances, use reduced width amplitudes"
  )
  .def(

    "to_gnds_file",
    [] ( const Component& self,
         const std::string& filename,
         const StyleType& style,
         bool use_reduced_width_amplitudes ) {

      njoy::format::gnds::write::createProjectileTargetFile( self, filename, style,
                                                             use_reduced_width_amplitudes );
    },
    python::arg( "filename" ),
    python::arg( "style" ) = StyleType::Evaluation,
    python::arg( "use_reduced_width_amplitudes" ) = true,
    "Write the ProjectileTarget data to an ENDF file\n\n"
    "Parameters\n"
    "----------\n"
    "    filename : str\n"
    "        the ENDF file name\n"
    "    style : str\n"
    "        the GNDS style name\n"
    "    use_reduced_width_amplitudes : bool, default True\n"
    "        if there are resonances, use reduced width amplitudes"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // dryad namespace
