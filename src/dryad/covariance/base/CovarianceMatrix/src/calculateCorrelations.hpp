/**
 *  @brief Calculate the correlations (for on diagonal matrices)
 *
 *  The correlations can be calculated without input of the standard
 *  deviations for matrices on the diagonal of the full matrix. Standard
 *  deviations will be calculated and stored as well.
 *
 *  When this method is called on an off diagonal matrix, the method has
 *  no effect.
 */
void calculateCorrelations() {

  if ( this->isOnDiagonal() ) {

    this->calculateStandardDeviations();

    auto nrows = this->rowMetadata().keys().size();
    matrix::DiagonalMatrix< double > temporary( nrows );
    temporary.setIdentity();
    for ( unsigned int i = 0; i < nrows; ++i ) {

      temporary.diagonal()[i] /= this->standardDeviations().value()[i];
      if ( std::isnan( temporary.diagonal()[i] ) ) {

        temporary.diagonal()[i] = 0;
      }
    }

    this->correlations_ = temporary * this->covariances() * temporary;
  }
}

/**
 *  @brief Calculate the correlations (for off diagonal matrices)
 *
 *  The correlations can only be calculated with input of the standard deviations
 *  for covariance matrices that are off diagonal in the full covariance matrix.
 *  Standard deviations will not be stored.
 *
 *  @param[in] rowDeviations      the standard deviations to be applied to each row
 *  @param[in] columnDeviations   the standard deviations to be applied to each column
 */
void calculateCorrelations( const std::vector< double >& rowDeviations,
                            const std::vector< double >& columnDeviations ) {

  auto nrows = this->rowMetadata().keys().size();
  auto ncols = this->columnMetadata().keys().size();

  verifyStandardDeviations( nrows,
                            ncols,
                            rowDeviations.size(),
                            columnDeviations.size() );

  matrix::DiagonalMatrix< double > left( nrows );
  left.setIdentity();
  for ( unsigned int i = 0; i < nrows; ++i ) {

    left.diagonal()[i] /= rowDeviations[i];
    if ( std::isnan( left.diagonal()[i] ) ) {

      left.diagonal()[i] = 0;
    }
  }

  matrix::DiagonalMatrix< double > right( ncols );
  right.setIdentity();
  for ( unsigned int i = 0; i < ncols; ++i ) {

    right.diagonal()[i] /= columnDeviations[i];
    if ( std::isnan( right.diagonal()[i] ) ) {

      right.diagonal()[i] = 0;
    }
  }

  this->correlations_ = left * this->covariances() * right;
}
