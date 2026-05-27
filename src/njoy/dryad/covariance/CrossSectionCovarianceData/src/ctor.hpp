/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CrossSectionCovarianceData() = default;

CrossSectionCovarianceData( const CrossSectionCovarianceData& ) = default;
CrossSectionCovarianceData( CrossSectionCovarianceData&& ) = default;

CrossSectionCovarianceData& operator=( const CrossSectionCovarianceData& ) = default;
CrossSectionCovarianceData& operator=( CrossSectionCovarianceData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param matrices   the covariance matrices
 */
CrossSectionCovarianceData( std::vector< CrossSectionCovarianceMatrix > matrices ) :
  Parent( std::move( matrices ) ) {}
