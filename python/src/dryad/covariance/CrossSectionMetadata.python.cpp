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
    "Covariance metadata for cross sections\n\n"
    "Parameters\n"
    "----------\n"
    "    reactions : list of njoy.dryad.id.ReactionID\n"
    "         the reaction identifiers\n"
    "    reaction : njoy.dryad.id.ReactionID\n"
    "         the reaction identifier (single reaction constructor)\n"
    "    energies : list of float\n"
    "         the energy boundary values\n"
    "    keys : list of tuple\n"
    "         the metadata keys (tuples of ReactionID, EnergyGroup)"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< ReactionID >,
                  std::vector< double > >(),
    python::arg( "reactions" ),
    python::arg( "energies" ),
    "Initialise the cross section covariance metadata"
  )
  .def(

    python::init< ReactionID,
                  std::vector< double > >(),
    python::arg( "reaction" ), 
    python::arg( "energies" ),
    "Initialise the cross section covariance metadata for a single reaction"
  )
  .def(

    python::init< std::vector< Key > >(),
    python::arg( "keys" ),
    "Initialise the cross section covariance metadata with metadata keys"
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

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // covariance namespace
} // dryad namespace
