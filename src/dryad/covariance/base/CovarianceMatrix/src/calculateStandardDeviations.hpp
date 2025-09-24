/**
 *  @brief Calculate the standard deviations from the covariances
 *
 *  The standard deviations can only be calculated from covariance matrices on the
 *  diagonal of the full covariance matrix. When this function is called on an
 *  off diagonal matrix, the function has no effect.
 */
void calculateStandardDeviations() {

  if ( this->isOnDiagonal() ) {

    std::vector< double > sigmas;
    sigmas.reserve( this->rowKeys().size() );

    for ( const auto& value : this->covariances().diagonal().reshaped() ) {

      sigmas.emplace_back( std::sqrt( value ) );
    }

    this->sigmas_ = sigmas;
  }
}
