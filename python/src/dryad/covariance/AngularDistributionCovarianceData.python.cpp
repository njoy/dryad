// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/covariance/AngularDistributionCovarianceData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

void wrapAngularDistributionCovarianceData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::AngularDistributionCovarianceData;
  using ReactionID = njoy::dryad::id::ReactionID;
  using AngularDistributionCovarianceMatrix = njoy::dryad::covariance::AngularDistributionCovarianceMatrix;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "AngularDistributionCovarianceData",
    "The angular distribution covariance data\n\n"
    "Parameters\n"
    "----------\n"
    "    matrices : list of njoy.dryad.covariance.AngularDistributionCovarianceData \n"
    "         the covariance matrices"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< AngularDistributionCovarianceMatrix > >(),
    python::arg( "matrices" ),
    "Initialise the covariance data\n"
  )
  .def_property_readonly(

    "number_reactions",
    [] ( const Component& self ) -> decltype(auto)
       { return self.numberReactions(); },
    "The number of reactions for which covariance data is available"
  )
  .def_property_readonly(

    "number_covariance_matrices",
    [] ( const Component& self ) -> decltype(auto)
       { return self.numberCovarianceMatrices(); },
    "The number of covariance blocks"
  )
  .def_property_readonly(

    "reaction_identifiers",
    [] ( const Component& self ) -> decltype(auto)
       { return self.reactionIdentifiers(); },
    "The reaction identifiers for which covariance data is available"
  )
  .def_property_readonly(

    "covariances",
    [] ( const Component& self ) -> decltype(auto)
       { return self.covariances(); },
    "The covariance data"
  )
  .def(

    "has_covariance_matrix",
    [] ( const Component& self, const ReactionID& row, const ReactionID& column ) -> decltype(auto)
       { return self.hasCovarianceMatrix( row, column ); },
    python::arg( "row" ), python::arg( "column" ),
    "Return whether or not a given reaction pair has covariance data\n\n"
    "Parameters\n"
    "----------\n"
    "    row : njoy.dryad.id.ReactionID\n"
    "         the row reaction identifier\n"
    "    column : njoy.dryad.id.ReactionID\n"
    "         the column reaction identifier"
  )
  .def(

    "has_covariance_matrix",
    [] ( const Component& self, const ReactionID& id ) -> decltype(auto)
       { return self.hasCovarianceMatrix( id ); },
    python::arg( "id" ),
    "Return whether or not a given reaction has covariance data\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ReactionID\n"
    "         the reaction identifier"
  )
  .def(

    "covariance_matrix",
    [] ( const Component& self, const ReactionID& row, const ReactionID& column ) -> decltype(auto)
       { return self.covarianceMatrix( row, column ); },
    python::arg( "row" ), python::arg( "column" ),
    "Return the covariance data for a row and column reaction pair\n\n"
    "Parameters\n"
    "----------\n"
    "    row : njoy.dryad.id.ReactionID\n"
    "         the row reaction identifier\n"
    "    column : njoy.dryad.id.ReactionID\n"
    "         the column reaction identifier",
    python::return_value_policy::reference_internal
  )
  .def(

    "covariance_matrix",
    [] ( const Component& self, const ReactionID& id ) -> decltype(auto)
       { return self.covarianceMatrix( id ); },
    python::arg( "id" ),
    "Return the covariance data for a reaction\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ReactionID\n"
    "         the reaction identifier",
    python::return_value_policy::reference_internal
  );

  // add standard equality comparison definitions
  addStandardEqualityComparisonDefinitions< Component >( component );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // covariance namespace
} // dryad namespace
