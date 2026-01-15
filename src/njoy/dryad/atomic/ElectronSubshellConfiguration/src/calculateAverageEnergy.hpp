template < typename Iterator >
static double calculateAverageEnergy( Iterator begin, Iterator end ) {

  if ( std::distance( begin, end ) > 0 ) {

    double average = 0.;
    double probability = 0.;
    while ( begin != end ) {

      average += begin->energy().value() * begin->probability();
      probability += begin->probability();
      ++begin;
    }
    return average / probability;
  }
  else {

    return 0.;
  }
}
