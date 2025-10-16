static
void verifyTable( const std::vector< id::ChannelID >& channels,
                  const std::vector< double >& energies,
                  const std::vector< std::vector< double > >& amplitudes ) {

  std::size_t nc = channels.size();
  std::size_t ne = energies.size();

  if ( nc  == 0 || ne == 0 ) {

    Log::error( "At least one channel and one resonance should be defined" );
    Log::info( "Number channels: {}", nc );
    Log::info( "Number resonances: {}", ne );
    throw std::exception();
  }

  if ( nc != amplitudes.size() ) {

    Log::error( "The number of channel identifiers and the number of columns of "
                "reduced amplitude widths is not as expected" );
    Log::info( "Number channel identifiers: {}", nc );
    Log::info( "Number columns: {}", amplitudes.size() );
    throw std::exception();
  }

  for ( unsigned int i = 0; i < nc; ++i ) {

    if ( ne != amplitudes[i].size() ) {

      Log::error( "The number of reduced amplitude widths for channel \'{}\' is not as expected" );
      Log::info( "Number widhts: {}", amplitudes[i].size() );
      Log::info( "Expected number: {}", ne );
      throw std::exception();
    }
  }
}
