private:

ProductMultiplicityCovarianceMatrix( Parent&& base ) :
  Parent( std::move( base ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ProductMultiplicityCovarianceMatrix() = default;

ProductMultiplicityCovarianceMatrix( const ProductMultiplicityCovarianceMatrix& ) = default;
ProductMultiplicityCovarianceMatrix( ProductMultiplicityCovarianceMatrix&& ) = default;

ProductMultiplicityCovarianceMatrix& operator=( const ProductMultiplicityCovarianceMatrix& ) = default;
ProductMultiplicityCovarianceMatrix& operator=( ProductMultiplicityCovarianceMatrix&& ) = default;

/**
 *  @brief Constructor for an on-diagonal product multiplicity covariance matrix
 *
 *  @param[in] metadata      the row and column metadata
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag (default is true)
 */
ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata metadata,
                                     matrix::Matrix< double > covariances,
                                     bool relative = true ) :
  Parent( std::move( metadata ), std::move( covariances ), relative ) {}

/**
 *  @brief Constructor for an off-diagonal product multiplicity covariance matrix
 *
 *  @param[in] rowMetadata      the row metadata
 *  @param[in] columnMetadata   the column metadata
 *  @param[in] covariances      the covariance matrix
 *  @param[in] relative         the relative covariance flag (default is true)
 */
ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata rowMetadata,
                                     ProductMultiplicityMetadata columnMetadata,
                                     matrix::Matrix< double > covariances,
                                     bool relative = true ) :
  Parent( std::move( rowMetadata ), std::move( columnMetadata ),
          std::move( covariances ), relative ) {}

/**
 *  @brief Constructor for an on-diagonal product multiplicity correlation matrix
 *
 *  @param[in] metadata       the row and column metadata
 *  @param[in] deviations     the standard deviations
 *  @param[in] correlations   the correlation matrix
 *  @param[in] relative       the relative covariance flag (default is true)
 */
ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata metadata,
                                     std::vector< double > deviations,
                                     matrix::Matrix< double > correlations,
                                     bool relative = true ) :
  Parent( std::move( metadata ), std::move( deviations ),
          std::move( correlations ), relative ) {}

/**
 *  @brief Constructor for an off-diagonal product multiplicity correlation matrix
 *
 *  @param[in] rowMetadata        the row metadata
 *  @param[in] columnMetadata     the column metadata
 *  @param[in] rowDeviations      the standard deviations to be applied to each row
 *  @param[in] columnDeviations   the standard deviations to be applied to each column
 *  @param[in] correlations       the correlation matrix
 *  @param[in] relative           the relative covariance flag (default is true)
 */
ProductMultiplicityCovarianceMatrix( ProductMultiplicityMetadata rowMetadata,
                                     ProductMultiplicityMetadata columnMetadata,
                                     const std::vector< double >& rowDeviations,
                                     const std::vector< double >& columnDeviations,
                                     matrix::Matrix< double > correlations,
                                     bool relative = true ) :
  Parent( std::move( rowMetadata ), std::move( columnMetadata ),
          rowDeviations, columnDeviations,
          std::move( correlations ), relative ) {}
