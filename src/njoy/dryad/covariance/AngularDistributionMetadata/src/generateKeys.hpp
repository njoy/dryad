static std::vector< Key > generateKeys( const std::vector< id::ReactionID >& reactions,
                                        const std::vector< double >& energies,
                                        const std::vector< std::size_t >& moments ) {

  if ( moments.size() == 0 || energies.size() < 2 || reactions.size() == 0 ) {

    Log::error( "There should be at least 1 Legendre moment, 2 energy values and 1 reaction identifier." );
    throw std::exception();
  }
  if ( ! std::is_sorted( energies.begin(), energies.end() ) ) {

    Log::error( "The energy group values do not appear to be sorted." );
    throw std::exception();
  }

  std::vector< Key > keys;
  keys.reserve( reactions.size() * ( energies.size() - 1 ) );
  for ( std::size_t i = 0; i < reactions.size(); ++i ) {

    for ( std::size_t j = 0; j < energies.size() - 1; ++j ) {

      for ( std::size_t k = 0; k < moments.size(); ++k ) {

        keys.emplace_back( Key{ reactions[i], { energies[j], energies[j+1] },
                                moments[k] } );
      }
    }
  }
  return keys;
}
