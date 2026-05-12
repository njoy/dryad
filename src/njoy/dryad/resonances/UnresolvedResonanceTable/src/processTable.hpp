static void processTable( std::vector< id::ChannelID >& channels,
                          std::vector< TabulatedAverageWidths >& widths) {

  if ( std::is_sorted( channels.begin(), channels.end() ) ) {
    return;
  }

  std::vector< std::size_t > order( channels.size() );
  std::iota( order.begin(), order.end(), 0 );
  std::sort( order.begin(), order.end(),
              [&] ( auto i, auto j ) { return channels[i] < channels[j]; } );

  tools::apply_permutation( channels, order );
  tools::apply_permutation( widths,   order );
  
}

static std::vector< TabulatedAverageWidths > buildWidths( std::vector< id::ChannelID > channels,
                          const std::vector< double >& energies,
                          const std::vector< std::vector< double > >& widthValues,
                          const std::vector< std::optional< int > >& dofs = {} ) {

  std::vector< TabulatedAverageWidths > widths;
  widths.reserve( widthValues.size() );

  for ( std::size_t i = 0; i < widthValues.size(); ++i ) {
    std::optional< int > dof = ( i < dofs.size() ) ? dofs[i] : std::nullopt;
    if ( ! dof.has_value() ) {
      widths.emplace_back( energies, widthValues[i] );
    }
    else {
      widths.emplace_back( dof.value(), energies, widthValues[i] );
    }
  }

  return widths;
}