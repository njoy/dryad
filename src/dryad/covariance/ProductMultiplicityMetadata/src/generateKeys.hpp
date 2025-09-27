static std::vector< Key > generateKeys( const std::vector< id::ReactionID >& reactions,
                                        const std::vector< double >& energies,
                                        const std::vector< id::ParticleID >& products ) {

  if ( energies.size() < 2 || products.size() == 0 ) {

    Log::error( "There should be at least 2 energy values and 1 product identifier." );
    throw std::exception();
  }
  if ( ! std::is_sorted( energies.begin(), energies.end() ) ) {

    Log::error( "The energy group values do note appear to be sorted." );
    throw std::exception();
  }
  if ( ! std::is_sorted( products.begin(), products.end() ) ) {

    Log::error( "The product identifiers do not appear to be sorted." );
    throw std::exception();
  }

  std::vector< Key > keys;
  keys.reserve( reactions.size() * ( energies.size() - 1 ) * products.size() );
  for ( std::size_t i = 0; i < reactions.size(); ++i ) {

    for ( std::size_t j = 0; j < energies.size() - 1; ++j ) {

      for ( std::size_t k = 0; k < products.size(); ++k ) {

        keys.emplace_back( Key{ reactions[i], { energies[j], energies[j+1] }, products[k] } );
      }
    }
  }
  return keys;
}
