auto iterator( double temperature ) const {

  return std::lower_bound( this->braggEdges().begin(), this->braggEdges().end(),
                           temperature,
                           [] ( auto&& edges, auto&& right )
                              { return edges.temperature() < right; } );
}
