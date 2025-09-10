/**
 *  @brief Calculate the standard deviations from the covariances
 *
 *  The standard deviations can only be calculated from covariance blocks on the
 *  diagonal of the covariance matrix. When this function is called on an
 *  off diagonal block, the function has no effect.
 */
void calculateStandardDeviations() {

  if ( this->isDiagonalBlock() ) {

    std::vector< double > sigmas;
    sigmas.reserve( this->rowMetadata().size() );

    for ( const auto& value : this->covariances().value().diagonal().reshaped() ) {

      sigmas.emplace_back( std::sqrt( value ) );
    }

    this->sigmas_ = sigmas;
  }
}
