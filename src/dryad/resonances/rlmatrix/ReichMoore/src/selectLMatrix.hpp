static LMatrix selectLMatrix( unsigned int size, const BoundaryCondition& boundary ) {

  switch ( boundary ) {

    case BoundaryCondition::Constant : return lmatrix::Constant( size );
    case BoundaryCondition::ShiftFactor : return lmatrix::ShiftFactor( size );
    default : {

      throw std::runtime_error( "Unknown boundary condition type" );
    }
  }
}
