static std::vector< Key > generateKeys( const std::vector< id::ReactionID >& reactions,
                                        const std::vector< double >& energies ) {

  if ( energies.size() < 2 || reactions.size() == 0 ) {

    Log::error( "There should be at least 2 energy values and 1 reaction identifier." );
    throw std::exception();
  }
  if ( ! std::is_sorted( energies.begin(), energies.end() ) ) {

    Log::error( "The energy group values do note appear to be sorted." );
    throw std::exception();
  }

  std::vector< Key > keys;
  keys.reserve( reactions.size() * ( energies.size() - 1 ) );
  for ( std::size_t i = 0; i < reactions.size(); ++i ) {

    for ( std::size_t j = 0; j < energies.size() - 1; ++j ) {

      keys.emplace_back( Key{ reactions[i], { energies[j], energies[j+1] } } );
    }
  }
  return keys;
}
