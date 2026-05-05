private:

/**
 *  @brief  Private constructor
 *  @param  table   the interpolation table
 *  @param  dof     the degrees of freedom
 */
TabulatedAverageWidths( InterpolationTable< double, double > table,
                        int dof) :
  InterpolationTable( std::move( table ) ),
  dof_( dof ) {}

public:

/**
 *  @brief  Default constructor (for pybind11 purposes only)
 */
TabulatedAverageWidths() = default;

TabulatedAverageWidths( const TabulatedAverageWidths& ) = default;
TabulatedAverageWidths( TabulatedAverageWidths&& ) = default;

TabulatedAverageWidths& operator=( const TabulatedAverageWidths& ) = default;
TabulatedAverageWidths& operator=( TabulatedAverageWidths&& ) = default;

/**
 *  @param[in]  energies        the energy values (eV)
 *  @param[in]  widths          the average width values (eV)
 *  @param[in]  dof             the degrees of freedom for Porter-Thomas distribution sampling for each width
 *  @param[in]  boundaries      the boundaries of the interpolation regions
 *  @param[in]  interpolants    the interpolation types of the interpolation regions
 */
TabulatedAverageWidths( std::vector< double > energies,
                        std::vector< double > widths,
                        std::vector<int> dof,
                        std::vector< std::size_t > boundaries,
                        std::vector< InterpolationType > interpolants ) :
  TabulatedAverageWidths(
      InterpolationTable< double, double >( std::move( energies ),
                                            std::move( widths ),
                                            std::move( boundaries ),
                                            std::move( interpolants ) ),
      dof ) {}

/**
 *  @brief Constructor for a single interpolation zone
 *
 *  @param[in] energies       the energy values (eV)
 *  @param[in] widths         the average width values (eV)
 *  @param[in] dof            the degrees of freedom for Porter-Thomas sampling for each width
 *  @param[in] interpolant    the interpolation type (default lin-lin)
 */
TabulatedAverageWidths( std::vector< double > energies,
                        std::vector< double > widths,
                        std::vector<int> dof,
                        InterpolationType interpolant = InterpolationType::LinearLinear ) :
  TabulatedAverageWidths(
      InterpolationTable< double, double >( std::move( energies ),
                                            std::move( widths ),
                                            interpolant ),
      dof ) {}
