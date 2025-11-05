static void verifySpinGroup( const std::vector< Channel >& channels,
                             const ResonanceTable& table ) {

  std::size_t nc = channels.size();

  if ( nc  == 0 ) {

    Log::error( "At least one channel should be defined" );
    Log::info( "Number channels: {}", nc );
    throw std::exception();
  }
  if ( nc != table.numberChannels() ) {

    Log::error( "The number of channels and the number of columns in the table are inconsistent" );
    Log::info( "Number channels: {}", channels.size() );
    Log::info( "Number columns in the table: {}", table.numberChannels() );
    throw std::exception();
  }

  auto iter = std::adjacent_find( channels.begin(), channels.end(),
                                  [] ( auto&& left, auto&& right )
                                     { return left.identifier() == right.identifier(); } );
  if ( iter != channels.end() ) {

    Log::error( "Channels in the spin group do not seem to be unique." );
    Log::info( "Channel \'{}\' is present at least twice", iter->identifier().symbol() );
    throw std::exception();
  }
}
