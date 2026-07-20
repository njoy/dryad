void processSpinGroups() {

  std::sort( this->spinGroups().begin(), this->spinGroups().end(),
             [] ( auto&& left, auto&& right ) { 
                  return std::make_tuple( left.totalAngularMomentum(), left.parity(), left.orbitalAngularMomentum() ) <
                         std::make_tuple( right.totalAngularMomentum(), right.parity(), right.orbitalAngularMomentum() ); 
             } );

  for ( const auto& group : this->spinGroups() ) {

    for ( const auto& reaction : group.reactions() ) {

      auto iter = std::lower_bound( this->reactions().begin(),
                                    this->reactions().end(), reaction );
      if ( ! ( iter != this->reactions().end() && *iter == reaction ) ) {

        this->reactions().insert( iter, reaction );
      }
    }
  }
}
