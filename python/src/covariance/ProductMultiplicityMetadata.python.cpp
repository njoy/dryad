// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "definitions.hpp"
#include "dryad/covariance/ProductMultiplicityMetadata.hpp"

// namespace aliases
namespace python = pybind11;

namespace covariance {

void wrapProductMultiplicityMetadata( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::ProductMultiplicityMetadata;
  using ParticleID = njoy::dryad::id::ParticleID;
  using EnergyGroup = njoy::dryad::id::EnergyGroup;
  using ReactionID = njoy::dryad::id::ReactionID;
  using Key = std::tuple< ReactionID, EnergyGroup, ParticleID >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ProductMultiplicityMetadata",
    "Covariance metadata for product multiplicities"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< ReactionID >,
                  std::vector< double >,
                  std::vector< ParticleID > >(),
    python::arg( "reactions" ), python::arg( "energies" ),
    python::arg( "products" ),
    "Initialise the product multiplicity covariance metadata\n\n"
    "Arguments:\n"
    "    self          the covariance matrix\n"
    "    reactions     the reaction identifiers\n"
    "    energies      the group structure\n"
    "    products      the product identifiers"
  )
  .def(

    python::init< std::vector< Key > >(),
    python::arg( "keys" ),
    "Initialise the product multiplicity covariance metadata\n\n"
    "Arguments:\n"
    "    self   the covariance matrix\n"
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

    "product_identifiers",
    &Component::productIdentifiers,
    "The reaction product identifiers"
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
