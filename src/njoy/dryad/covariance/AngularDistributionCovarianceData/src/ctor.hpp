/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
AngularDistributionCovarianceData() = default;

AngularDistributionCovarianceData( const AngularDistributionCovarianceData& ) = default;
AngularDistributionCovarianceData( AngularDistributionCovarianceData&& ) = default;

AngularDistributionCovarianceData& operator=( const AngularDistributionCovarianceData& ) = default;
AngularDistributionCovarianceData& operator=( AngularDistributionCovarianceData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param matrices   the covariance matrices
 */
AngularDistributionCovarianceData( std::vector< AngularDistributionCovarianceMatrix > matrices ) :
  Parent( std::move( matrices ) ) {}
