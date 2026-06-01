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