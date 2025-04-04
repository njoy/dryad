static void verifySize( std::size_t size, const UniformDistributionType& type ) {

  if ( type == UniformDistributionType::Discrete ) {

    if ( size == 0 ) {

      Log::error( "Expected at least 1 discrete value, found {}", size );
      throw std::exception();
    }
  }
  else {

    if ( size < 2 ) {

      Log::error( "Expected at least 2 values for an interval, found {}", size );
      throw std::exception();
    }
  }
}