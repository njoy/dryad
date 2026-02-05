/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CrossSectionMetadata() = default;

CrossSectionMetadata( const CrossSectionMetadata& ) = default;
CrossSectionMetadata( CrossSectionMetadata&& ) = default;

CrossSectionMetadata& operator=( const CrossSectionMetadata& ) = default;
CrossSectionMetadata& operator=( CrossSectionMetadata&& ) = default;

/**
 *  @brief Internal constructor
 *
 *  @param[in] keys   the keys associated with the covariance matrix
 */
CrossSectionMetadata( std::vector< Key > keys ) :
    Parent( std::move( keys ) ) {

  this->updateMetadata();
}

/**
 *  @brief Constructor
 *
 *  @param[in] reactions   the reaction identifiers
 *  @param[in] energies    the energy boundary values
 */
CrossSectionMetadata( std::vector< id::ReactionID > reactions,
                      std::vector< double > energies ) :
    Parent( generateKeys( reactions, energies ) ),
    reactions_( std::move( reactions ) ),
    energies_( std::move( energies ) ) {}

/**
 *  @brief Constructor for a single reaction
 *
 *  @param[in] reaction   the reaction identifier
 *  @param[in] energies   the energy boundary values
 */
CrossSectionMetadata( id::ReactionID reaction,
                      std::vector< double > energies ) :
    CrossSectionMetadata( std::vector< id::ReactionID >{ std::move( reaction ) },
                          std::move( energies ) ) {}
