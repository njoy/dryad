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
    l_matrix_( selectBoundaryCondition( channels.size() - 1, boundary ) ),
    shift_factors_( channels.size() - 1 ),
    boundaries_( channels.size() - 1 ),
    below_threshold_( channels.size() - 1 ),
    r_matrix_( channels.size() - 1, channels.size() - 1 ),
    r_l_matrix_( channels.size() - 1, channels.size() - 1 ) {

  this->r_matrix_.setZero();
  this->r_l_matrix_.setZero();
  verifyEliminatedChannel( channels );
}
