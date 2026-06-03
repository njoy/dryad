static void verifyTable( const std::vector< id::ChannelID >& channels,
                  const std::vector< double >& energies,
                  const std::vector< double >& spacingValues,
                  const std::vector< std::vector< double > >& widthValues ) {
  std::size_t nc = channels.size();
  std::size_t ne = energies.size();

  if ( nc  == 0 ) {
    Log::error( "At least one channel should be defined" );
    Log::info( "Number channels: {}", nc );
    throw std::exception(); 
  }
  auto energy = std::adjacent_find( energies.begin(), energies.end() );
  if ( energy != energies.end() ) {
    Log::warning( "The energies are not unique" );
    std::vector< double > duplicates;
    duplicates.insert( std::lower_bound( duplicates.begin(), duplicates.end(), *energy ), *energy );
    energy = std::adjacent_find( energy + 1, energies.end() );
    while ( energy != energies.end() ) {
      duplicates.insert( std::lower_bound( duplicates.begin(), duplicates.end(), *energy ), *energy );
      energy = std::adjacent_find( energy + 1, energies.end() );
    }
    duplicates.erase( std::unique( duplicates.begin(), duplicates.end() ), duplicates.end() );
    for ( double value : duplicates ) {
      Log::info( "The energy = {} appears more than once", value );
    }
  }

  auto channel = std::adjacent_find( channels.begin(), channels.end() );
  if ( channel != channels.end() ) {
    Log::error( "The channels are not unique" );
    Log::info( "The channel = {} appears more than once", channel->symbol() );
    throw std::exception();
  }

  if ( nc != widthValues.size() ) {
    Log::error( "The number of channel identifiers and the number of columns of "
                "average widths is not as expected" );
    Log::info( "Number channel identifiers: {}", nc );
    Log::info( "Number columns: {}", widthValues.size() );
    throw std::exception();
  }

  if ( ne != spacingValues.size() ) {
    Log::error( "The number of energies and the number of spacing values is not as expected" );
    Log::info( "Number energies: {}", ne );
    Log::info( "Number spacing values: {}", spacingValues.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < nc; ++i ) {
    if ( ne != widthValues[i].size() ) {
      Log::error( "The number of average widths for channel \'{}\' is not as expected", channels[i].symbol() );
      Log::info( "Number widths: {}", widthValues[i].size() );
      Log::info( "Expected number: {}", ne );
      throw std::exception();
    }
  }
}

static void verifyTable( const std::vector< id::ChannelID >& channels,
                         const std::vector< TabulatedAverageWidths >& widths,
                         const TabulatedLevelSpacing& spacings ) {

  std::size_t nc = channels.size();

  if ( nc == 0 ) {

    Log::error( "At least one channel should be defined" );
    Log::info( "Number channels: {}", nc );
    throw std::exception();
  }

  auto channel = std::adjacent_find( channels.begin(), channels.end() );
  if ( channel != channels.end() ) {

    Log::error( "The channels are not unique" );
    Log::info( "The channel = {} appears more than once", channel->symbol() );
    throw std::exception();
  }

  if ( nc != widths.size() ) {

    Log::error( "The number of channel identifiers and the number of average "
                "widths is not as expected" );
    Log::info( "Number channel identifiers: {}", nc );
    Log::info( "Number average widths: {}", widths.size() );
    throw std::exception();
  }

  const auto& reference = channels.front().quantumNumbers();
  for ( const auto& channel : channels ) {
    const auto& numbers = channel.quantumNumbers();
    if ( numbers.totalAngularMomentum() != reference.totalAngularMomentum() || 
         numbers.parity() != reference.parity() ||
         numbers.orbitalAngularMomentum() != reference.orbitalAngularMomentum() ) {
      Log::error( "All channels in UnresolvedResonanceTable must belong to the same Jpi spin group" );
      Log::info( "Reference Channel: \'{}\'", channels.front().symbol() );
      Log::info( "Conflicting Channel: \'{}\'",  channel.symbol() ); 
      throw std::exception(); 
    }
  }

}