private:

AngularDistributionCovarianceMatrix( Parent&& base, std::optional< ReferenceFrame > frame ) :
  Parent( std::move( base ) ), frame_( std::move( frame ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
AngularDistributionCovarianceMatrix() = default;

AngularDistributionCovarianceMatrix( const AngularDistributionCovarianceMatrix& ) = default;
AngularDistributionCovarianceMatrix( AngularDistributionCovarianceMatrix&& ) = default;

AngularDistributionCovarianceMatrix& operator=( const AngularDistributionCovarianceMatrix& ) = default;
AngularDistributionCovarianceMatrix& operator=( AngularDistributionCovarianceMatrix&& ) = default;

/**
 *  @brief Constructor for an on-diagonal angular distribution covariance matrix
 *
 *  @param[in] metadata      the row and column metadata
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag (default is true)
 *  @param[in] frame         the reference frame of the distribution data (default is None)
 */
AngularDistributionCovarianceMatrix( AngularDistributionMetadata metadata,
                                     matrix::Matrix< double > covariances,
                                     bool relative = true,
                                     std::optional< ReferenceFrame > frame = std::nullopt ) :
  Parent( std::move( metadata ), std::move( covariances ), relative ) {}

/**
 *  @brief Constructor for an off-diagonal angular distribution covariance matrix
 *
 *  @param[in] rowMetadata      the row metadata
 *  @param[in] columnMetadata   the column metadata
 *  @param[in] covariances      the covariance matrix
 *  @param[in] relative         the relative covariance flag (default is true)
 *  @param[in] frame            the reference frame of the distribution data (default is None)
 */
AngularDistributionCovarianceMatrix( AngularDistributionMetadata rowMetadata,
                                     AngularDistributionMetadata columnMetadata,
                                     matrix::Matrix< double > covariances,
                                     bool relative = true,
                                     std::optional< ReferenceFrame > frame = std::nullopt ) :
  Parent( std::move( rowMetadata ), std::move( columnMetadata ),
          std::move( covariances ), relative ) {}

/**
 *  @brief Constructor for an on-diagonal angular distribution correlation matrix
 *
 *  @param[in] metadata       the row and column metadata
 *  @param[in] deviations     the standard deviations
 *  @param[in] correlations   the correlation matrix
 *  @param[in] relative       the relative covariance flag (default is true)
 *  @param[in] frame          the reference frame of the distribution data (default is None)
 */
AngularDistributionCovarianceMatrix( AngularDistributionMetadata metadata,
                                     std::vector< double > deviations,
                                     matrix::Matrix< double > correlations,
                                     bool relative = true,
                                     std::optional< ReferenceFrame > frame = std::nullopt ) :
  Parent( std::move( metadata ), std::move( deviations ),
          std::move( correlations ), relative ) {}

/**
 *  @brief Constructor for an off-diagonal angular distribution correlation matrix
 *
 *  @param[in] rowMetadata        the row metadata
 *  @param[in] columnMetadata     the column metadata
 *  @param[in] rowDeviations      the standard deviations to be applied to each row
 *  @param[in] columnDeviations   the standard deviations to be applied to each column
 *  @param[in] correlations       the correlation matrix
 *  @param[in] relative           the relative covariance flag (default is true)
 *  @param[in] frame              the reference frame of the distribution data (default is None)
 */
AngularDistributionCovarianceMatrix( AngularDistributionMetadata rowMetadata,
                                     AngularDistributionMetadata columnMetadata,
                                     const std::vector< double >& rowDeviations,
                                     const std::vector< double >& columnDeviations,
                                     matrix::Matrix< double > correlations,
                                     bool relative = true,
                                     std::optional< ReferenceFrame > frame = std::nullopt ) :
  Parent( std::move( rowMetadata ), std::move( columnMetadata ),
          rowDeviations, columnDeviations,
          std::move( correlations ), relative ) {}

/**
 *  @brief Constructor using eigenvalues and eigenvectors for an on-diagonal
 *         angular distribution covariance matrix
 *
 *  @param[in] metadata       the row and column metadata
 *  @param[in] eigenvalues    the eigenvalues
 *  @param[in] eigenvectors   the associated eigenvectors
 *  @param[in] relative       the relative covariance flag
 *  @param[in] frame          the reference frame of the distribution data (default is None)
 */
AngularDistributionCovarianceMatrix( AngularDistributionMetadata metadata,
                                     std::vector< double > eigenvalues,
                                     std::vector< matrix::Vector< double > > eigenvectors,
                                     bool relative = true,
                                     std::optional< ReferenceFrame > frame = std::nullopt ) :
  Parent( std::move( metadata ), std::move( eigenvalues ),
          std::move( eigenvectors ), relative ) {}
