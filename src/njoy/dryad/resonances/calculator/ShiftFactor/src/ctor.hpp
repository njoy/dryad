/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ShiftFactor() = default;

ShiftFactor( const ShiftFactor& ) = default;
ShiftFactor( ShiftFactor&& ) = default;

ShiftFactor& operator=( const ShiftFactor& ) = default;
ShiftFactor& operator=( ShiftFactor&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param size   the size of the L matrix (the number of channels)
 */
ShiftFactor( unsigned int size ) :
    l_matrix_( size ) {

  this->matrix().setZero();
}
