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
 *  @param[in] keys          the keys associated with the covariance block
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CovarianceMatrix( std::vector< Key > keys, Matrix< double > covariances,
                  bool relative = true ) :
  row_( std::move( keys ) ), column_( std::nullopt ), relative_( relative ),
  covariances_( std::move( covariances ) ), sigmas_( std::nullopt ),
  correlations_( std::nullopt ) {

  verifyMatrix( this->covariances().value(), this->rowKeys().size() );
}

/**
 *  @brief Constructor for an on-diagonal correlation matrix (relative or absolute)
 *
 *  @param[in] keys           the keys associated with the covariance block
 *  @param[in] deviations     the standard deviations
 *  @param[in] correlations   the correlation matrix
 *  @param[in] relative       the relative covariance flag
 */
CovarianceMatrix( std::vector< Key > keys,
                  std::vector< double > deviations,
                  Matrix< double > correlations,
                  bool relative = true ) :
  row_( std::move( keys ) ), column_( std::nullopt ), relative_( relative ),
  covariances_( std::nullopt ), sigmas_( std::move( deviations ) ),
  correlations_( std::move( correlations ) ) {

  verifyMatrix( this->standardDeviations().value(),
                this->correlations().value(),
                this->rowKeys().size() );
}

/**
 *  @brief Constructor for an off-diagonal covariance matrix (relative or absolute)
 *
 *  @param[in] rowKeys       the row keys
 *  @param[in] columnKeys    the column keys
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CovarianceMatrix( std::vector< Key > rowKeys, std::vector< Key > columnKeys,
                  Matrix< double > covariances, bool relative = true ) :
  row_( std::move( rowKeys ) ), column_( std::move( columnKeys ) ),
  relative_( relative ), covariances_( std::move( covariances ) ),
  sigmas_( std::nullopt ), correlations_( std::nullopt ) {

  verifyMatrix( this->covariances().value(),
                this->rowKeys().size(),
                this->columnKeys().size() );
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
 *  @param[in] correlations       the covariance matrix
 *  @param[in] relative           the relative covariance flag
 */
CovarianceMatrix( std::vector< Key > rowKeys, std::vector< Key > columnKeys,
                  const std::vector< double >& rowDeviations,
                  const std::vector< double >& columnDeviations,
                  Matrix< double > correlations, bool relative = true ) :
  row_( std::move( rowKeys ) ), column_( std::move( columnKeys ) ),
  relative_( relative ), covariances_( std::nullopt ),
  sigmas_( std::nullopt ), correlations_( std::move( correlations ) ) {

  verifyMatrix( this->correlations().value(),
                this->rowKeys().size(),
                this->columnKeys().size() );
}
