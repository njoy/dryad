static auto processTable( std::vector< id::ChannelID > channels,
                          std::vector< double > energies,
                          std::vector< std::vector< double > > amplitudes ) {

  // verify if the channels are sorted by channel id
  if ( ! std::is_sorted( channels.begin(), channels.end() ) ) {

    // get the order
    std::vector< std::size_t > order( channels.size() );
    std::iota( order.begin(), order.end(), 0 );
    std::sort( order.begin(), order.end(),
               [&] ( auto&& i, auto&& j ) { return channels[i] < channels[j]; } );

    // sort the channels and perform a permutation on the columns
    std::sort( channels.begin(), channels.end() );
    tools::apply_permutation( amplitudes, order );
  }

  // verify if the energies are sorted
  if ( ! std::is_sorted( energies.begin(), energies.end() ) ) {

    // get the order
    std::vector< std::size_t > order( energies.size() );
    std::iota( order.begin(), order.end(), 0 );
    std::sort( order.begin(), order.end(),
               [&] ( auto&& i, auto&& j ) { return energies[i] < energies[j]; } );

    // sort the energies and perform a permutation on each column
    std::sort( energies.begin(), energies.end() );
    if ( amplitudes.size() == 1 ) {

      tools::apply_permutation( amplitudes.front(), order );
    }
    else {

      for ( auto& column : amplitudes ) {

        auto temp = order;
        tools::apply_permutation( column, temp );
      }
    }
  }

  return std::make_tuple( std::move( channels ), std::move( energies ), std::move( amplitudes ) );
}