/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
DebyeWallerIntegralData() = default;

DebyeWallerIntegralData( const DebyeWallerIntegralData& ) = default;
DebyeWallerIntegralData( DebyeWallerIntegralData&& ) = default;

DebyeWallerIntegralData& operator=( const DebyeWallerIntegralData& ) = default;
DebyeWallerIntegralData& operator=( DebyeWallerIntegralData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param temperatures   the temperatures values
 *  @param values         the integral values
 */
DebyeWallerIntegralData( std::vector< double > temperatures,
                         std::vector< double > values ) :
  temperatures_( std::move( temperatures ) ),
  integrals_( std::move( values ) ) {}
