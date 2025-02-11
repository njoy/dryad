private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedAverageCosine( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedAverageCosine() = default;

TabulatedAverageCosine( const TabulatedAverageCosine& ) = default;
TabulatedAverageCosine( TabulatedAverageCosine&& ) = default;

TabulatedAverageCosine& operator=( const TabulatedAverageCosine& ) = default;
TabulatedAverageCosine& operator=( TabulatedAverageCosine&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the average cosine values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedAverageCosine( std::vector< double > energies,
                        std::vector< double > values,
                        std::vector< std::size_t > boundaries,
                        std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( energies ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a cross section using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the average cosine values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedAverageCosine( std::vector< double > energies,
                        std::vector< double > values,
                        InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( energies ), std::move( values ), interpolant ) {}
