static std::vector< Key > generateKeys( std::vector< double > energies,
                                        std::vector< id::ParticleID > products ) {

  if ( energies.size() < 2 || products.size() == 0 ) {

    Log::error( "There should be at least 2 energy values and 1 product identifier." );
    throw std::exception();
  }

  std::vector< Key > keys;
  keys.reserve( energies.size() * products.size() );
  for ( unsigned int i = 0; i < energies.size() - 1; ++i ) {

    for ( unsigned int j = 0; j < products.size(); ++j ) {

      keys.emplace_back( id::EnergyGroup( energies[i], energies[i+1] ), products[j] );
    }
  }

  return keys;
}
