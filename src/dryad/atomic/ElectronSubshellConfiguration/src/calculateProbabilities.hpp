void calculateProbabilities() noexcept {

  //! @todo do we want to normalise these probability values?

  if ( this->hasTransitions() ) {

    auto sum = [] ( double value, auto&& transition )
                  { return value + transition.probability(); };
    this->radiative_probability_ = std::accumulate( this->radiativeTransitions().begin(),
                                                    this->radiativeTransitions().end(),
                                                    0., sum );
    this->nonradiative_probability_ = std::accumulate( this->nonRadiativeTransitions().begin(),
                                                       this->nonRadiativeTransitions().end(),
                                                       0., sum );
  }
}