/**
 *  @brief Calculate the correlations (for covariance blocks on the diagonal)
 *
 *  The correlations can only be calculated without input of the standard
 *  deviations for covariance blocks on the diagonal of the covariance matrix.
 *  When this method is called on an off diagonal block, the method has no
 *  effect. Standard deviations will be calculated and stored as well.
 */
void calculateCorrelations() {

  if ( this->isDiagonalBlock() ) {

    this->calculateStandardDeviations();

    DiagonalMatrix< double > temporary( this->rowMetadata().size() );
    temporary.setIdentity();
    for ( unsigned int i = 0; i < this->rowMetadata().size(); ++i ) {

      temporary.diagonal()[i] /= this->standardDeviations().value()[i];
    }

    this->correlations_ = temporary * this->covariances().value() * temporary;
  }
}

/**
 *  @brief Calculate the correlations (for off diagonal covariance blocks)
 *
 *  The correlations can only be calculated with input of the standard deviations
 *  for covariance blocks that are off diagonal in the covariance matrix.
 *  Standard deviations will not be stored.
 *
 *  @param[in] rowDeviations      the standard deviations to be applied to each row
 *  @param[in] columnDeviations   the standard deviations to be applied to each column
 */
void calculateCorrelations( const std::vector< double >& rowDeviations,
                            const std::vector< double >& columnDeviations ) {

  verifyStandardDeviations( this->rowMetadata().size(),
                            this->columnMetadata().size(),
                            rowDeviations.size(),
                            columnDeviations.size() );

  DiagonalMatrix< double > left( this->rowMetadata().size() );
  left.setIdentity();
  for ( unsigned int i = 0; i < this->rowMetadata().size(); ++i ) {

    left.diagonal()[i] /= rowDeviations[i];
  }

  DiagonalMatrix< double > right( this->columnMetadata().size() );
  right.setIdentity();
  for ( unsigned int i = 0; i < this->columnMetadata().size(); ++i ) {

    right.diagonal()[i] /= columnDeviations[i];
  }

  this->correlations_ = left * this->covariances().value() * right;
}
