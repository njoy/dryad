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
}
