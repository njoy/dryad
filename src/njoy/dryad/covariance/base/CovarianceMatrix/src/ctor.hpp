//! @todo the keys are currently required in the ctors. they can be removed
//!       when we are capable of using cartesian_product

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CovarianceMatrix() = default;

CovarianceMatrix( const CovarianceMatrix& ) = default;
CovarianceMatrix( CovarianceMatrix&& ) = default;

CovarianceMatrix& operator=( const CovarianceMatrix& ) = default;
CovarianceMatrix& operator=( CovarianceMatrix&& ) = default;

/**
 *  @brief Constructor for an on-diagonal covariance matrix (relative or absolute)
 *
 *  @param[in] metadata      the metadata
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CovarianceMatrix( Metadata metadata,
                  matrix::Matrix< double > covariances,
                  bool relative = true ) :
    row_metadata_( std::move( metadata ) ),
    column_metadata_( std::nullopt ),
    relative_( relative ),
    covariances_( std::move( covariances ) ),
    sigmas_( std::nullopt ),
    correlations_( std::nullopt ) {

  verifyMatrix( this->covariances(), this->rowMetadata().keys().size() );
  this->calculateCorrelations();
  this->calculateEigenvalues();
}

/**
 *  @brief Constructor for an on-diagonal correlation matrix (relative or absolute)
 *
 *  @param[in] metadata       the metadata from which the keys are derived
 *  @param[in] deviations     the standard deviations
 *  @param[in] correlations   the correlation matrix
 *  @param[in] relative       the relative covariance flag
 */
CovarianceMatrix( Metadata metadata,
                  std::vector< double > deviations,
                  matrix::Matrix< double > correlations,
                  bool relative = true ) :
    row_metadata_( std::move( metadata ) ),
    column_metadata_( std::nullopt ),
    relative_( relative ),
    sigmas_( std::move( deviations ) ),
    correlations_( std::move( correlations ) ) {

  verifyMatrix( this->standardDeviations().value(),
                this->correlations().value(),
                this->rowMetadata().keys().size() );
  this->calculateCovariances();
  this->calculateEigenvalues();
}

/**
 *  @brief Constructor using eigenvalues and eigenvectors (relative or absolute)
 *
 *  @param[in] metadata       the metadata from which the keys are derived
 *  @param[in] eigenvalues    the eigenvalues
 *  @param[in] eigenvectors   the associated eigenvalues
 *  @param[in] relative       the relative covariance flag
 */
CovarianceMatrix( Metadata metadata,
                  std::vector< double > eigenvalues,
                  std::vector< matrix::Vector< double > > eigenvectors,
                  bool relative = true ) :
    row_metadata_( std::move( metadata ) ),
    column_metadata_( std::nullopt ),
    relative_( relative ),
    eigendata_( std::make_tuple( std::move( eigenvalues ), std::move( eigenvectors ) ) ) {

  verifyMatrix( this->eigenvalues().value(),
                this->eigenvectors().value(),
                this->rowMetadata().keys().size() );
  this->calculateCovariances();
  this->calculateCorrelations();
}

/**
 *  @brief Constructor for an off-diagonal covariance matrix (relative or absolute)
 *
 *  @param[in] rowKeys       the row keys
 *  @param[in] columnKeys    the column keys
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CovarianceMatrix( Metadata rowMetadata,
                  Metadata columnMetadata,
                  matrix::Matrix< double > covariances,
                  bool relative = true ) :
    row_metadata_( std::move( rowMetadata ) ),
    column_metadata_( std::move( columnMetadata ) ),
    relative_( relative ),
    covariances_( std::move( covariances ) ),
    sigmas_( std::nullopt ),
    correlations_( std::nullopt ) {

  verifyMatrix( this->covariances(),
                this->rowMetadata().keys().size(),
                this->columnMetadata().keys().size() );
}

/**
 *  @brief Constructor for an off-diagonal correlation matrix (relative or absolute)
 *
 *  The standard deviations are not stored for off-diagonal data.
 *
 *  @param[in] rowKeys            the row keys
 *  @param[in] columnKeys         the column keys
 *  @param[in] rowDeviations      the standard deviations to be applied to each row
 *  @param[in] columnDeviations   the standard deviations to be applied to each column
 *  @param[in] correlations       the correlation matrix
 *  @param[in] relative           the relative covariance flag
 */
CovarianceMatrix( Metadata rowMetadata,
                  Metadata columnMetadata,
                  const std::vector< double >& rowDeviations,
                  const std::vector< double >& columnDeviations,
                  matrix::Matrix< double > correlations,
                  bool relative = true ) :
    row_metadata_( std::move( rowMetadata ) ),
    column_metadata_( std::move( columnMetadata ) ),
    relative_( relative ),
    sigmas_( std::nullopt ),
    correlations_( std::move( correlations ) ) {

  verifyMatrix( this->correlations().value(),
                this->rowMetadata().keys().size(),
                this->columnMetadata().keys().size() );
  this->calculateCovariances( rowDeviations, columnDeviations );
}
