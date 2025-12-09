/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TabulatedComptonProfile() = default;

TabulatedComptonProfile( const TabulatedComptonProfile& ) = default;
TabulatedComptonProfile( TabulatedComptonProfile&& ) = default;

TabulatedComptonProfile& operator=( const TabulatedComptonProfile& ) = default;
TabulatedComptonProfile& operator=( TabulatedComptonProfile&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param identifier     the electron subshell identifier
 *  @param momentum       the momentum values
 *  @param values         the probability values
 *  @param boundaries     the boundaries of the interpolation regions
 *  @param interpolants   the interpolation types of the interpolation regions
 *  @param normalise      option to indicate whether or not to normalise
 *                        all probability data (default: no normalisation)
 */
TabulatedComptonProfile(
    id::ElectronSubshellID identifier,
    std::vector< double > momentum,
    std::vector< double > values,
    std::vector< std::size_t > boundaries,
    std::vector< InterpolationType > interpolants,
    bool normalise = false ) :
  id_( std::move( identifier ) ),
  pdf_( std::move( momentum ), std::move( values ),
        std::move( boundaries ), std::move( interpolants ) ),
  cdf_() {

  if ( normalise ) {

    this->normalise();
  }
  else {

    this->calculateCdf();
  }
}

/**
 *  @brief Constructor for a pdf using a single interpolation zone
 *
 *  @param identifier     the electron subshell identifier
 *  @param momentum       the momentum values
 *  @param values         the probability values
 *  @param interpolant    the interpolation type of the data (default lin-lin)
 *  @param normalise      option to indicate whether or not to normalise
 *                        all probability data (default: no normalisation)
 */
TabulatedComptonProfile(
    id::ElectronSubshellID identifier,
    std::vector< double > momentum,
    std::vector< double > values,
    InterpolationType interpolant = InterpolationType::LinearLinear,
    bool normalise = false ) :
  id_( std::move( identifier ) ),
  pdf_( std::move( momentum ), std::move( values ), std::move( interpolant ) ),
  cdf_() {

  if ( normalise ) {

    this->normalise();
  }
  else {

    this->calculateCdf();
  }
}

/**
 *  @brief Constructor using a pdf
 *
 *  @param identifier   the electron subshell identifier
 *  @param pdf          the pdf of the distribution
 *  @param normalise    option to indicate whether or not to normalise
 *                      all probability data (default: no normalisation)
 */
TabulatedComptonProfile(
    id::ElectronSubshellID identifier,
    TabulatedComptonProfileFunction pdf,
    bool normalise = false ) :
  id_( std::move( identifier ) ),
  pdf_( std::move( pdf ) ), cdf_() {

  if ( normalise ) {

    this->normalise();
  }
  else {

    this->calculateCdf();
  }
}

/**
 *  @brief Constructor using a pdf and cdf
 *
 *  @param identifier   the electron subshell identifier
 *  @param pdf          the pdf of the distribution
 *  @param cdf          the cdf of the distribution
 */
TabulatedComptonProfile(
    id::ElectronSubshellID identifier,
    TabulatedComptonProfileFunction pdf,
    TabulatedComptonProfileFunction cdf ) :
  id_( std::move( identifier ) ),
  pdf_( std::move( pdf ) ), cdf_( std::move( cdf ) ) {}
