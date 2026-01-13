private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedDebyeWallerIntegral( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedDebyeWallerIntegral() = default;

TabulatedDebyeWallerIntegral( const TabulatedDebyeWallerIntegral& ) = default;
TabulatedDebyeWallerIntegral( TabulatedDebyeWallerIntegral&& ) = default;

TabulatedDebyeWallerIntegral& operator=( const TabulatedDebyeWallerIntegral& ) = default;
TabulatedDebyeWallerIntegral& operator=( TabulatedDebyeWallerIntegral&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param temperatures   the temperatures values
 *  @param values         the integral values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedDebyeWallerIntegral( std::vector< double > temperatures,
                     std::vector< double > values,
                     std::vector< std::size_t > boundaries,
                     std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( temperatures ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a Debye-Waller integral table using a single interpolation zone
 *
 *  @param temperatures   the temperature values
 *  @param values         the integral values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedDebyeWallerIntegral( std::vector< double > temperatures,
                              std::vector< double > values,
                              InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( temperatures ), std::move( values ), interpolant ) {}
