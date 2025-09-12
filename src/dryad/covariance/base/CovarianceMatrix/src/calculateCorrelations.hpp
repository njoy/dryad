/**
 *  @brief Calculate the correlations (for on diagonal blocks on the diagonal)
 *
 *  The correlations can only be calculated without input of the standard
 *  deviations for blocks on the diagonal of the matrix. When this method
 *  is called on an off diagonal block, the method has no effect. Standard
 *  deviations will be calculated and stored as well.
 *
 *  When this method is called on a block that has no covariances, the method
 *  has no effect.
 */
void calculateCorrelations() {

  if ( this->isOnDiagonal() && this->covariances().has_value() ) {

    this->calculateStandardDeviations();

    DiagonalMatrix< double > temporary( this->rowKeys().size() );
    temporary.setIdentity();
    for ( unsigned int i = 0; i < this->rowKeys().size(); ++i ) {

      temporary.diagonal()[i] /= this->standardDeviations().value()[i];
      if ( std::isnan( temporary.diagonal()[i] ) ) {

        temporary.diagonal()[i] = 0;
      }
    }

    this->correlations_ = temporary * this->covariances().value() * temporary;
  }
}

/**
 *  @brief Calculate the correlations (for off diagonal blocks)
 *
 *  The correlations can only be calculated with input of the standard deviations
 *  for covariance blocks that are off diagonal in the covariance matrix.
 *  Standard deviations will not be stored.
 *
 *  When this method is called on a block that has no covariances, the method
 *  has no effect.
 *
 *  @param[in] rowDeviations      the standard deviations to be applied to each row
 *  @param[in] columnDeviations   the standard deviations to be applied to each column
 */
void calculateCorrelations( const std::vector< double >& rowDeviations,
                            const std::vector< double >& columnDeviations ) {

  if( this->covariances().has_value() ) {

    verifyStandardDeviations( this->rowKeys().size(),
                              this->columnKeys().size(),
                              rowDeviations.size(),
                              columnDeviations.size() );

    DiagonalMatrix< double > left( this->rowKeys().size() );
    left.setIdentity();
    for ( unsigned int i = 0; i < this->rowKeys().size(); ++i ) {

      left.diagonal()[i] /= rowDeviations[i];
      if ( std::isnan( left.diagonal()[i] ) ) {

        left.diagonal()[i] = 0;
      }
    }

    DiagonalMatrix< double > right( this->columnKeys().size() );
    right.setIdentity();
    for ( unsigned int i = 0; i < this->columnKeys().size(); ++i ) {

      right.diagonal()[i] /= columnDeviations[i];
      if ( std::isnan( left.diagonal()[i] ) ) {

        right.diagonal()[i] = 0;
      }
    }

    this->correlations_ = left * this->covariances().value() * right;
  }
}
