// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "dryad/definitions.hpp"
#include "njoy/dryad/covariance/ProductMultiplicityCovarianceMatrix.hpp"

// namespace aliases
namespace python = pybind11;

namespace dryad {
namespace covariance {

void wrapProductMultiplicityCovarianceMatrix( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::ProductMultiplicityCovarianceMatrix;
  using ProductMultiplicityMetadata = njoy::dryad::covariance::ProductMultiplicityMetadata;
  using ParticleID = njoy::dryad::id::ParticleID;
  using EnergyGroup = njoy::dryad::id::EnergyGroup;
  using ReactionID = njoy::dryad::id::ReactionID;
  using Matrix = njoy::matrix::Matrix< double >;
  using Vector = njoy::matrix::Vector< double >;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "ProductMultiplicityCovarianceMatrix",
    "A covariance matrix for product multiplicities\n\n"
    "Parameters\n"
    "----------\n"
    "    metadata : njoy.dryad.covariance.ProductMultiplicityMetadata\n"
    "        the row and column metadata (on-diagonal)\n"
    "    row_metadata : njoy.dryad.covariance.ProductMultiplicityMetadata\n"
    "        the row metadata (off-diagonal)\n"
    "    column_metadata : njoy.dryad.covariance.ProductMultiplicityMetadata\n"
    "        the column metadata (off-diagonal)\n"
    "    covariances : array-like\n"
    "        the covariance matrix\n"
    "    deviations : list of float\n"
    "        the standard deviations (on-diagonal)\n"
    "    row_deviations : list of float\n"
    "        the standard deviations to be applied to each row (off-diagonal)\n"
    "    column_deviations : list of float\n"
    "        the standard deviations to be applied to each column (off-diagonal)\n"
    "    correlations : array-like\n"
    "        the correlation matrix\n"
    "    eigenvalues : list of float\n"
    "        the eigenvalues\n"
    "    eigenvectors : list of array-like\n"
    "        the associated eigenvectors\n"
    "    relative : bool, default True\n"
    "        the relative covariance flag"
  );

