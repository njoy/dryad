private:

/**
 *  @brief Private constructor
 *
 *  @param series   the polynomial series
 */
PolynomialMultiplicity( PolynomialSeries< double, double > series ) :
  PolynomialSeries( std::move( series ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
PolynomialMultiplicity() = default;

PolynomialMultiplicity( const PolynomialMultiplicity& ) = default;
PolynomialMultiplicity( PolynomialMultiplicity&& ) = default;

PolynomialMultiplicity& operator=( const PolynomialMultiplicity& ) = default;
PolynomialMultiplicity& operator=( PolynomialMultiplicity&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param lower          the lower limit of the domain
 *  @param upper          the upper limit of the domain
 *  @param coefficients   the coefficients of the polynomial series (from
 *                        lowest to highest order coefficient)
 */
PolynomialMultiplicity( double lower, double upper, std::vector< double > coefficients ) :
  PolynomialSeries( std::move( lower ), std::move( upper ), std::move( coefficients ) ) {}
