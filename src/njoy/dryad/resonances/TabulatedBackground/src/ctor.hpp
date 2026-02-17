private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedBackground( InterpolationTable< double, std::complex< double > > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedBackground() = default;

TabulatedBackground( const TabulatedBackground& ) = default;
TabulatedBackground( TabulatedBackground&& ) = default;

TabulatedBackground& operator=( const TabulatedBackground& ) = default;
TabulatedBackground& operator=( TabulatedBackground&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the background values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedBackground( std::vector< double > energies,
                     std::vector< std::complex< double > > values,
                     std::vector< std::size_t > boundaries,
                     std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( energies ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a background using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the background values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedBackground( std::vector< double > energies,
                     std::vector< std::complex< double > > values,
                     InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( energies ), std::move( values ), interpolant ) {}
