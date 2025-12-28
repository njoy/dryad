template < typename Range >
static double calculateAverageEnergy( const Range& transitions ) {

  if ( transitions.size() > 0 ) {

    double average = 0.;
    double probability = 0.;
    for ( const auto& transition : transitions ) {

      average += transition.energy().value() * transition.probability();
      probability += transition.probability();
    }
    return average / probability;
  }
  else {

    return 0.;
  }
}
