static void processTable( std::vector< id::ChannelID >& channels,
                          std::vector< TabulatedAverageWidths >& widths) {

  if ( std::is_sorted( channels.begin(), channels.end() ) ) {
    return;
  }

  std::vector< std::size_t > order( channels.size() );
  std::iota( order.begin(), order.end(), 0 );
  std::sort( order.begin(), order.end(),
              [&] ( auto i, auto j ) { return channels[i] < channels[j]; } );

  auto orderCopy = order;
  tools::apply_permutation( channels, order );
  tools::apply_permutation( widths,   orderCopy );
  
}