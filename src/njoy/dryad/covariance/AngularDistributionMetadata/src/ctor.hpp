/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
AngularDistributionMetadata() = default;

AngularDistributionMetadata( const AngularDistributionMetadata& ) = default;
AngularDistributionMetadata( AngularDistributionMetadata&& ) = default;

AngularDistributionMetadata& operator=( const AngularDistributionMetadata& ) = default;
AngularDistributionMetadata& operator=( AngularDistributionMetadata&& ) = default;

/**
 *  @brief Internal constructor
 *
 *  @param[in] keys   the keys associated with the covariance matrix
 */
AngularDistributionMetadata( std::vector< Key > keys ) :
    Parent( std::move( keys ) ) {

  this->updateMetadata();
}

/**
 *  @brief Constructor
 *
 *  @param[in] reactions   the reaction identifiers
 *  @param[in] moments     the Legendre moment values
 *  @param[in] energies    the energy boundary values
 */
AngularDistributionMetadata( std::vector< id::ReactionID > reactions,
                             std::vector< std::size_t > moments,
                             std::vector< double > energies ) :
    Parent( generateKeys( reactions, moments, energies ) ),
    reactions_( std::move( reactions ) ),
    moments_( std::move( moments ) ),
    energies_( std::move( energies ) ) {}
