/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
Constant() = default;

Constant( const Constant& ) = default;
Constant( Constant&& ) = default;

Constant& operator=( const Constant& ) = default;
Constant& operator=( Constant&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param size   the size of the L matrix (the number of channels)
 */
Constant( unsigned int size ) :
    l_matrix_( size ) {

  this->matrix().setZero();
}
