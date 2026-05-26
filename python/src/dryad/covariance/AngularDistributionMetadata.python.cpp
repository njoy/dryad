// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/covariance/AngularDistributionMetadata.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

void wrapAngularDistributionMetadata( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::AngularDistributionMetadata;
  using EnergyGroup = njoy::dryad::id::EnergyGroup;
  using ReactionID = njoy::dryad::id::ReactionID;
  using Key = std::tuple< ReactionID, std::size_t, EnergyGroup >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "AngularDistributionMetadata",
    "Covariance metadata for angular distributions"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< ReactionID >,
                  std::vector< std::size_t >,
                  std::vector< double > >(),
    python::arg( "reactions" ), 
    python::arg( "moments" ),
    python::arg( "energies" ),
    "Initialise the angular distribution covariance metadata\n\n"
    "Arguments:\n"
    "    self          the covariance metadata\n"
    "    reactions     the reaction identifiers\n"
    "    moments       the Legendre moments\n"
    "    energies      the group structure"
  )
  .def(

    python::init< std::vector< Key > >(),
    python::arg( "keys" ),
    "Initialise the angular distribution covariance metadata\n\n"
    "Arguments:\n"
    "    self   the covariance metadata\n"
    "    keys   the metadata keys"
  )
  .def_property_readonly(

    "reaction_identifiers",
    &Component::reactionIdentifiers,
    "The reaction identifiers"
  )
  .def_property_readonly(

    "moments",
    &Component::moments,
    "The Legendre moments"
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
