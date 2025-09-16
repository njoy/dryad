static std::vector< Key > generateKeys( const id::ReactionID& reaction,
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
  keys.reserve( energies.size() * products.size() );
  for ( std::size_t i = 0; i < energies.size() - 1; ++i ) {

    for ( std::size_t j = 0; j < products.size(); ++j ) {

      keys.emplace_back( Key{ products[j], { energies[i], energies[i+1] }, reaction } );
    }
  }

  return keys;
}
