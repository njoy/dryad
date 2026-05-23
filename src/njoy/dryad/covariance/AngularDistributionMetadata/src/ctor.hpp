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
 *  @param[in] energies    the energy boundary values
 *  @param[in] moments     the Legendre moment values
 */
AngularDistributionMetadata( std::vector< id::ReactionID > reactions,
                             std::vector< double > energies,
                             std::vector< std::size_t > moments ) :
    Parent( generateKeys( reactions, energies, moments ) ),
    reactions_( std::move( reactions ) ),
    energies_( std::move( energies ) ),
    moments_( std::move( moments ) ) {}
