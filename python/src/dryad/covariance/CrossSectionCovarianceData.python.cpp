// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/covariance/CrossSectionCovarianceData.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

void wrapCrossSectionCovarianceData( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::CrossSectionCovarianceData;
  using ReactionID = njoy::dryad::id::ReactionID;
  using CrossSectionCovarianceMatrix = njoy::dryad::covariance::CrossSectionCovarianceMatrix;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CrossSectionCovarianceData",
    "The cross section covariance data\n\n"
    "Parameters\n"
    "----------\n"
    "    matrices : list of njoy.dryad.covariance. \n"
    "         the covariance matrices"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< CrossSectionCovarianceMatrix > >(),
    python::arg( "matrices" ),
    "Initialise the covariance data\n"
  )
  .def_property_readonly(

    "number_reactions",
    &Component::numberReactions,
    "The number of reactions for which covariance data is available"
  )
  .def_property_readonly(

    "number_covariance_matrices",
    &Component::numberCovarianceMatrices,
    "The number of covariance blocks"
  )
  .def_property_readonly(

    "reaction_identifiers",
    &Component::reactionIdentifiers,
    "The reaction identifiers for which covariance data is available"
  )
  .def_property_readonly(

    "covariances",
    &Component::covariances,
    "The covariance data"
  )
  .def(

    "has_covariance_matrix",
    python::overload_cast< const ReactionID&, const ReactionID& >( &Component::hasCovarianceMatrix, python::const_ ),
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
    python::overload_cast< const ReactionID& >( &Component::hasCovarianceMatrix, python::const_ ),
    python::arg( "id" ),
    "Return whether or not a given reaction has covariance data\n\n"
    "Parameters\n"
    "----------\n"
    "    id : njoy.dryad.id.ReactionID\n"
    "         the reaction identifier"
  )
  .def(

    "covariance_matrix",
    python::overload_cast< const ReactionID&, const ReactionID& >( &Component::covarianceMatrix, python::const_ ),
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
    python::overload_cast< const ReactionID& >( &Component::covarianceMatrix, python::const_ ),
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
