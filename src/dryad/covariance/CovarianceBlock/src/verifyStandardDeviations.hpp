static void verifyStandardDeviations( unsigned int rows,
                                      unsigned int columns,
                                      unsigned int rowDeviations,
                                      unsigned int columnDeviations )
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
