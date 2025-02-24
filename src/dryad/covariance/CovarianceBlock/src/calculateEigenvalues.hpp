/**
 *  @brief Calculate the eigenvalues from the covariances
 *
 *  The eigenvalues can only be calculated from covariance blocks on the
 *  diagonal of the covariance matrix. When this function is called on an
 *  off diagonal block, the function has no effect.
 */
void calculateEigenvalues() {

  if ( this->isDiagonalBlock() ) {

    // the SelfAdjointEigenSolver exploits the symmetric features of the matrix
    Eigen::SelfAdjointEigenSolver< Matrix< double > > solver( this->covariances().value() );

    std::vector< double > eigenvalues;
    eigenvalues.reserve( this->rowMetadata().size() );

    for ( const auto& value : solver.eigenvalues().reshaped() ) {

      eigenvalues.emplace_back( value );
    }

    this->eigenvalues_ = eigenvalues;
  }
}
