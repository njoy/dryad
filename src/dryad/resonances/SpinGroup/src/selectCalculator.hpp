static Calculator selectCalculator( const Formalism& formalism,
                                    const BoundaryCondition& boundary,
                                    const std::vector< Channel >& channels ) {

  switch ( formalism ) {

    case Formalism::ReichMoore : return calculator::ReichMoore( boundary, channels );
    default : {

      throw std::runtime_error( "Unknown formalism type" );
    }
  }
}
