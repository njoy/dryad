/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ProductMultiplicityCovarianceMatrix() = default;

ProductMultiplicityCovarianceMatrix( const ProductMultiplicityCovarianceMatrix& ) = default;
ProductMultiplicityCovarianceMatrix( ProductMultiplicityCovarianceMatrix&& ) = default;

ProductMultiplicityCovarianceMatrix& operator=( const ProductMultiplicityCovarianceMatrix& ) = default;
ProductMultiplicityCovarianceMatrix& operator=( ProductMultiplicityCovarianceMatrix&& ) = default;

/**
 *  @brief Constructor for full product multiplicity covariance data
 *
 *  @param[in] reaction      the reaction identifier
 *  @param[in] energies      the group structure
 *  @param[in] products      the product identifiers
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
ProductMultiplicityCovarianceMatrix( id::ReactionID reaction,
                                     std::vector< double > energies,
                                     std::vector< id::ParticleID > products,
                                     Matrix< double > covariances,
                                     bool relative = true ) :
    Parent( generateKeys( reaction, energies, products ),
            std::move( covariances ), relative ),
    reaction_( std::move( reaction ) ), energies_( std::move( energies ) ),
    products_( std::move( products ) ) {}

/**
 *  @brief Constructor for full product multiplicity correlation data
 *
 *  @param[in] reaction      the reaction identifier
 *  @param[in] energies      the group structure
 *  @param[in] products      the product identifiers
 *  @param[in] deviations    the product identifiers
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
ProductMultiplicityCovarianceMatrix( id::ReactionID reaction,
                                     std::vector< double > energies,
                                     std::vector< id::ParticleID > products,
                                     std::vector< double > deviations,
                                     Matrix< double > correlations,
                                     bool relative = true ) :
    Parent( generateKeys( reaction, energies, products ),
            std::move( deviations ), std::move( correlations ), relative ),
    reaction_( std::move( reaction ) ), energies_( std::move( energies ) ),
    products_( std::move( products ) ) {}

/**
 *  @brief Constructor for product multiplicity covariance data for a
 *         single energy group
 *
 *  @param[in] reaction      the reaction identifier
 *  @param[in] lower         the lower energy value of the energy group
 *  @param[in] upper         the upper energy value of the energy group
 *  @param[in] products      the product identifiers
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
ProductMultiplicityCovarianceMatrix( id::ReactionID reaction,
                                     double lower,
                                     double upper,
                                     std::vector< id::ParticleID > products,
                                     Matrix< double > covariances,
                                     bool relative = true ) :
    ProductMultiplicityCovarianceMatrix( std::move( reaction ),
                                         { lower, upper },
                                         std::move( products ),
                                         std::move( covariances ),
                                         relative ) {}

/**
 *  @brief Constructor for product multiplicity correlation data for a
 *         single energy group
 *
 *  @param[in] reaction      the reaction identifier
 *  @param[in] lower         the lower energy value of the energy group
 *  @param[in] upper         the upper energy value of the energy group
 *  @param[in] products      the product identifiers
 *  @param[in] deviations    the product identifiers
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
ProductMultiplicityCovarianceMatrix( id::ReactionID reaction,
                                     double lower,
                                     double upper,
                                     std::vector< id::ParticleID > products,
                                     std::vector< double > deviations,
                                     Matrix< double > correlations,
                                     bool relative = true ) :
    ProductMultiplicityCovarianceMatrix( std::move( reaction ),
                                         { lower, upper },
                                         std::move( products ),
                                         std::move( deviations ),
                                         std::move( correlations ),
                                         relative ) {}
