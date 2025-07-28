/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
Documentation() = default;

Documentation( const Documentation& ) = default;
Documentation( Documentation&& ) = default;

Documentation& operator=( const Documentation& ) = default;
Documentation& operator=( Documentation&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] awr           the atomic weight ratio
 *  @param[in] library       the library number
 *  @param[in] version       the version number
 *  @param[in] description   the description
 */
Documentation( std::optional< double > awr, std::optional< int > library,
               std::optional< std::pair< int, int > > version,
               std::optional< std::string > description ) :
    awr_( std::move( awr ) ),
    library_( std::move( library ) ),
    version_( std::move( version ) ),
    description_( std::move( description ) ) {}
