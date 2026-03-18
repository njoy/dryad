/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ThermalScattering() = default;

ThermalScattering( const ThermalScattering& ) = default;
ThermalScattering( ThermalScattering&& ) = default;

ThermalScattering& operator=( const ThermalScattering& ) = default;
ThermalScattering& operator=( ThermalScattering&& ) = default;

/**
 *  @brief Constructor with documentation
 *
 *  @param[in] documentation   the documentation
 *  @param[in] incoherent      the incoherent elastic scattering data (default: none)
 */
ThermalScattering( Documentation documentation,
                   std::optional< thermal::CoherentElasticScattering > coherent = std::nullopt,
                   std::optional< thermal::IncoherentElasticScattering > incoherent = std::nullopt ) :
    documentation_( std::move( documentation ) ),
    coherent_elastic_( std::move( coherent ) ),
    incoherent_elastic_( std::move( incoherent ) ) {}

/**
 *  @brief Constructor without documentation
 *
 *  @param[in] incoherent      the incoherent elastic scattering data (default: none)
 */
ThermalScattering( std::optional< thermal::CoherentElasticScattering > coherent = std::nullopt,
                   std::optional< thermal::IncoherentElasticScattering > incoherent = std::nullopt ) :
    documentation_(),
    coherent_elastic_( std::move( coherent ) ),
    incoherent_elastic_( std::move( incoherent ) ) {}
