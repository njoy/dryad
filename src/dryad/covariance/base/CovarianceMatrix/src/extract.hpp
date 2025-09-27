private:

static std::vector< Key >
extractKeys( const std::vector< std::size_t >& indices,
             const std::vector< Key >& keys ) {

  std::vector< Key > extracted;
  extracted.reserve( indices.size() );
  for ( std::size_t index : indices ) {

    extracted.emplace_back( keys[index] );
  }
  return extracted;
}

dryad::covariance::Matrix< double >
extractMatrix( const std::vector< std::size_t >& rows,
               const std::vector< std::size_t >& columns ) const {

  auto size1 = rows.size();
  auto size2 = columns.size();
  dryad::covariance::Matrix< double > matrix( size1, size2 );
  for ( unsigned int i = 0; i < size1; ++i ) {

    for ( unsigned int j = 0; j < size2; ++j ) {

      matrix( i, j ) = this->covariances()( rows[i], columns[j] );
    }
  }
  return matrix;
}

public:

/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
CovarianceMatrix extract( const std::optional< Ts >&... args ) const {

  auto rows = this->rowMetadata().selection( args... );
  auto rowKeys = extractKeys( rows, this->rowMetadata().keys() );
  if ( this->isOnDiagonal() ) {

    return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                             this->extractMatrix( rows, rows ),
                             this->isRelativeMatrix() );
  }
  else {

    auto columns = this->columnMetadata().selection( args... );
    auto columnKeys = extractKeys( columns, this->columnMetadata().keys() );
    if ( rowKeys == columnKeys ) {

      return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                               this->extractMatrix( rows, columns ),
                               this->isRelativeMatrix() );
    }
    else {

      return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                               Metadata( std::move( columnKeys ) ),
                               this->extractMatrix( rows, columns ),
                               this->isRelativeMatrix() );
    }
  }
}

/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
CovarianceMatrix extract( const std::optional< Ts >&... row_args,
                          const std::optional< Ts >&... col_args ) const {

  if ( std::tie( row_args... ) == std::tie( col_args... ) ) {

    return this->extract( row_args... );
  }
  else {

    auto rows = this->rowMetadata().selection( row_args... );
    auto columns = this->columnMetadata().selection( col_args... );
    auto rowKeys = extractKeys( rows, this->rowMetadata().keys() );
    auto columnKeys = extractKeys( columns, this->columnMetadata().keys() );

    if ( rowKeys == columnKeys ) {

      return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                               this->extractMatrix( rows, columns ),
                               this->isRelativeMatrix() );
    }
    else {

      return CovarianceMatrix( Metadata( std::move( rowKeys ) ),
                               Metadata( std::move( columnKeys ) ),
                               this->extractMatrix( rows, columns ),
                               this->isRelativeMatrix() );
    }
  }
}
