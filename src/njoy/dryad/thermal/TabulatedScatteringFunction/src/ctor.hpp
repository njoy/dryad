private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedScatteringFunction( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedScatteringFunction() = default;

TabulatedScatteringFunction( const TabulatedScatteringFunction& ) = default;
TabulatedScatteringFunction( TabulatedScatteringFunction&& ) = default;

TabulatedScatteringFunction& operator=( const TabulatedScatteringFunction& ) = default;
TabulatedScatteringFunction& operator=( TabulatedScatteringFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param momentumTransfers   the moderator temperatures values
 *  @param values              the scattering function values
 *  @param boundaries          the boundaries of the interpolation regions
 *  @param interpolants        the interpolation types of the interpolation regions
 */
TabulatedScatteringFunction( std::vector< double > momentumTransfers,
                             std::vector< double > values,
                             std::vector< std::size_t > boundaries,
                             std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( momentumTransfers ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a scattering function table using a single interpolation zone
 *
 *  @param momentumTransfers   the moderator temperatures values
 *  @param values              the effective temperature values
 *  @param interpolant         the interpolation type of the data (default lin-lin)
 */
TabulatedScatteringFunction( std::vector< double > momentumTransfers,
                             std::vector< double > values,
                             InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( momentumTransfers ), std::move( values ), interpolant ) {}
