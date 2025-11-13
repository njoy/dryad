static std::vector< id::EnergyGroup >
generateEnergyGroups( const std::vector< double >& energies ) {

  std::vector< id::EnergyGroup > groups;
  groups.reserve( energies.size() );
  for ( std::size_t i = 0; i < energies.size() - 1; ++i ) {

    groups.emplace_back( energies[i], energies[i+1] );
  }
  return groups;
}
