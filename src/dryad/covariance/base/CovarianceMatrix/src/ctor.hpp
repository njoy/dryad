/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CovarianceBlock() = default;

CovarianceBlock( const CovarianceBlock& ) = default;
CovarianceBlock( CovarianceBlock&& ) = default;

CovarianceBlock& operator=( const CovarianceBlock& ) = default;
CovarianceBlock& operator=( CovarianceBlock&& ) = default;

/**
 *  @brief Constructor for a diagonal covariance block using a covariance
 *         matrix (relative or absolute)
 *
 *  @param[in] structure     the structure associated with the covariance block
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CovarianceBlock( Structure structure, Matrix< double > covariances, bool relative = true ) :
  row_( std::move( structure ) ), column_( std::nullopt ), relative_( relative ),
  covariances_( std::move( covariances ) ), sigmas_( std::nullopt ),
  correlations_( std::nullopt ) {

  verifyMatrix( this->covariances().value(), this->rowStructure().size() );
}

/**
 *  @brief Constructor for an off-diagonal covariance block using a covariance
 *         matrix (relative or absolute)
 *
 *  @param[in] rowStructure      the row structure
 *  @param[in] columnStructure   the column structure
 *  @param[in] covariances       the covariance matrix
 *  @param[in] relative          the relative covariance flag
 */
CovarianceBlock( Structure rowStructure, Structure columnStructure,
                 Matrix< double > covariances, bool relative = true ) :
  row_( std::move( rowStructure ) ), column_( std::move( columnStructure ) ),
  relative_( relative ), covariances_( std::move( covariances ) ),
  sigmas_( std::nullopt ), correlations_( std::nullopt ) {

  verifyMatrix( this->covariances().value(),
                this->rowStructure().size(),
                this->columnStructure().size() );
}
