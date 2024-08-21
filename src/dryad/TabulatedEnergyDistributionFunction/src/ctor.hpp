private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedEnergyDistributionFunction( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedEnergyDistributionFunction() = default;

TabulatedEnergyDistributionFunction( const TabulatedEnergyDistributionFunction& ) = default;
TabulatedEnergyDistributionFunction( TabulatedEnergyDistributionFunction&& ) = default;

TabulatedEnergyDistributionFunction& operator=( const TabulatedEnergyDistributionFunction& ) = default;
TabulatedEnergyDistributionFunction& operator=( TabulatedEnergyDistributionFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the probability values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedEnergyDistributionFunction(
    std::vector< double > energies,
    std::vector< double > values,
    std::vector< std::size_t > boundaries,
    std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( energies ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for an energy distirbution using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the probability values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedEnergyDistributionFunction(
    std::vector< double > energies,
    std::vector< double > values,
    InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( energies ), std::move( values ), interpolant ) {}
