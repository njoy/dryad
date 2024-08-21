private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedAngularDistributionFunction( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedAngularDistributionFunction() = default;

TabulatedAngularDistributionFunction( const TabulatedAngularDistributionFunction& ) = default;
TabulatedAngularDistributionFunction( TabulatedAngularDistributionFunction&& ) = default;

TabulatedAngularDistributionFunction& operator=( const TabulatedAngularDistributionFunction& ) = default;
TabulatedAngularDistributionFunction& operator=( TabulatedAngularDistributionFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param cosines        the cosine values
 *  @param values         the probability values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedAngularDistributionFunction(
    std::vector< double > cosines,
    std::vector< double > values,
    std::vector< std::size_t > boundaries,
    std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( cosines ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a probability using a single interpolation zone
 *
 *  @param cosines        the cosine values
 *  @param values         the probability values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedAngularDistributionFunction(
    std::vector< double > cosines,
    std::vector< double > values,
    InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( cosines ), std::move( values ), interpolant ) {}
