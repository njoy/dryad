template < typename Iterator >
static double calculateProbability(  Iterator begin, Iterator end  ) {

  return std::accumulate( begin, end, 0.,
                          [] ( double value, auto&& transition )
                             { return value + transition.probability(); } );
}
