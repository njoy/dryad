/**
 *  @brief Extract a submatrix from the covariance matrix based
 *         on selected values of the keys
 */
CovarianceMatrix extract( const std::optional< Ts >&... args ) const {

  Selection select = std::make_tuple( args... );

  std::vector< std::size_t > rows;
  std::vector< Key > rowKeys;
  for ( std::size_t i = 0; i < this->rowKeys().size(); ++i ) {

    if ( compare_key( select, this->rowKeys()[i] ) ) {

      rows.emplace_back( i );
      rowKeys.emplace_back( this->rowKeys()[i] );
    }
  }

  if ( this->isOnDiagonal() ) {

    auto size = rows.size();
    dryad::covariance::Matrix< double > matrix( size, size );
    for ( unsigned int i = 0; i < size; ++i ) {

      for ( unsigned int j = 0; j < size; ++j ) {

        matrix( i, j ) = this->covariances()( rows[i], rows[j] );
      }
    }

    return CovarianceMatrix( std::move( rowKeys ), std::move( matrix ),
                             this->isRelativeMatrix() );
  }
  else {

    std::vector< std::size_t > columns;
    std::vector< Key > columnKeys;
    for ( std::size_t i = 0; i < this->columnKeys().size(); ++i ) {

      if ( compare_key( select, this->columnKeys()[i] ) ) {

        columns.emplace_back( i );
        columnKeys.emplace_back( this->columnKeys()[i] );
      }
    }

    auto size1 = rows.size();
    auto size2 = columns.size();
    dryad::covariance::Matrix< double > matrix( size1, size2 );
    for ( unsigned int i = 0; i < size1; ++i ) {

      for ( unsigned int j = 0; j < size2; ++j ) {

        matrix( i, j ) = this->covariances()( rows[i], columns[j] );
      }
    }

    if ( rowKeys == columnKeys ) {

      return CovarianceMatrix( std::move( rowKeys ), std::move( matrix ),
                               this->isRelativeMatrix() );
    }
    else {

      return CovarianceMatrix( std::move( rowKeys ), std::move( columnKeys ),
                               std::move( matrix ), this->isRelativeMatrix() );
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

    Selection select_row = std::make_tuple( row_args... );
    Selection select_col = std::make_tuple( col_args... );

    std::vector< std::size_t > rows;
    std::vector< Key > rowKeys;
    for ( std::size_t i = 0; i < this->rowKeys().size(); ++i ) {

      if ( compare_key( select_row, this->rowKeys()[i] ) ) {

        rows.emplace_back( i );
        rowKeys.emplace_back( this->rowKeys()[i] );
      }
    }

    std::vector< std::size_t > columns;
    std::vector< Key > columnKeys;
    for ( std::size_t i = 0; i < this->columnKeys().size(); ++i ) {

      if ( compare_key( select_col, this->columnKeys()[i] ) ) {

        columns.emplace_back( i );
        columnKeys.emplace_back( this->columnKeys()[i] );
      }
    }

    auto size1 = rows.size();
    auto size2 = columns.size();
    dryad::covariance::Matrix< double > matrix( size1, size2 );
    for ( unsigned int i = 0; i < size1; ++i ) {

      for ( unsigned int j = 0; j < size2; ++j ) {

        matrix( i, j ) = this->covariances()( rows[i], columns[j] );
      }
    }

    if ( rowKeys == columnKeys ) {

      return CovarianceMatrix( std::move( rowKeys ), std::move( matrix ),
                               this->isRelativeMatrix() );
    }
    else {

      return CovarianceMatrix( std::move( rowKeys ), std::move( columnKeys ),
                               std::move( matrix ), this->isRelativeMatrix() );
    }
  }
}
