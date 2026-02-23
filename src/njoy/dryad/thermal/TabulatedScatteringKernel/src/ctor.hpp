/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedScatteringKernel() = default;

TabulatedScatteringKernel( const TabulatedScatteringKernel& ) = default;
TabulatedScatteringKernel( TabulatedScatteringKernel&& ) = default;

TabulatedScatteringKernel& operator=( const TabulatedScatteringKernel& ) = default;
TabulatedScatteringKernel& operator=( TabulatedScatteringKernel&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energyTransfers   the energy transfer values
 *  @param functions         the associated scattering functions
 *  @param boundaries        the boundaries of the interpolation regions
 *  @param interpolants      the interpolation types of the interpolation regions
 */
TabulatedScatteringKernel( std::vector< double > energyTransfers,
                           std::vector< TabulatedScatteringKernelFunction > functions,
                           std::vector< std::size_t > boundaries,
                           std::vector< InterpolationType > interpolants ) :
  Parent( std::move( energyTransfers ), std::move( functions ),
          std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for scattering functions using a single interpolation zone
 *
 *  @param energyTransfers   the energy transfer values
 *  @param functions         the associated functions
 *  @param interpolant       the interpolation type of the data (default lin-lin)
 */
TabulatedScatteringKernel( std::vector< double > energyTransfers,
                           std::vector< TabulatedScatteringKernelFunction > functions,
                           InterpolationType interpolant = InterpolationType::LinearLinear ) :
  Parent( std::move( energyTransfers ), std::move( functions ), interpolant ) {}
