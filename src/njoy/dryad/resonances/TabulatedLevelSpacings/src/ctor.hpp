private:

/**
 *  @brief Private constructor
 *  @param table    the interpolation table
 */
TabulatedLevelSpacings( InterpolationTable< double, double > table ) :
    InterpolationTable( std::move( table ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposed only)
 */

TabulatedLevelSpacings() = default;

TabulatedLevelSpacings( const TabulatedLevelSpacings& ) = default;
TabulatedLevelSpacings( TabulatedLevelSpacings&& ) = default;

TabulatedLevelSpacings& operator=( const TabulatedLevelSpacings& ) = default;
TabulatedLevelSpacings& operator=( TabulatedLevelSpacings&& ) = default;

/**
 *  @brief  Constructor
 *
 *  @param[in]  energies        the energy values (eV)
 *  @param[in]  spacings        the average level spacing values (eV)
 *  @param[in]  boundaries      the boundaries of the interpolation regions
 *  @param[in]  interpolants    the interpolation types of the interpolation regions
 */
TabulatedLevelSpacings( std::vector< double > energies,
                        std::vector< double > spacings,
                        std::vector< std::size_t > boundaries,
                        std::vector< InterpolationType > interpolants ) :
    InterpolationTable( std::move( energies ), std::move( spacings ),
                        std::move( boundaries ), std::move( interpolants ) ) {}

/**
 *  @brief  Constructor for a single interpolation zone
 *
 *  @param[in]  energies        the energy values (eV)
 *  @param[in]  spacings        the average level spacing values (eV)
 *  @param[in]  interpolant     the interpolation type (default lin-lin)
 */
TabulatedLevelSpacings(
                        std::vector< double > energies,
                        std::vector< double > spacings,
                        InterpolationType interpolant = InterpolationType::LinearLinear ) :
    InterpolationTable( std::move( energies ), std::move( spacings ), interpolant ) {}
