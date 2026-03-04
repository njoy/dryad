auto iterator( double temperature ) const {

  return std::lower_bound( this->braggEdgeData().begin(), this->braggEdgeData().end(),
                           temperature,
                           [] ( auto&& edges, auto&& right )
                              { return edges.temperature() < right; } );
}
