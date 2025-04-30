static void verifySize( std::size_t reactions, std::size_t coefficients ) {

  if ( reactions != coefficients ) {

    Log::error( "The number of reactions and number of coefficients provided are not consistent" );
    Log::info( "Number reactions: {}", reactions );
    Log::info( "Number coefficients: {}", coefficients );
    throw std::exception();
  }
  if ( reactions < 1 ) {

    Log::error( "Expected at least one reaction involved in the linear combination" );
    Log::info( "Number reactions: {}", reactions );
    Log::info( "Number coefficients: {}", coefficients );
    throw std::exception();
  }
}