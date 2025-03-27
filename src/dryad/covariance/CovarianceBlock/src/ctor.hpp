/**
 *  @brief Constructor for a diagonal covariance block using a covariance
 *         matrix (relative or absolute)
 *
 *  @param[in] metadata      the metadata associated with the covariance block
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
CovarianceBlock( MetaData metadata, Matrix< double > covariances, bool relative = true ) :
  row_( std::move( metadata ) ), column_( std::nullopt ), relative_( relative ),
  covariances_( std::move( covariances ) ), sigmas_( std::nullopt ),
  correlations_( std::nullopt ) {

  verifyMatrix( this->covariances().value(), this->rowMetadata().size() );
}

/**
 *  @brief Constructor for an off-diagonal covariance block using a covariance
 *         matrix (relative or absolute)
 *
 *  @param[in] rowMetadata       the row metadata
 *  @param[in] columnMetadata    the column metadata
 *  @param[in] covariances       the covariance matrix
 *  @param[in] relative          the relative covariance flag
 */
CovarianceBlock( MetaData rowMetadata, MetaData columnMetadata,
                 Matrix< double > covariances, bool relative = true ) :
  row_( std::move( rowMetadata ) ), column_( std::move( columnMetadata ) ),
  relative_( relative ), covariances_( std::move( covariances ) ),
  sigmas_( std::nullopt ), correlations_( std::nullopt ) {

  verifyMatrix( this->covariances().value(),
                this->rowMetadata().size(),
                this->columnMetadata().size() );
}
