/**
 *  @brief Calculate the eigenvalues from the covariances
 *
 *  The eigenvalues can only be calculated from matrices on the diagonal
 *  of the full matrix. When this function is called on an off diagonal matrix,
 *  the function has no effect.
 *
 *  When the absolute value of an eigenvalue is equal to zero within 10 times epsilon,
 *  the eigenvalue will get set to zero exactly.
 */
void calculateEigenvalues() {

  if ( this->isOnDiagonal() ) {

    // the SelfAdjointEigenSolver exploits the symmetric features of the matrix
    Eigen::SelfAdjointEigenSolver< matrix::Matrix< double > > solver( this->covariances() );

    // create a vector for eigenvalues and eigenvectors
    std::size_t size = this->rowMetadata().keys().size();
    std::vector< double > eigenvalues;
    std::vector< matrix::Vector< double > > eigenvectors;
    eigenvalues.reserve( size );
    eigenvectors.reserve( size );

    // loop over the eigenvalues and eigenvectors
    for ( std::size_t i = 0; i < size; ++i ) {

      double eigenvalue = solver.eigenvalues()(i);
      if ( scion::math::isCloseToZero( eigenvalue, 10. * std::numeric_limits< double >::epsilon() ) ) {

        eigenvalue = 0.;
      }
      eigenvalues.emplace_back( eigenvalue );

      matrix::Vector< double > eigenvector = solver.eigenvectors().col(i);
      eigenvectors.emplace_back( eigenvector );
    }

    // reverse the order (eigenvalues are stored in descending order)
    std::reverse( eigenvalues.begin(), eigenvalues.end() );
    std::reverse( eigenvectors.begin(), eigenvectors.end() );

    //! @todo check efficiency compared to using std::upper_bound

    // move the vectors into the fields
    this->eigenvalues_ = std::move( eigenvalues );
    this->eigenvectors_ = std::move( eigenvectors );
  }
}
