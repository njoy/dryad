private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedScatteringKernelFunction( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedScatteringKernelFunction() = default;

TabulatedScatteringKernelFunction( const TabulatedScatteringKernelFunction& ) = default;
TabulatedScatteringKernelFunction( TabulatedScatteringKernelFunction&& ) = default;

TabulatedScatteringKernelFunction& operator=( const TabulatedScatteringKernelFunction& ) = default;
TabulatedScatteringKernelFunction& operator=( TabulatedScatteringKernelFunction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param momentumTransfers   the momentum transfer values
 *  @param values              the scattering function values
 *  @param boundaries          the boundaries of the interpolation regions
 *  @param interpolants        the interpolation types of the interpolation regions
 */
TabulatedScatteringKernelFunction( std::vector< double > momentumTransfers,
                                   std::vector< double > values,
                                   std::vector< std::size_t > boundaries,
                                   std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( momentumTransfers ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a scattering function table using a single interpolation zone
 *
 *  @param momentumTransfers   the momentum transfer values
 *  @param values              the effective temperature values
 *  @param interpolant         the interpolation type of the data (default lin-lin)
 */
TabulatedScatteringKernelFunction( std::vector< double > momentumTransfers,
                                   std::vector< double > values,
                                   InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( momentumTransfers ), std::move( values ), interpolant ) {}
