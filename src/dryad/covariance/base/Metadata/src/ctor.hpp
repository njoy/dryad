/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
Metadata() = default;

Metadata( const Metadata& ) = default;
Metadata( Metadata&& ) = default;

Metadata& operator=( const Metadata& ) = default;
Metadata& operator=( Metadata&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] keys   the keys associated with the covariance matrix
 */
Metadata( std::vector< Key > keys ) : keys_( std::move( keys ) ) {}
