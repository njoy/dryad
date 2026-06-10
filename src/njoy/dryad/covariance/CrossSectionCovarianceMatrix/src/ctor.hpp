private:

CrossSectionCovarianceMatrix( Parent&& base ) :
  Parent( std::move( base ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CrossSectionCovarianceMatrix() = default;

CrossSectionCovarianceMatrix( const CrossSectionCovarianceMatrix& ) = default;
CrossSectionCovarianceMatrix( CrossSectionCovarianceMatrix&& ) = default;

CrossSectionCovarianceMatrix& operator=( const CrossSectionCovarianceMatrix& ) = default;
CrossSectionCovarianceMatrix& operator=( CrossSectionCovarianceMatrix&& ) = default;

/**
 *  @brief Constructor for an on-diagonal cross section covariance matrix
 *
 *  @param[in] metadata      the row and column metadata
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag (default is true)
 *  @param[in] scaling       the variance scaling information (default is none)
 */
CrossSectionCovarianceMatrix( CrossSectionMetadata metadata,
                              matrix::Matrix< double > covariances,
                              bool relative = true,
                              std::optional< VarianceScaling > scaling = std::nullopt ) :
  Parent( std::move( metadata ), std::move( covariances ), relative ),
  scaling_( std::move( scaling ) ) {}

/**
 *  @brief Constructor for an off-diagonal cross section covariance matrix
 *
 *  @param[in] rowMetadata       the row metadata
 *  @param[in] columnMetadata    the column metadata
 *  @param[in] covariances       the covariance matrix
 *  @param[in] relative          the relative covariance flag (default is true)
 */
CrossSectionCovarianceMatrix( CrossSectionMetadata rowMetadata,
                              CrossSectionMetadata columnMetadata,
                              matrix::Matrix< double > covariances,
                              bool relative = true ) :
  Parent( std::move( rowMetadata ), std::move( columnMetadata ),
          std::move( covariances ), relative ),
  scaling_( std::nullopt ) {}

/**
 *  @brief Constructor for an on-diagonal cross section correlation matrix
 *
 *  @param[in] metadata       the row and column metadata
 *  @param[in] deviations     the standard deviations
 *  @param[in] correlations   the correlation matrix
 *  @param[in] relative       the relative covariance flag (default is true)
 *  @param[in] scaling        the variance scaling information (default is none)
 */
CrossSectionCovarianceMatrix( CrossSectionMetadata metadata,
                              std::vector< double > deviations,
                              matrix::Matrix< double > correlations,
                              bool relative = true,
                              std::optional< VarianceScaling > scaling = std::nullopt ) :
  Parent( std::move( metadata ), std::move( deviations ),
          std::move( correlations ), relative ),
  scaling_( std::move( scaling ) ) {}

/**
 *  @brief Constructor for an off-diagonal cross section correlation matrix
 *
 *  @param[in] rowMetadata        the row metadata
 *  @param[in] columnMetadata     the column metadata
 *  @param[in] rowDeviations      the standard deviations to be applied to each row
 *  @param[in] columnDeviations   the standard deviations to be applied to each column
 *  @param[in] correlations       the correlation matrix
 *  @param[in] relative           the relative covariance flag (default is true)
 */
CrossSectionCovarianceMatrix( CrossSectionMetadata rowMetadata,
                              CrossSectionMetadata columnMetadata,
                              const std::vector< double >& rowDeviations,
                              const std::vector< double >& columnDeviations,
                              matrix::Matrix< double > correlations,
                              bool relative = true ) :
  Parent( std::move( rowMetadata ), std::move( columnMetadata ),
          rowDeviations, columnDeviations,
          std::move( correlations ), relative ),
  scaling_( std::nullopt ) {}

/**
 *  @brief Constructor using eigenvalues and eigenvectors for an on-diagonal
 *         cross section covariance matrix
 *
 *  @param[in] metadata       the row and column metadata
 *  @param[in] eigenvalues    the eigenvalues
 *  @param[in] eigenvectors   the associated eigenvalues
 *  @param[in] relative       the relative covariance flag
 *  @param[in] scaling        the variance scaling information (default is none)
 */
CrossSectionCovarianceMatrix( CrossSectionMetadata metadata,
                              std::vector< double > eigenvalues,
                              std::vector< matrix::Vector< double > > eigenvectors,
                              bool relative = true,
                              std::optional< VarianceScaling > scaling = std::nullopt ) :
  Parent( std::move( metadata ), std::move( eigenvalues ),
          std::move( eigenvectors ), relative ),
  scaling_( std::move( scaling ) ) {}
