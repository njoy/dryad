private:

/**
 *  @brief Constructor for an on-diagonal covariance matrix (relative or absolute)
 *
 *  @param[in] keys          the keys associated with the covariance block
 *  @param[in] covariances   the covariance matrix
 *  @param[in] relative      the relative covariance flag
 */
ProductMultiplicityCovarianceData( std::vector< Key > keys,
                                   Matrix< double > covariances,
                                   bool relative = true ) :
  Parent( std::move( keys ), std::move( covariances ), relative ) {}

public:

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
    ProductMultiplicityCovarianceData(
        generateKeys( std::move( energies ), std::move( products ) ),
        std::move( covariances ) ) {}
