static void unifyEnergyGrids( std::vector< TabulatedAverageWidths >& widths, TabulatedLevelSpacing& spacings ) {

  const auto& referenceGrid = spacings.energies();
  bool allMatch = std::all_of( widths.begin(), widths.end(),
                               [&] ( const TabulatedAverageWidths& w ) { return w.energies() == referenceGrid; } 
                              );
  if ( allMatch ) {
    return;
  }

  std::vector< double > unionGrid;
  unionGrid.insert( unionGrid.end(), referenceGrid.begin(), referenceGrid.end() );
  for ( const auto& width : widths ) {
    const auto& energies = width.energies();
    unionGrid.insert( unionGrid.end(), energies.begin(), energies.end() );
  }
  std::sort( unionGrid.begin(), unionGrid.end() );
  unionGrid.erase( std::unique( unionGrid.begin(), unionGrid.end() ), unionGrid.end() );

  std::vector< double > spacingValues(unionGrid.size());
  for ( size_t i = 0; i < unionGrid.size(); ++i ) {
    spacingValues[i] = spacings( unionGrid[i] );
  }
  spacings = TabulatedLevelSpacing( unionGrid, spacingValues );

  for ( auto& width : widths ) {
    std::vector< double > widthValues(width.energies().size());
    for ( size_t i = 0; i < width.energies().size(); ++i ) {
      widthValues[i] = width( width.energies()[i] );
    }
    if ( width.degreesOfFreedom().has_value() ) {
      width = TabulatedAverageWidths( width.degreesOfFreedom().value(), unionGrid, widthValues);
    } else {
      width = TabulatedAverageWidths(unionGrid, widthValues);
    }
  }

}
