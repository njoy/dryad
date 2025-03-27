// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/eigen.h>

// local includes
#include "dryad/covariance/CrossSectionCovarianceBlock.hpp"

// namespace aliases
namespace python = pybind11;

namespace covariance {

void wrapCrossSectionCovarianceBlock( python::module& module ) {

  // type aliases
  using Component = njoy::dryad::covariance::CrossSectionCovarianceBlock;
  using ParticleID = njoy::dryad::id::ParticleID;
  using ReactionID = njoy::dryad::id::ReactionID;
  using Matrix = njoy::dryad::covariance::Matrix< double >;
  using CrossSectionMetadata = njoy::dryad::covariance::CrossSectionMetadata;
  using VarianceScaling = njoy::dryad::covariance::VarianceScaling;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "CrossSectionCovarianceBlock",
    "A cross section covariance matrix block"
  );

  // wrap the component
  component
  .def(

    python::init< CrossSectionMetadata, Matrix, bool,
                  std::optional< VarianceScaling > >(),
    python::arg( "metadata" ), python::arg( "covariances" ),
    python::arg( "relative" ) = true,
    python::arg( "scaling" ) = std::nullopt,
    "Initialise a diagonal cross section covariance block\n\n"
    "Arguments:\n"
    "    self          the covariance block\n"
    "    metadata      the metadata associated with the covariance block\n"
    "    covariances   the covariance matrix\n"
    "    relative      the relative covariance flag (default is true)\n"
    "    scaling       the variance scaling information (default is none)"
  )
  .def(

    python::init< CrossSectionMetadata, CrossSectionMetadata, Matrix, bool >(),
    python::arg( "row_metadata" ), python::arg( "column_metadata" ),
    python::arg( "covariances" ), python::arg( "relative" ) = true,
    "Initialise a diagonal cross section covariance block\n\n"
    "Arguments:\n"
    "    self               the covariance block\n"
    "    row_metadata       the row metadata\n"
    "    column_metadata    the column metadata\n"
    "    covariances        the covariance matrix\n"
    "    relative           the relative covariance flag (default is true)"
  )
  .def(

    python::init< ParticleID, ParticleID, ReactionID,
                  std::vector< double >, Matrix, bool,
                  std::optional< VarianceScaling > >(),
    python::arg( "projectile" ), python::arg( "target" ),
    python::arg( "reaction" ), python::arg( "energies" ),
    python::arg( "covariances" ), python::arg( "relative" ) = true,
    python::arg( "scaling" ) = std::nullopt,
    "Initialise a diagonal cross section covariance block\n\n"
    "Arguments:\n"
    "    self          the covariance block\n"
    "    projectile    the projectile identifier\n"
    "    target        the target identifier\n"
    "    reaction      the reaction identifier\n"
    "    energies      the energy boundaries\n"
    "    covariances   the covariance matrix\n"
    "    relative      the relative covariance flag (default is true)\n"
    "    scaling       the variance scaling information (default is none)"
  )
  .def(

    python::init< ParticleID, ParticleID, ReactionID, std::vector< double >,
                  ParticleID, ParticleID, ReactionID, std::vector< double >,
                  Matrix, bool >(),
    python::arg( "row_projectile" ), python::arg( "row_target" ),
    python::arg( "row_reaction" ), python::arg( "row_energies" ),
    python::arg( "column_projectile" ), python::arg( "column_target" ),
    python::arg( "column_reaction" ), python::arg( "column_energies" ),
    python::arg( "covariances" ), python::arg( "relative" ) = true,
    "Initialise an off-diagonal cross section covariance block\n\n"
    "Arguments:\n"
    "    self                 the covariance block\n"
    "    row_projectile       the row projectile identifier\n"
    "    row_target           the row target identifier\n"
    "    row_reaction         the row reaction identifier\n"
    "    row_energies         the row energy boundaries\n"
    "    column_projectile    the column projectile identifier\n"
    "    column_target        the column target identifier\n"
    "    column_reaction      the column reaction identifier\n"
    "    column_energies      the column energy boundaries\n"
    "    covariances          the covariance matrix\n"
    "    relative             the relative covariance flag"
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

    "variance_scaling",
    &Component::varianceScaling,
    "The variance scaling information\n\n"
    " If this type of information is given, it will be for an on-diagonal covariance block."
  )
  .def_property_readonly(

    "has_variance_scaling",
    &Component::hasVarianceScaling,
    "Flag indicating whether or not the covariance block has variance scaling "
    "information"
  )
  .def_property_readonly(

    "is_relative_block",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isRelativeBlock(); },
    "Flag to indicate whether or not this covariance block is relative or not"
  )
  .def_property_readonly(

    "is_off_diagonal_block",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isOffDiagonalBlock(); },
    "Flag to indicate whether or not this covariance block is an off-diagonal block"
  )
  .def_property_readonly(

    "is_diagonal_block",
    [] ( const Component& self ) -> decltype(auto)
       { return self.isDiagonalBlock(); },
    "Flag to indicate whether or not this covariance block is a diagonal block"
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
    "The standard deviations can only be calculated from covariance blocks on the\n"
    "diagonal of the covariance matrix. When this function is called on an\n"
    "off diagonal block, the function has no effect."
  )
  .def(

    "calculate_correlations",
    [] ( Component& self )
       { return self.calculateCorrelations(); },
    "Calculate the correlations (for covariance blocks on the diagonal)\n\n"
    "The correlations can only be calculated without input of the standard\n"
    "deviations for covariance blocks on the diagonal of the covariance matrix.\n"
    "When this method is called on an off diagonal block, the method has no effect.\n"
    "Standard deviations will be calculated and stored as well."
  )
  .def(

    "calculate_correlations",
    [] ( Component& self, const std::vector< double >& row,
         const std::vector< double >& column )
       { return self.calculateCorrelations( row, column ); },
    python::arg( "row_deviations" ), python::arg( "column_deviations" ),
    "Calculate the correlations (for off diagonal covariance blocks)\n\n"
    "The correlations can only be calculated with input of the standard deviations\n"
    "for covariance blocks that are off diagonal in the covariance matrix.\n"
    "Standard deviations will not be stored.\n\n"
    "Arguments:\n"
    "    self                 the covariance block\n"
    "    row_deviations       the standard deviations to be applied to each row\n"
    "    column_deviations    the standard deviations to be applied to each column"
  )
  .def(

    "calculate_eigenvalues",
    [] ( Component& self )
       { return self.calculateEigenvalues(); },
    "Calculate the eigenvalues from the covariances\n\n"
    "The eigenvalues can only be calculated from covariance blocks on the\n"
    "diagonal of the covariance matrix. When this function is called on an\n"
    "off diagonal block, the function has no effect."
  );
}

} // covariance namespace
