/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ProductMultiplicityMetadata() = default;

ProductMultiplicityMetadata( const ProductMultiplicityMetadata& ) = default;
ProductMultiplicityMetadata( ProductMultiplicityMetadata&& ) = default;

ProductMultiplicityMetadata& operator=( const ProductMultiplicityMetadata& ) = default;
ProductMultiplicityMetadata& operator=( ProductMultiplicityMetadata&& ) = default;

/**
 *  @brief Internal constructor
 *
 *  @param[in] keys   the keys associated with the covariance matrix
 */
ProductMultiplicityMetadata( std::vector< Key > keys ) :
    Parent( std::move( keys ) ) {

  this->updateMetadata();
}

/**
 *  @brief Constructor
 *
 *  @param[in] reactions   the reaction identifiers
 *  @param[in] energies    the energy boundary values
 *  @param[in] products    the product identifiers
 */
ProductMultiplicityMetadata( std::vector< id::ReactionID > reactions,
                             std::vector< double > energies,
                             std::vector< id::ParticleID > products ) :
    Parent( generateKeys( reactions, energies, products ) ),
    reactions_( std::move( reactions ) ),
    energies_( std::move( energies ) ),
    products_( std::move( products ) ) {}
