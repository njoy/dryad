/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
SammyBackground() = default;

SammyBackground( const SammyBackground& ) = default;
SammyBackground( SammyBackground&& ) = default;

SammyBackground& operator=( const SammyBackground& ) = default;
SammyBackground& operator=( SammyBackground&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] polynomialCoefficients    the coefficients of the polymonial term
 *  @param[in] logarithmicCoefficients   the coefficients of the logarithmic term
 *  @param[in] lowerSingularity          the lower logarithmic singularity values
 *  @param[in] upperSingularity          the upper logarithmic singularity values
 */
SammyBackground( std::array< double, 3 > polynomialCoefficients,
                 std::array< double, 2 > logarithmicCoefficients,
                 double lowerSingularity,
                 double upperSingularity ) :
  polynomial_coefficients_( std::move( polynomialCoefficients ) ),
  logarithmic_coefficients_( std::move( logarithmicCoefficients ) ),
  lower_singularity_( lowerSingularity ),
  upper_singularity_( upperSingularity ) {}

