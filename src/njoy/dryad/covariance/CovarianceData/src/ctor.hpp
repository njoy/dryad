/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CovarianceData() = default;

CovarianceData( const CovarianceData& ) = default;
CovarianceData( CovarianceData&& ) = default;

CovarianceData& operator=( const CovarianceData& ) = default;
CovarianceData& operator=( CovarianceData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param matrices   the covariance matrices
 */
CovarianceData( std::optional< covariance::CrossSectionCovarianceData > xs,
                std::optional< covariance::AngularDistributionCovarianceData > angular ) :
  xs_( std::move( xs ) ) ,
  angular_( std::move( angular ) ) {}
