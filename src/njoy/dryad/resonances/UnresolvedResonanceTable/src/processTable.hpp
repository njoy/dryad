static auto processTable( std::vector< id::ChannelID > channels,
                          std::vector< TabulatedAverageWidths > widths,
                          TabulatedLevelSpacing spacings ) {

  if ( ! std::is_sorted( channels.begin(), channels.end() ) ) {

    std::vector< std::size_t > order( channels.size() );
    std::iota( order.begin(), order.end(), 0 );
    std::sort( order.begin(), order.end(),
               [&] ( auto i, auto j ) { return channels[i] < channels[j]; } );

    tools::apply_permutation( channels, order );
    tools::apply_permutation( widths,   order );
  }

  return std::make_tuple( std::move( channels ),
                          std::move( widths ),
                          std::move( spacings ) );
}

static auto processTable( std::vector< id::ChannelID > channels,
                          const std::vector< double >& energies,
                          const std::vector< double >& spacingValues,
                          const std::vector< std::vector< double > >& widthValues,
                          const std::vector< std::optional< int > >& dofs = {} ) {

  TabulatedLevelSpacing spacings( energies, spacingValues );
  std::vector< TabulatedAverageWidths > widths;
  widths.reserve( widthValues.size() );

  for ( std::size_t i = 0; i < widthValues.size(); ++i ) {
    const auto& width = widthValues[i];
    std::optional< int > dof = ( i < dofs.size() ) ? dofs[i] : std::nullopt;
    if ( ! dof.has_value() ) {
      widths.emplace_back( energies, width );
    }
    else {
      widths.emplace_back( dof.value(), energies, width );
    }
  }

  return processTable( std::move( channels ),
                       std::move( widths ),
                       std::move( spacings ) );
}

static auto processTable( std::vector< id::ChannelID > channels ) {

  std::vector< TabulatedAverageWidths > widths( channels.size() );
  TabulatedLevelSpacing spacings;
  return processTable( std::move( channels ),
                       std::move( widths ),
                       std::move( spacings ) );
}