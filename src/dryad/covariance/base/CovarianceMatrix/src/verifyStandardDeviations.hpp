static void verifyStandardDeviations( std::size_t rows,
                                      std::size_t columns,
                                      std::size_t rowDeviations,
                                      std::size_t columnDeviations )
{

  if ( ( rowDeviations != rows ) || ( columnDeviations != columns ) ) {

    Log::error( "The provided number of standard deviations and the covariance "
                "matrix size are not consistent" );
    Log::info( "Covariance matrix number rows: {}", rows );
    Log::info( "Covariance matrix number columns: {}", columns );
    Log::info( "Number row standard deviations: {}", rowDeviations );
    Log::info( "Number column standard deviations: {}", columnDeviations );
    throw std::exception();
  }
}
