/**
 *  @brief Constructor for a scaled variance block
 *
 *  @param[in] metadata    the metadata associated with the covariance block
 *  @param[in] factors     the covariance matrix
 */
ScaledVarianceBlock( Metadata metadata, std::vector< double > factors ) :
  row_( std::move( metadata ) ), factors_( std::move( factors ) ) {}
