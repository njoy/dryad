// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"

// namespace aliases
namespace python = pybind11;

namespace covariance {

void wrapProductMultiplicityCovarianceMatrix( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;
  using ProductMultiplicityMetadata = njoy::dryad::covariance::ProductMultiplicityMetadata;
  using ParticleID = njoy::dryad::id::ParticleID;
  using EnergyGroup = njoy::dryad::id::EnergyGroup;
  using ReactionID = njoy::dryad::id::ReactionID;
  using Matrix = njoy::dryad::covariance::Matrix< double >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ProductMultiplicityCovarianceMatrix",
    "A covariance matrix for product multiplicities"
  );

  // wrap the component
  component
  .def(

    python::init< ProductMultiplicityMetadata, Matrix, bool >(),
    python::arg( "metadata" ), python::arg( "covariances" ),
    python::arg( "relative" ) = true,
    "Initialise an on-diagonal product multiplicity covariance matrix\n\n"
    "Arguments:\n"
    "    self          the covariance matrix\n"
    "    metadata      the row and column metadata\n"
    "    covariances   the covariance matrix\n"
    "    relative      the relative covariance flag (default is true)"
  )
  .def(

    python::init< ProductMultiplicityMetadata,
                  ProductMultiplicityMetadata,
                  Matrix, bool >(),
    python::arg( "row_metadata" ),
    python::arg( "column_metadata" ),
    python::arg( "covariances" ),
    python::arg( "relative" ) = true,
    "Initialise an off-diagonal product multiplicity covariance matrix\n\n"
    "Arguments:\n"
    "    self             the covariance matrix\n"
    "    row_metadata     the row metadata\n"
    "    column_metadata  the column metadata\n"
    "    covariances      the covariance matrix\n"
    "    relative         the relative covariance flag (default is true)"
  )
  .def(

    python::init< ProductMultiplicityMetadata,
                  std::vector< double >, Matrix, bool >(),
    python::arg( "metadata" ), python::arg( "deviations" ),
    python::arg( "correlations" ), python::arg( "relative" ) = true,
    "Initialise an on-diagonal product multiplicity correlation matrix\n\n"
    "Arguments:\n"
    "    self           the covariance matrix\n"
    "    metadata       the row and column metadata\n"
    "    deviations     the standard deviations\n"
    "    correlations   the correlation matrix\n"
    "    relative       the relative covariance flag (default is true)"
  )
  .def(

    python::init< ProductMultiplicityMetadata,
                  ProductMultiplicityMetadata,
                  std::vector< double >,
                  std::vector< double >,
                  Matrix, bool >(),
    python::arg( "row_metadata" ), python::arg( "column_metadata" ),
    python::arg( "row_deviations" ), python::arg( "column_deviations" ),
    python::arg( "correlations" ), python::arg( "relative" ) = true,
    "Initialise an off-diagonal product multiplicity correlation matrix\n\n"
    "Arguments:\n"
    "    self               the covariance matrix\n"
    "    row_metadata       the row metadata\n"
    "    column_metadata    the column metadata\n"
    "    row_deviations     the standard deviations to be applied to each row\n"
    "    column_deviations  the standard deviations to be applied to each column\n"
    "    correlations       the correlation matrix\n"
    "    relative           the relative covariance flag (default is true)"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "instance" ),
    "Initialise a copy\n\n"
    "Arguments:\n"
    "    instance    the instance to be copied\n"
  )
  .def_property_readonly(

    "row_metadata",
    [] ( const Component& self ) -> decltype(auto)
       { return self.rowMetadata(); },
    "The row metadata"
  )
  .def_property_readonly(

    "column_metadata",
    [] ( const Component& self ) -> decltype(auto)
       { return self.columnMetadata(); },
    "The column metadata"
  )
  .def_property_readonly(

    "is_relative_matrix",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isRelativeMatrix(); },
    "Flag to indicate whether or not this covariance matrix is relative or not"
  )
  .def_property_readonly(

    "is_absolute_matrix",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isAbsoluteMatrix(); },
    "Flag to indicate whether or not this covariance matrix is absolute or not"
  )
  .def_property_readonly(

    "is_off_diagonal",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isOffDiagonal(); },
    "Flag to indicate whether or not this covariance matrix is off-diagonal"
  )
  .def_property_readonly(

    "is_on_diagonal",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isOnDiagonal(); },
    "Flag to indicate whether or not this covariance matrix is on-diagonal"
  )
  .def_property_readonly(

    // to ensure the matrix is not copied: reference_internal is used
    // see pybind11 documentation for Eigen bindings for more information

    "covariances",
    [] ( const Component& self ) -> decltype(auto)
       { return self.covariances(); },
    "The covariance matrix",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "standard_deviations",
    [] ( const Component& self ) -> decltype(auto)
       { return self.standardDeviations(); },
    "The standard deviations",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "correlations",
    [] ( const Component& self ) -> decltype(auto)
       { return self.correlations(); },
    "The correlation matrix",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "eigenvalues",
    [] ( const Component& self ) -> decltype(auto)
       { return self.eigenvalues(); },
    "The eigenvalues",
    python::return_value_policy::reference_internal
  )
  .def(

    "calculate_standard_deviations",
    [] ( Component& self )
       { return self.calculateStandardDeviations(); },
    "Calculate the standard deviations from the covariances\n\n"
    "The standard deviations can only be calculated from covariance matrices on the\n"
    "diagonal of the full covariance matrix. When this function is called on an\n"
    "off diagonal matrix, the function has no effect."
  )
  .def(

    "calculate_correlations",
    [] ( Component& self )
       { return self.calculateCorrelations(); },
    "Calculate the correlations (for on diagonal matrices)\n\n"
    "The correlations can be calculated without input of the standard\n"
    "deviations for matrices on the diagonal of the full matrix. Standard\n"
    "deviations will be calculated and stored as well.\n"
    "When this method is called on an off diagonal matrix, the method has\n"
    "no effect."
  )
  .def(

    "calculate_correlations",
    [] ( Component& self, const std::vector< double >& row,
         const std::vector< double >& column )
       { return self.calculateCorrelations( row, column ); },
    python::arg( "row_deviations" ), python::arg( "column_deviations" ),
    "Calculate the correlations (for off diagonal matrices)\n\n"
    "The correlations can only be calculated with input of the standard deviations\n"
    "for covariance matrices that are off diagonal in the full covariance matrix.\n"
    "Standard deviations will not be stored.\n\n"
    "Arguments:\n"
    "    self                the covariance matrix\n"
    "    row_deviations      the standard deviations to be applied to each row\n"
    "    column_deviations   the standard deviations to be applied to each column"
  )
  .def(

    "calculate_eigenvalues",
    [] ( Component& self )
       { return self.calculateEigenvalues(); },
    "Calculate the eigenvalues from the covariances\n\n"
    "The eigenvalues can only be calculated from matrices on the diagonal\n"
    "of the full matrix. When this function is called on an off diagonal matrix,\n"
    "the function has no effect."
  )
  .def(

    "extract",
    python::overload_cast< const std::optional< ReactionID >&,
                           const std::optional< EnergyGroup >&,
                           const std::optional< ParticleID >& >
    ( &Component::extract, python::const_ ),
    python::arg( "reaction" ),
    python::arg( "group" ),
    python::arg( "product" )
  )
  .def(

    "extract",
    python::overload_cast< const std::optional< ReactionID >&,
                           const std::optional< EnergyGroup >&,
                           const std::optional< ParticleID >&,
                           const std::optional< ReactionID >&,
                           const std::optional< EnergyGroup >&,
                           const std::optional< ParticleID >& >
    ( &Component::extract, python::const_ ),
    python::arg( "row_reaction" ),
    python::arg( "row_group" ),
    python::arg( "row_product" ),
    python::arg( "col_reaction" ),
    python::arg( "col_group" ),
    python::arg( "col_product" )
  );
}

} // covariance namespace
