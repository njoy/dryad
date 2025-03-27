// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/covariance/CrossSectionMetadata.hpp"

// namespace aliases
namespace python = pybind11;

namespace covariance {

void wrapCrossSectionMetadata( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::CrossSectionMetadata;
  using ParticleID = njoy::dryad::id::ParticleID;
  using ReactionID = njoy::dryad::id::ReactionID;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CrossSectionMetadata",
    "Metadata for the rows or columns of a covariance matrix block for "
    "cross section data"
  );

  // wrap the component
  component
  .def(

    python::init< ParticleID, ParticleID, ReactionID, std::vector< double > >(),
    python::arg( "projectile" ), python::arg( "target" ),
    python::arg( "reaction" ), python::arg( "energies" ),
    "Initialise the meta data\n\n"
    "Arguments:\n"
    "    self         the meta data\n"
    "    projectile   the projectile identifier\n"
    "    target       the target identifier\n"
    "    reaction     the reaction identifier\n"
    "    energies     the energy boundaries"
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

    "reaction_identifier",
    &Component::reactionIdentifier,
    "The reaction identifier"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy boundaries"
  )
  .def_property_readonly(

    "number_groups",
    &Component::numberGroups,
    "The number of energy groups"
  );
}

} // covariance namespace
