private:

/**
 *  @brief Constructor for cross section data
 *
 *  @param table   the interpolation table
 */
CrossSection( InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ) {}

public:

CrossSection( const CrossSection& ) = default;
CrossSection( CrossSection&& ) = default;

CrossSection& operator=( const CrossSection& ) = default;
CrossSection& operator=( CrossSection&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param energies       the energy values
 *  @param values         the cross section values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 */
CrossSection( std::vector< double > energies, std::vector< double > values,
              std::vector< std::size_t > boundaries,
              std::vector< InterpolationType > interpolants ) :
  InterpolationTable( std::move( energies ), std::move( values ),
                      std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief Constructor for a cross section using a single interpolation zone
 *
 *  @param energies       the energy values
 *  @param values         the cross section values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 */
CrossSection( std::vector< double > energies,
              std::vector< double > values,
              InterpolationType interpolant = InterpolationType::LinearLinear ) :
  InterpolationTable( std::move( energies ), std::move( values ), interpolant ) {}
