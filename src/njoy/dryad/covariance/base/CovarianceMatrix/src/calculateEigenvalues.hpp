/**
 *  @brief Calculate the eigenvalues from the covariances
 *
 *  The eigenvalues can only be calculated from matrices on the diagonal
 *  of the full matrix. When this function is called on an off diagonal matrix,
 *  the function has no effect.
 *
 *  When the absolute value of an eigenvalue is within 10 times epsilon, the eigenvalue
 *  will get set to zero exactly.
 */
void calculateEigenvalues() {

  if ( this->isOnDiagonal() ) {

    // the SelfAdjointEigenSolver exploits the symmetric features of the matrix
    Eigen::SelfAdjointEigenSolver< matrix::Matrix< double > > solver( this->covariances() );

    std::vector< double > eigenvalues;
    eigenvalues.reserve( this->rowMetadata().keys().size() );

    for ( const auto& value : solver.eigenvalues().reshaped() ) {

      if ( scion::math::isCloseToZero( value, 10. * std::numeric_limits< double >::epsilon() ) ) {

        eigenvalues.emplace_back( 0. );
      }
      else {

        eigenvalues.emplace_back( value );
      }
    }

    this->eigenvalues_ = eigenvalues;
  }
}
