static LMatrix selectLMatrix( unsigned int size, const BoundaryCondition& boundary ) {

  switch ( boundary ) {

    case BoundaryCondition::Constant : return Constant( size );
    case BoundaryCondition::ShiftFactor : return ShiftFactor( size );
    default : {

      throw std::runtime_error( "Unknown boundary condition type" );
    }
  }
}
