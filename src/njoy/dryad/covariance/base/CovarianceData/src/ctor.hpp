private:

/**
 *  @brief Private constructor
 *
 *  @param matrices   the covariance matrices
 */
CovarianceData( std::pair< std::vector< id::ReactionID >, std::vector< Covariance > > data ) :
  covariances_( std::move( data.second ) ),
  reactions_( std::move( data.first ) ) {}

public:

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
CovarianceData( std::vector< CovarianceMatrix > matrices ) :
  CovarianceData( generateCovariances( matrices ) ) {}
