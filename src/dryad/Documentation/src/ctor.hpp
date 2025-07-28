/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
Metadata() = default;

Metadata( const Metadata& ) = default;
Metadata( Metadata&& ) = default;

Metadata& operator=( const Metadata& ) = default;
Metadata& operator=( Metadata&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] library       the library number
 *  @param[in] version       the version number
 *  @param[in] temperature   the temperature
 *  @param[in] description   the description
 */
Metadata( std::optional< double > awr, std::optional< int > library,
          std::optional< std::pair< int, int > > version,
          std::optional< double > temperature,
          std::optional< std::string > description ) :
    awr_( std::move( awr ) ), library_( std::move( library ) ),
    version_( std::move( version ) ), temperature_( std::move( temperature ) ),
    description_( std::move( description ) ) {}
