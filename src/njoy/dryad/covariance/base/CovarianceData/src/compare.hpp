static bool
compare( const id::ReactionID& row, const id::ReactionID& column,
         const Covariance& covariance ) {

  auto get_tie = tools::overload{

    [] ( const CovarianceMatrix& entry ) {

      return std::tie( entry.rowMetadata().reactionIdentifiers().front(),
                       entry.columnMetadata().reactionIdentifiers().front() );
    },
    [] ( const std::vector< CovarianceMatrix >& entry ) {

      return std::tie( entry.front().rowMetadata().reactionIdentifiers().front(),
                       entry.front().columnMetadata().reactionIdentifiers().front() );
    }
  };

  return std::tie( row, column ) == std::visit( get_tie, covariance );
}
