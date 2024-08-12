private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedScatteringFunction( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

TabulatedScatteringFunction( const TabulatedScatteringFunction& ) = default;
TabulatedScatteringFunction( TabulatedScatteringFunction&& ) = default;

TabulatedScatteringFunction& operator=( const TabulatedScatteringFunction& ) = default;
TabulatedScatteringFunction& operator=( TabulatedScatteringFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param x              the x values
 *  @param values         the scattering function values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedScatteringFunction( std::vector< double > x,
                             std::vector< double > values,
                             std::vector< std::size_t > boundaries,
                             std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( x ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a cross section using a single interpolation zone
 *
 *  @param x              the x values
 *  @param values         the scattering function values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedScatteringFunction( std::vector< double > x,
                             std::vector< double > values,
                             InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( x ), std::move( values ), interpolant ) {}
