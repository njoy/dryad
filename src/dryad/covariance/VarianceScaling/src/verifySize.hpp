static void verifySize( const std::vector< double >& energies,
                        const std::vector< double >& factors ) {

  // at least two elements in the energy boundary values
  if ( energies.size() < 2 ) {

    Log::error( "There must be at least 2 energy boundary values" );
    throw std::exception();
  }

  // the energy boundary values are sorted
  if ( !std::is_sorted( energies.begin(), energies.end() ) ) {

    Log::error( "The energy boundary values do not appear to be in ascending "
                "order" );
    throw std::exception();
  }

  // the energy boundary values are unique
  if ( energies.end() != std::adjacent_find( energies.begin(), energies.end() ) ) {

    Log::error( "The energy boundary values do not appear to be unique" );

    auto iter = std::adjacent_find( energies.begin(), energies.end() );
    while ( iter != energies.end() ) {

      Log::info( "Duplicate energy found: ", *iter );
      iter = std::adjacent_find( ++iter, energies.end() );
    }
    throw std::exception();
  }

  // check if the group structure size and
  if ( energies.size() - 1 != factors.size() ) {

    Log::error( "The number of groups and the number of scaling factors are not consistent" );
    Log::info( "Number energies: {}", energies.size() );
    Log::info( "Number factors: {}", factors.size() );
    Log::info( "Expected factors: {}", energies.size() - 1 );
    throw std::exception();
  }
}
