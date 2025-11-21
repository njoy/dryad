static
void verifyTable( const std::vector< id::ChannelID >& channels,
                  const std::vector< double >& energies,
                  const std::vector< std::vector< double > >& amplitudes ) {

  std::size_t nc = channels.size();
  std::size_t ne = energies.size();

  if ( nc  == 0 ) {

    Log::error( "At least one channel should be defined" );
    Log::info( "Number channels: {}", nc );
    throw std::exception();
  }

  auto energy = std::adjacent_find( energies.begin(), energies.end() );
  if ( energy != energies.end() ) {

    Log::error( "The energies are not unique" );
    Log::info( "The energy = {} appears more than once", *energy );
    throw std::exception();
  }

  auto channel = std::adjacent_find( channels.begin(), channels.end() );
  if ( channel != channels.end() ) {

    Log::error( "The channels are not unique" );
    Log::info( "The channel = {} appears more than once", channel->symbol() );
    throw std::exception();
  }

  if ( nc != amplitudes.size() ) {

    Log::error( "The number of channel identifiers and the number of columns of "
                "reduced width amplitudes is not as expected" );
    Log::info( "Number channel identifiers: {}", nc );
    Log::info( "Number columns: {}", amplitudes.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < nc; ++i ) {

    if ( ne != amplitudes[i].size() ) {

      Log::error( "The number of reduced width amplitudes for channel \'{}\' is not as expected" );
      Log::info( "Number widths: {}", amplitudes[i].size() );
      Log::info( "Expected number: {}", ne );
      throw std::exception();
    }
  }
}
