/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedEnergyDistribution() = default;

TabulatedEnergyDistribution( const TabulatedEnergyDistribution& ) = default;
TabulatedEnergyDistribution( TabulatedEnergyDistribution&& ) = default;

TabulatedEnergyDistribution& operator=( const TabulatedEnergyDistribution& ) = default;
TabulatedEnergyDistribution& operator=( TabulatedEnergyDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the probability values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedEnergyDistribution(
    std::vector< double > energies,
    std::vector< double > values,
    std::vector< std::size_t > boundaries,
    std::vector< InterpolationType > interpolants,
    bool cdf = false ) :
  pdf_( std::move( energies ), std::move( values ),
        std::move( boundaries ), std::move( interpolants ) ),
  cdf_( std::nullopt ) {}

/**
 *  @brief Constructor for an energy distirbution using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the probability values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedEnergyDistribution(
    std::vector< double > energies,
    std::vector< double > values,
    InterpolationType interpolant = InterpolationType::LinearLinear ) :
  pdf_( std::move( energies ), std::move( values ), interpolant ),
  cdf_( std::nullopt ) {}
