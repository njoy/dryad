/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ReichMoore() = default;

ReichMoore( const ReichMoore& ) = default;
ReichMoore( ReichMoore&& ) = default;

ReichMoore& operator=( const ReichMoore& ) = default;
ReichMoore& operator=( ReichMoore&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param boundary   the boundary condition
 *  @param channels   the channels of the spingroup
 */
ReichMoore( const BoundaryCondition& boundary,
            const std::vector< Channel >& channels ) :
    l_matrix_( selectLMatrix( channels.size() - 1, boundary ) ),
    r_matrix_( channels.size() - 1, channels.size() - 1 ),
    r_l_matrix_( channels.size() - 1, channels.size() - 1 ),
    t_matrix_( channels.size() - 1, channels.size() - 1 ),
    w_matrix_( channels.size() - 1, channels.size() - 1 ),
    u_matrix_( channels.size() - 1, channels.size() - 1 ),
    sqrt_p_matrix_( channels.size() - 1 ),
    omega_matrix_( channels.size() - 1 ),
    penetrabilities_( channels.size() - 1 ),
    shift_factors_( channels.size() - 1 ),
    phase_shifts_( channels.size() - 1 ),
    coulomb_phase_shifts_( channels.size() - 1 ),
    boundaries_( channels.size() - 1 ),
    below_threshold_( channels.size() - 1 ) {

  this->r_matrix_.setZero();
  this->r_l_matrix_.setZero();
  this->t_matrix_.setZero();
  this->w_matrix_.setZero();
  this->u_matrix_.setZero();
  verifyEliminatedChannel( channels );
}
