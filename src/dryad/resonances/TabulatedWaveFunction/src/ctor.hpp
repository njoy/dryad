private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedWaveFunction( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedWaveFunction() = default;

TabulatedWaveFunction( const TabulatedWaveFunction& ) = default;
TabulatedWaveFunction( TabulatedWaveFunction&& ) = default;

TabulatedWaveFunction& operator=( const TabulatedWaveFunction& ) = default;
TabulatedWaveFunction& operator=( TabulatedWaveFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param ratios.        the ratio values
 *  @param values         the wave function values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedWaveFunction( std::vector< double > ratios,
                       std::vector< double > values,
                       std::vector< std::size_t > boundaries,
                       std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( ratios ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a wave function using a single interpolation zone
 *
 *  @param ratios        the ratio values
 *  @param values        the wave function values
 *  @param interpolant   the interpolation type of the data (default lin-lin)
 */
TabulatedWaveFunction( std::vector< double > ratios,
                       std::vector< double > values,
                       InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( ratios ), std::move( values ), interpolant ) {}
