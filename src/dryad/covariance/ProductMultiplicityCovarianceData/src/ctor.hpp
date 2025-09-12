/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ProductMultiplicityCovarianceData() = default;

ProductMultiplicityCovarianceData( const ProductMultiplicityCovarianceData& ) = default;
ProductMultiplicityCovarianceData( ProductMultiplicityCovarianceData&& ) = default;

ProductMultiplicityCovarianceData& operator=( const ProductMultiplicityCovarianceData& ) = default;
ProductMultiplicityCovarianceData& operator=( ProductMultiplicityCovarianceData&& ) = default;

/**
 *  @brief Constructor for product multiplicity covariance data
 *
 *  @param[in] energies      the group structure
 *  @param[in] products      the product identifiers
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
ProductMultiplicityCovarianceData( std::vector< double > energies,
                                   std::vector< id::ParticleID > products,
                                   Matrix< double > covariances,
                                   bool relative = true ) :
    Parent( generateKeys( std::move( energies ), std::move( products ) ),
            std::move( covariances ), relative ) {}

/**
 *  @brief Constructor for product multiplicity correlation data
 *
 *  @param[in] energies      the group structure
 *  @param[in] products      the product identifiers
 *  @param[in] deviations    the product identifiers
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
ProductMultiplicityCovarianceData( std::vector< double > energies,
                                   std::vector< id::ParticleID > products,
                                   std::vector< double > deviations,
                                   Matrix< double > correlations,
                                   bool relative = true ) :
    Parent( generateKeys( std::move( energies ), std::move( products ) ),
            std::move( deviations ), std::move( correlations ), relative ) {}
