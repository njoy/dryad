/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
GeneralRMatrix() = default;

GeneralRMatrix( const GeneralRMatrix& ) = default;
GeneralRMatrix( GeneralRMatrix&& ) = default;

GeneralRMatrix& operator=( const GeneralRMatrix& ) = default;
GeneralRMatrix& operator=( GeneralRMatrix&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param boundary   the boundary condition
 *  @param channels   the channels of the spingroup
 */
GeneralRMatrix( const BoundaryCondition& boundary,
                const std::vector< Channel >& channels,
                const ResonanceTable& table ) :
    l_matrix_( selectLMatrix( channels.size(), boundary ) ),
    g_matrix_( makeGMatrix( table ) ),
    a_matrix_( table.numberEnergies(), table.numberEnergies() ),
    r_l_matrix_( channels.size(), channels.size() ),
    t_matrix_( channels.size(), channels.size() ),
    w_matrix_( channels.size(), channels.size() ),
    u_matrix_( channels.size(), channels.size() ),
    sqrt_p_matrix_( channels.size() ),
    omega_matrix_( channels.size() ),
    penetrabilities_( channels.size() ),
    shift_factors_( channels.size() ),
    phase_shifts_( channels.size() ),
    coulomb_phase_shifts_( channels.size() ),
    boundaries_( channels.size() ),
    below_threshold_( channels.size() ) {

  // set the matrices to zero
  this->a_matrix_.setZero();
  this->r_l_matrix_.setZero();
  this->t_matrix_.setZero();
  this->w_matrix_.setZero();
  this->u_matrix_.setZero();

  // precalculate stuff
  if ( boundary == BoundaryCondition::Constant ) {

    this->boundaryConditions( channels );
  }
}
