private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedAverageEnergy( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedAverageEnergy() = default;

TabulatedAverageEnergy( const TabulatedAverageEnergy& ) = default;
TabulatedAverageEnergy( TabulatedAverageEnergy&& ) = default;

TabulatedAverageEnergy& operator=( const TabulatedAverageEnergy& ) = default;
TabulatedAverageEnergy& operator=( TabulatedAverageEnergy&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the average energy values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedAverageEnergy( std::vector< double > energies,
                        std::vector< double > values,
                        std::vector< std::size_t > boundaries,
                        std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( energies ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a cross section using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the cross section values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedAverageEnergy( std::vector< double > energies,
                        std::vector< double > values,
                        InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( energies ), std::move( values ), interpolant ) {}
