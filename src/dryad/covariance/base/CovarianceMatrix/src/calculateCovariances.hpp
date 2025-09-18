/**
 *  @brief Calculate the covariances (for on diagonal blocks)
 *
 *  The covariances can be calculated without input of the standard
 *  deviations for blocks on the diagonal of the matrix.
 *
 *  When this method is called on an off diagonal block, the method has no effect.
 *
 *  When this method is called on a block that has no correlations, the method
 *  has no effect.
 */
void calculateCovariances() {

  if ( this->isOnDiagonal() && this->correlations().has_value() ) {

    DiagonalMatrix< double > temporary( this->rowKeys().size() );
    temporary.setIdentity();
    for ( unsigned int i = 0; i < this->rowKeys().size(); ++i ) {

      temporary.diagonal()[i] = this->standardDeviations().value()[i];
    }

    this->covariances_ = temporary * this->correlations().value() * temporary;
  }
}

/**
 *  @brief Calculate the covariances (for off diagonal blocks)
 *
 *  The covariances can only be calculated with input of the standard deviations
 *  for blocks that are off diagonal in the matrix. Standard deviations will not
 *  be stored.
 *
 *  When this method is called on a block that has no correlations, the method
 *  has no effect.
 *
 *  @param[in] rowDeviations      the standard deviations to be applied to each row
 *  @param[in] columnDeviations   the standard deviations to be applied to each column
 */
void calculateCovariances( const std::vector< double >& rowDeviations,
                           const std::vector< double >& columnDeviations ) {

  if ( this->correlations().has_value() ) {

    verifyStandardDeviations( this->rowKeys().size(),
                              this->columnKeys().size(),
                              rowDeviations.size(),
                              columnDeviations.size() );

    DiagonalMatrix< double > left( this->rowKeys().size() );
    left.setIdentity();
    for ( unsigned int i = 0; i < this->rowKeys().size(); ++i ) {

      left.diagonal()[i] = rowDeviations[i];
    }

    DiagonalMatrix< double > right( this->columnKeys().size() );
    right.setIdentity();
    for ( unsigned int i = 0; i < this->columnKeys().size(); ++i ) {

      right.diagonal()[i] = columnDeviations[i];
    }

    this->covariances_ = left * this->correlations().value() * right;
  }
}
