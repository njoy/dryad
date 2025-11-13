private:

/**
 *  @brief Private constructor
 *
 *  @param table   the interpolation table
 */
TabulatedMultiplicity( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedMultiplicity() = default;

TabulatedMultiplicity( const TabulatedMultiplicity& ) = default;
TabulatedMultiplicity( TabulatedMultiplicity&& ) = default;

TabulatedMultiplicity& operator=( const TabulatedMultiplicity& ) = default;
TabulatedMultiplicity& operator=( TabulatedMultiplicity&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the multiplicity values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
TabulatedMultiplicity( std::vector< double > energies,
                       std::vector< double > values,
                       std::vector< std::size_t > boundaries,
                       std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( energies ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a multiplicity using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the multiplicity values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
TabulatedMultiplicity( std::vector< double > energies,
                       std::vector< double > values,
                       InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( energies ), std::move( values ), interpolant ) {}
