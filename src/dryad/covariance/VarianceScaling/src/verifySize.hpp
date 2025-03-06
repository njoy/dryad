static void verifySize( unsigned int energies, unsigned int factors ) {

  // at least two elements in the energy boundary values
  if ( energies < 2 ) {

    Log::error( "There must be at least 2 energy boundary values" );
    throw std::exception();
  }

  // check if the group structure size and
  if ( energies - 1 != factors ) {

    Log::error( "The number of groups and the number of scaling factors are not consistent" );
    Log::info( "Number energies: {}", energies );
    Log::info( "Number factors: {}", factors );
    Log::info( "Expected factors: {}", energies - 1 );
    throw std::exception();
  }
}
