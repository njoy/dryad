template < typename Range >
static double calculateTotalProbability( const Range& transitions ) {

  return std::accumulate( transitions.begin(), transitions.end(), 0.,
                          [] ( double value, auto&& transition )
                             { return value + transition.probability(); } );
}
