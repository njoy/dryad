static std::pair< std::vector< id::ReactionID >, std::vector< Covariance > >
generateCovariances( std::vector< CovarianceMatrix > submatrices ) {

  // we are assuming the following:
  //   - all submatrices are for a single ProjectileTarget
  //   - each submatrix is for a single row and column reaction
  //   - all submatrices are on diagonal or above the diagonal

  std::vector< id::ReactionID > reactions;
  std::vector< Covariance > covariances;

  Derived::sort( submatrices );

  auto add_reaction = [] ( std::vector< id::ReactionID >& reactions, const id::ReactionID& id ) {

    auto iter = std::lower_bound( reactions.begin(), reactions.end(), id );
    if ( iter == reactions.end() || id != *iter ) {

      reactions.insert( iter, id );
    }
  };

  auto iter = submatrices.begin();
  while ( iter != submatrices.end() ) {

    auto row = iter->rowMetadata().reactionIdentifiers().front();
    auto column = iter->columnMetadata().reactionIdentifiers().front();

    add_reaction( reactions, row );
    add_reaction( reactions, column );

    auto next = std::upper_bound( iter, submatrices.end(),
                                  std::tie( row, column ),
                                  [] ( auto&& left, auto&& right )
                                     { return left < std::tie( right.rowMetadata().reactionIdentifiers().front(),
                                                               right.columnMetadata().reactionIdentifiers().front() ); } );

    auto size = std::distance( iter, next );
    if ( size > 1 ) {

      std::vector< CovarianceMatrix > entries;
      entries.reserve( size );
      std::move( iter, next, std::back_inserter( entries ) );

      covariances.emplace_back( std::move( entries ) );
    }
    else {

      covariances.emplace_back( std::move( *iter ) );
    }

    iter = next;
  }

  return std::make_pair( std::move( reactions ), std::move( covariances ) );
}
