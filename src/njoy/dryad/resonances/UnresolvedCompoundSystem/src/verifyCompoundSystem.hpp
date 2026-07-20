static void verifyCompoundSystem(
    double lower, double upper ) {

  if ( lower >= upper ) {

    Log::error( "The lower energy limit must be smaller than the upper energy limit" );
    Log::info( "Lower energy limit: {}", lower );
    Log::info( "Upper energy limit: {}", upper );
    throw std::exception();
  }

}
