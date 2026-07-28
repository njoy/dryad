static void verifySpinGroup( const std::vector< UnresolvedChannel >& channels,
                             const UnresolvedResonanceTable& table ) {

  std::size_t nc = channels.size();
  if ( nc == 0 ) {

    Log::error( " At least one channel must be present in a spin group." );
    Log::info( "Number of channels: {}", nc );
    throw std::exception();
  }
  if ( nc != table.numberChannels() ) {

    Log::error( " The number of channels in the resonance table must match the number of channels in the spin group." );
    Log::info( "Number of channels in spin group: {}", nc );
    Log::info( "Number of channels in resonance table: {}", table.numberChannels() );
    throw std::exception();
  }

  auto iter = std::adjacent_find( channels.begin(), channels.end(),
                             [] ( auto&& left, auto&& right ) {

                               return left.identifier() == right.identifier();
                             } );
  if ( iter != channels.end() ) {

    Log::error( " Each channel in a spin group must have a unique identifier." );
    Log::info( "Duplicate channel identifier: {}", iter->identifier().symbol() );
    throw std::exception();
  }
}
