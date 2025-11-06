// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/covariance/CrossSectionMetadata.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

void wrapCrossSectionMetadata( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::CrossSectionMetadata;
  using EnergyGroup = njoy::dryad::id::EnergyGroup;
  using ReactionID = njoy::dryad::id::ReactionID;
  using Key = std::tuple< ReactionID, EnergyGroup >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CrossSectionMetadata",
    "Covariance metadata for cross sections"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< ReactionID >,
                  std::vector< double > >(),
    python::arg( "reactions" ), python::arg( "energies" ),
    "Initialise the product multiplicity covariance metadata\n\n"
    "Arguments:\n"
    "    self          the covariance metadata\n"
    "    reactions     the reaction identifiers\n"
    "    energies      the group structure"
  )
  .def(

    python::init< std::vector< Key > >(),
    python::arg( "keys" ),
    "Initialise the product multiplicity covariance metadata\n\n"
    "Arguments:\n"
    "    self   the covariance metadata\n"
    "    keys   the metadata keys"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "reaction_identifiers",
    &Component::reactionIdentifiers,
    "The reaction identifiers"
  )
  .def_property_readonly(

    "energies",
    &Component::energies,
    "The energy group boundaries"
  )
  .def_property_readonly(

    "keys",
    [] ( Component& self ) -> decltype(auto)
       { return self.keys(); },
    "The metadata keys"
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );
}

} // covariance namespace
} // dryad namespace
