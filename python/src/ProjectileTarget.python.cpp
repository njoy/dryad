// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/ProjectileTarget.hpp"
#include "dryad/format/endf/createProjectileTargetFromFile.hpp"

// namespace aliases
namespace python = pybind11;

void wrapProjectileTarget( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::dryad::ProjectileTarget;
  using ParticleID = njoy::dryad::ParticleID;
  using Reaction = njoy::dryad::Reaction;
  using ToleranceConvergence = njoy::dryad::ToleranceConvergence;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ProjectileTarget",
    "A data associated to a given projectile and target"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID, ParticleID, std::vector< Reaction > >(),
    python::arg( "projectile" ), python::arg( "target" ),
    python::arg( "reactions" ),
    "Initialise the ProjectileTarget\n\n"
    "Arguments:\n"
    "    self         the reaction\n"
    "    projectile   the particle identifier\n"
    "    target       the target identifier\n"
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

    "reactions",
    &Component::reactions,
    "The reactions"
  )
  .def_property_readonly(

    "is_linearised",
    &Component::isLinearised,
    "Flag indicating whether or not the data is linearised"
  )
  .def(

    "linearise",
    [] ( const Component& self, const ToleranceConvergence& tolerance )
       { return self.linearise( tolerance ); },
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the data and return a new object\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    tolerance   the linearisation tolerance"
  )
  .def(

    "linearise_inplace",
    [] ( Component& self, const ToleranceConvergence& tolerance )
       { return self.lineariseInplace( tolerance ); },
    python::arg( "tolerance" ) = ToleranceConvergence(),
    "Linearise the data inplace\n\n"
    "Arguments:\n"
    "    self        the reaction\n"
    "    tolerance   the linearisation tolerance"
  )
  .def_static(

    "from_endf_file",
    [] ( const std::string& filename ) -> Component {

      return njoy::dryad::format::endf::createProjectileTargetFromFile( filename );
    },
    python::arg( "filename" ),
    "Create a ProjectileTarget from an ENDF file\n\n"
    "If there are multiple materials in the ENDF file, only the first material\n"
    "will be transformed into a ProjectileTarget.\n\n"
    "Arguments:\n"
    "    filename   the ENDF file name"
  );
}
