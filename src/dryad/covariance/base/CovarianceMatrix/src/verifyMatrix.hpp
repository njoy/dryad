static void verifyMatrix( const Matrix< double >& matrix,
                          unsigned int order ) {

  // check if the matrix is square
  if ( ! isSquare( matrix ) ) {

    Log::error( "The matrix for a diagonal block must be square" );
    throw std::exception();
  }

  // check if the matrix is symmetric
  if ( ! isSymmetric( matrix ) ) {

    Log::error( "The matrix for a diagonal block must be symmetric" );
    throw std::exception();
  }

  // check if the order of the square matrix is consistent with the
  // order obtained from the structure
  if ( matrix.rows() != order ) {

    Log::error( "The order of the square matrix and the order from the structure are not consistent" );
    Log::info( "Number rows: {}", matrix.rows() );
    Log::info( "Number columns: {}", matrix.cols() );
    Log::info( "Expected order: {}", order );
    throw std::exception();
  }
}

static void verifyMatrix( const std::vector< double >& deviations,
                          const Matrix< double >& matrix,
                          unsigned int order ) {

  verifyMatrix( matrix, order );

  // check if the number of deviation values is consistent with the
  // order obtained from the structure
  if ( deviations.size() != order ) {

    Log::error( "The number of standard deviation values and the order from the "
                "structure are not consistent" );
    Log::info( "Number standard deviation values: {}", deviations.size() );
    Log::info( "Expected order: {}", order );
    throw std::exception();
  }
}

static void verifyMatrix( const Matrix< double >& matrix,
                          unsigned int rows,
                          unsigned int columns ) {

  // check if the matrix dimensions are consistent with the structure
  if ( ( matrix.rows() != rows ) ||
       ( matrix.cols() != columns ) ) {

    Log::error( "The matrix dimensions and the structure are not consistent" );
    Log::info( "Number rows: {}", matrix.rows() );
    Log::info( "Number columns: {}", matrix.cols() );
    Log::info( "Expected number of rows: {}", rows );
    Log::info( "Expected nNumber of columns: {}", columns );
    throw std::exception();
  }
}
