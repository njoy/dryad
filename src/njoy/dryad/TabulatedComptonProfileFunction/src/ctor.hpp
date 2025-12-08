private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedComptonProfileFunction( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedComptonProfileFunction() = default;

TabulatedComptonProfileFunction( const TabulatedComptonProfileFunction& ) = default;
TabulatedComptonProfileFunction( TabulatedComptonProfileFunction&& ) = default;

TabulatedComptonProfileFunction& operator=( const TabulatedComptonProfileFunction& ) = default;
TabulatedComptonProfileFunction& operator=( TabulatedComptonProfileFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param momentum       the momentum values
 *  @param values         the probability values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedComptonProfileFunction(
    std::vector< double > momentum,
    std::vector< double > values,
    std::vector< std::size_t > boundaries,
    std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( momentum ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a probability using a single interpolation zone
 *
 *  @param momentum       the momentum values
 *  @param values         the probability values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedComptonProfileFunction(
    std::vector< double > momentum,
    std::vector< double > values,
    InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( momentum ), std::move( values ), interpolant ) {}
