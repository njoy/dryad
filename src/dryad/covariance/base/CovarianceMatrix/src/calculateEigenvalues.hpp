/**
 *  @brief Calculate the eigenvalues from the covariances
 *
 *  The eigenvalues can only be calculated from blocks on the diagonal
 *  of the matrix. When this function is called on an off diagonal block,
 *  the function has no effect.
 *
 *  When this method is called on a block that has no covariances, the method
 *  has no effect.
 */
void calculateEigenvalues() {

  if ( this->isOnDiagonal() && this->covariances().has_value() ) {

    // the SelfAdjointEigenSolver exploits the symmetric features of the matrix
    Eigen::SelfAdjointEigenSolver< Matrix< double > > solver( this->covariances().value() );

    std::vector< double > eigenvalues;
    eigenvalues.reserve( this->rowKeys().size() );

    for ( const auto& value : solver.eigenvalues().reshaped() ) {

      eigenvalues.emplace_back( value );
    }

    this->eigenvalues_ = eigenvalues;
  }
}
