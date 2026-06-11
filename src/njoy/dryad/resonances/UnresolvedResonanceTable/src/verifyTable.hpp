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