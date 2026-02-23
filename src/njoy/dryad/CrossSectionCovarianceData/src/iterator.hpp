auto iterator( const id::ReactionID& row, const id::ReactionID& column ) const {

  auto compare = [] ( auto&& left, auto&& right ) {

    auto get_tie = tools::overload{

      [] ( const covariance::CrossSectionCovarianceMatrix& entry ) {

        return std::tie( entry.rowMetadata().reactionIdentifiers().front(),
                         entry.columnMetadata().reactionIdentifiers().front() );
      },
      [] ( const std::vector< covariance::CrossSectionCovarianceMatrix >& entry ) {

        return std::tie( entry.front().rowMetadata().reactionIdentifiers().front(),
                         entry.front().columnMetadata().reactionIdentifiers().front() );
      }
    };

    return std::visit( get_tie, left ) < right;
  };

  auto iter = std::lower_bound( this->covariances().begin(), this->covariances().end(),
                                std::tie( row, column ),
                                compare );
  return iter;
}
