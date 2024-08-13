private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedFormFactor( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedFormFactor() = default;

TabulatedFormFactor( const TabulatedFormFactor& ) = default;
TabulatedFormFactor( TabulatedFormFactor&& ) = default;

TabulatedFormFactor& operator=( const TabulatedFormFactor& ) = default;
TabulatedFormFactor& operator=( TabulatedFormFactor&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the form factor values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedFormFactor( std::vector< double > energies,
                     std::vector< double > values,
                     std::vector< std::size_t > boundaries,
                     std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( energies ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a form factor using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the form factor values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedFormFactor( std::vector< double > energies,
                     std::vector< double > values,
                     InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( energies ), std::move( values ), interpolant ) {}
