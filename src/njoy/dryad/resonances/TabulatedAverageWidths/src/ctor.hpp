private:

/**
 *  @brief  Private constructor
 *  @param  table   the interpolation table
 *  @param  dof     the degrees of freedom
 */
TabulatedAverageWidths( std::optional< int > dof,
                        InterpolationTable< double, double > table ) :
  InterpolationTable( std::move( table ) ), degrees_freedom_(  dof ) {}


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
 *  @param[in]  dof             the degrees of freedom for Porter-Thomas distribution sampling for each width
 *  @param[in]  energies        the energy values (eV)
 *  @param[in]  widths          the average width values (eV)
 *  @param[in]  boundaries      the boundaries of the interpolation regions
 *  @param[in]  interpolants    the interpolation types of the interpolation regions
 */
TabulatedAverageWidths( int dof,
                        std::vector< double > energies,
                        std::vector< double > widths,
                        std::vector< std::size_t > boundaries,
                        std::vector< InterpolationType > interpolants ) :
  TabulatedAverageWidths( std::optional< int >( dof ),
                          InterpolationTable< double, double >( std::move( energies ),
                                                                std::move( widths ),
                                                                std::move( boundaries ),
                                                                std::move( interpolants ) )
                          ) {}

/**
 *  @brief Constructor for a single interpolation zone
 *
 *  @param[in] dof            the degrees of freedom for Porter-Thomas sampling for each width
 *  @param[in] energies       the energy values (eV)
 *  @param[in] widths         the average width values (eV)
 *  @param[in] interpolant    the interpolation type (default lin-lin)
 */
TabulatedAverageWidths( int dof,
                        std::vector< double > energies,
                        std::vector< double > widths,
                        InterpolationType interpolant = InterpolationType::LinearLinear ) :
  TabulatedAverageWidths( std::optional< int >( dof ),
                          InterpolationTable< double, double >( std::move( energies ),
                                                                std::move( widths ),
                                                                interpolant )
                          ) {}

/**
 *  @brief Constructor with a default dof (nullopt)
 *
 *  @param[in] energies       the energy values (eV)
 *  @param[in] widths         the average width values (eV)
 *  @param[in] boundaries     the boundaries of the interpolation regions
 *  @param[in] interpolants   the interpolation types of the interpolation regions
 */
TabulatedAverageWidths( std::vector< double > energies,
                        std::vector< double > widths,
                        std::vector< std::size_t > boundaries,
                        std::vector< InterpolationType > interpolants ) :
  TabulatedAverageWidths( std::nullopt,
                          InterpolationTable< double, double >( std::move( energies ),
                                                                std::move( widths ),
                                                                std::move( boundaries ),
                                                                std::move( interpolants ) )
                          ) {}

/**
 *  @brief Constructor for a single interpolation zone with a default dof (nullopt)
 *
 *  @param[in] energies       the energy values (eV)
 *  @param[in] widths         the average width values (eV)
 *  @param[in] interpolant    the interpolation type (default lin-lin)
 */
TabulatedAverageWidths( std::vector< double > energies,
                        std::vector< double > widths,
                        InterpolationType interpolant = InterpolationType::LinearLinear ) :
  TabulatedAverageWidths( std::nullopt,
                          InterpolationTable< double, double >( std::move( energies ),
                                                                std::move( widths ),
                                                                interpolant )
                          ) {}