  // wrap the component
  component
  .def(

    python::init< ProductMultiplicityMetadata,
                  Matrix,
                  bool >(),
    python::arg( "metadata" ),
    python::arg( "covariances" ),
    python::arg( "relative" ) = true,
    "Initialise an on-diagonal product multiplicity covariance matrix"
  )
  .def(

    python::init< ProductMultiplicityMetadata,
                  ProductMultiplicityMetadata,
                  Matrix, bool >(),
    python::arg( "row_metadata" ), python::arg( "column_metadata" ),
    python::arg( "covariances" ), python::arg( "relative" ) = true,
    "Initialise an off-diagonal product multiplicity covariance matrix"
  )
  .def(

    python::init< ProductMultiplicityMetadata,
                  std::vector< double >,
                  Matrix,
                  bool >(),
    python::arg( "metadata" ), python::arg( "deviations" ),
    python::arg( "correlations" ), python::arg( "relative" ) = true,
    "Initialise an on-diagonal product multiplicity correlation matrix"
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
    "Initialise an off-diagonal product multiplicity correlation matrix"
  )
  .def(

    python::init< ProductMultiplicityMetadata,
                  std::vector< double >,
                  std::vector< Vector >,
                  bool >(),
    python::arg( "metadata" ), python::arg( "eigenvalues" ),
    python::arg( "eigenvectors" ), python::arg( "relative" ) = true,
    "Initialise an on-diagonal product multiplicity covariance matrix using eigenvalues\n"
    "and eigenvectors"
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
    "The flag to indicate whether or not this covariance matrix is relative or not"
  )
  .def_property_readonly(

    "is_absolute_matrix",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isAbsoluteMatrix(); },
    "The flag to indicate whether or not this covariance matrix is absolute or not"
  )
  .def_property_readonly(

    "is_off_diagonal",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isOffDiagonal(); },
    "The flag to indicate whether or not this covariance matrix is off-diagonal"
  )
  .def_property_readonly(

    "is_on_diagonal",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isOnDiagonal(); },
    "The flag to indicate whether or not this covariance matrix is on-diagonal"
  )
  .def_property(

    // to ensure the matrix is not copied: reference_internal is used
    // see pybind11 documentation for Eigen bindings for more information

    "covariances",
    [] ( const Component& self ) -> decltype(auto)
       { return self.covariances(); },
    [] ( Component& self, Matrix covariances ) -> void
       { self.covariances( std::move( covariances ) ); },
    "The covariance matrix",
    python::return_value_policy::reference_internal
  )
  .def_property(

    "standard_deviations",
    [] ( const Component& self ) -> decltype(auto)
       { return self.standardDeviations(); },
    [] ( Component& self,
         std::optional< std::vector< double > > deviations ) -> void
       { self.standardDeviations( std::move( deviations ) ); },
    "The standard deviations",
    python::return_value_policy::reference_internal
  )
  .def_property(

    "correlations",
    [] ( const Component& self ) -> decltype(auto)
       { return self.correlations(); },
    [] ( Component& self, Matrix correlations ) -> void
       { self.correlations( std::move( correlations ) ); },
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
  .def_property_readonly(

    "eigenvectors",
    [] ( const Component& self ) -> decltype(auto)
       { return self.eigenvectors(); },
    "The eigenvectors",
    python::return_value_policy::reference_internal
  )
  .def_property(

    "eigendata",
    [] ( const Component& self ) -> decltype(auto)
       { return self.eigendata(); },
    [] ( Component& self,
         std::tuple< std::optional< std::vector< double > >,
                     std::optional< std::vector< Vector > > > eigendata ) -> void
       { self.eigendata( std::move( eigendata ) ); },
    "The eigenvalues and eigenvectors",
    python::return_value_policy::reference_internal
  )
  .def(

    "calculate_covariances",
    [] ( Component& self )
       { return self.calculateCovariances(); },
    "Calculate the covariances (for on-diagonal blocks)\n\n"
    "The covariances can be calculated without input of the standard\n"
    "deviations for blocks on the diagonal of the matrix.\n\n"
    "When this method is called on an off-diagonal block, the method has no effect.\n\n"
    "When this method is called on a block that has no correlations, the method\n"
    "has no effect."
  )
  .def(

    "calculate_covariances",
    [] ( Component& self,
         const std::vector< double >& row,
         const std::vector< double >& column )
       { return self.calculateCovariances( row, column ); },
    python::arg( "row_deviations" ), python::arg( "column_deviations" ),
    "Calculate the covariances (for off-diagonal matrices)\n\n"
    "The covariances can only be calculated with input of the standard deviations\n"
    "for blocks that are off-diagonal in the matrix. Standard deviations will not\n"
    "be stored.\n\n"
    "When this method is called on a block that has no correlations, the method\n"
    "has no effect.\n\n"
    "Parameters\n"
    "----------\n"
    "    row_deviations : list of float\n"
    "        the standard deviations to be applied to each row\n"
    "    column_deviations : list of float\n"
    "        the standard deviations to be applied to each column"
  )
  .def(

    "calculate_standard_deviations",
    [] ( Component& self )
       { return self.calculateStandardDeviations(); },
    "Calculate the standard deviations from the covariances\n\n"
    "The standard deviations can only be calculated from covariance matrices on the\n"
    "diagonal of the full covariance matrix. When this function is called on an\n"
    "off-diagonal matrix, the function has no effect."
  )
  .def(

    "calculate_correlations",
    [] ( Component& self )
       { return self.calculateCorrelations(); },
    "Calculate the correlations (for on-diagonal matrices)\n\n"
    "The correlations can be calculated without input of the standard\n"
    "deviations for matrices on the diagonal of the full matrix. Standard\n"
    "deviations will be calculated and stored as well.\n\n"
    "When this method is called on an off-diagonal matrix, the method has\n"
    "no effect."
  )
  .def(

    "calculate_correlations",
    [] ( Component& self,
         const std::vector< double >& row,
         const std::vector< double >& column )
       { return self.calculateCorrelations( row, column ); },
    python::arg( "row_deviations" ), python::arg( "column_deviations" ),
    "Calculate the correlations (for off-diagonal matrices)\n\n"
    "The correlations can only be calculated with input of the standard deviations\n"
    "for covariance matrices that are off-diagonal in the full covariance matrix.\n"
    "Standard deviations will not be stored.\n\n"
    "Parameters\n"
    "----------\n"
    "    row_deviations : list of float\n"
    "        the standard deviations to be applied to each row\n"
    "    column_deviations : list of float\n"
    "        the standard deviations to be applied to each column"
  )
  .def(

    "calculate_eigenvalues",
    [] ( Component& self )
       { return self.calculateEigenvalues(); },
    "Calculate the eigenvalues from the covariances\n\n"
    "The eigenvalues can only be calculated from matrices on the diagonal\n"
    "of the full matrix. When this function is called on an off-diagonal matrix,\n"
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
    python::arg( "product" ),
    "Extract a submatrix from the covariance matrix based on selected values\n\n"
    "Parameters\n"
    "----------\n"
    "    reaction : njoy.dryad.id.ReactionID or None\n"
    "        the reaction identifier to extract\n"
    "    group : njoy.dryad.id.EnergyGroup or None\n"
    "        the energy group to extract\n"
    "    product : njoy.dryad.id.ParticleID or None\n"
    "        the product identifier to extract"
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
    python::arg( "col_product" ),
    "Extract a submatrix from the covariance matrix based on selected row and column values\n\n"
    "Parameters\n"
    "----------\n"
    "    row_reaction : njoy.dryad.id.ReactionID or None\n"
    "        the row reaction identifier to extract\n"
    "    row_group : njoy.dryad.id.EnergyGroup or None\n"
    "        the row energy group to extract\n"
    "    row_product : njoy.dryad.id.ParticleID or None\n"
    "        the row product identifier to extract\n"
    "    col_reaction : njoy.dryad.id.ReactionID or None\n"
    "        the column reaction identifier to extract\n"
    "    col_group : njoy.dryad.id.EnergyGroup or None\n"
    "        the column energy group to extract\n"
    "    col_product : njoy.dryad.id.ParticleID or None\n"
    "        the column product identifier to extract"
  );

  // add standard copy definitions
  addStandardCopyDefinitions< Component >( component );
}

} // covariance namespace
} // dryad namespace
