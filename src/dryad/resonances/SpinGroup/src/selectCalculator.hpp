static Calculator selectCalculator( const Formalism& formalism,
                                    const BoundaryCondition& boundary,
                                    const std::vector< Channel >& channels,
                                    const ResonanceTable& table ) {

  switch ( formalism ) {

    case Formalism::ReichMoore : return calculator::ReichMoore( boundary, channels );
    case Formalism::GeneralRMatrix : return calculator::GeneralRMatrix( boundary, channels, table );
    default : {

      throw std::runtime_error( "Unknown formalism type" );
    }
  }
}
