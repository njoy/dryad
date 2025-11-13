static void verifyCompatibility( const ResonanceTable& left, const ResonanceTable& right ) {

  // if there are common energies between the two tables: check for common channels
  std::vector< double > intersection( std::min( left.energies().size(), right.energies().size() ) );
  auto iter = std::set_intersection( left.energies().begin(), left.energies().end(),
                                     right.energies().begin(), right.energies().end(),
                                     intersection.begin() );
  if ( iter != intersection.begin() ) {

    std::vector< std::size_t > left_indices;
    std::vector< std::size_t > right_indices;
    for ( double energy : intersection ) {

      auto left_iter = std::lower_bound( left.energies().begin(), left.energies().end(), energy );
      auto right_iter = std::lower_bound( right.energies().begin(), right.energies().end(), energy );
      left_indices.emplace_back( std::distance( left.energies().begin(), left_iter ) );
      right_indices.emplace_back( std::distance( right.energies().begin(), right_iter ) );
    }

    for ( unsigned int i = 0; i < left.channels().size(); ++i ) {

      auto id = left.channels()[i];

      if ( right.hasChannel( id ) ) {

        auto channel_iter = std::lower_bound( right.channels().begin(), right.channels().end(), id );
        auto index = std::distance( right.channels().begin(), channel_iter );
        for ( unsigned int j = 0; j < intersection.size(); ++j ) {

          if ( left.reducedWidthAmplitudes()[i][left_indices[j]] != 0
               && right.reducedWidthAmplitudes()[index][right_indices[j]] != 0 ) {

            Log::error( "Found a channel where both tables have a non-zero width for a common level energy" );
            Log::info( "Channel: {}", id.symbol() );
            Log::info( "Energy: {}", intersection[j] );
            throw std::exception();
          }
        }
      }
    }
  }
}
