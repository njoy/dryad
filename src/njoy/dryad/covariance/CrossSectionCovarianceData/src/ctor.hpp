private:

/**
 *  @brief Private constructor
 *
 *  @param matrices   the covariance matrices
 */
CrossSectionCovarianceData( std::pair< std::vector< id::ReactionID >, std::vector< Covariance > > data ) :
  covariances_( std::move( data.second ) ),
  reactions_( std::move( data.first ) ) {}

public:

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
CrossSectionCovarianceData( std::vector< covariance::CrossSectionCovarianceMatrix > matrices ) :
  CrossSectionCovarianceData( generateCovariances( matrices ) ) {}
