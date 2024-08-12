private:

/**
 *  @brief Private constructor
 *
 *  @param frame        the reference frame of the distribution data
 *  @param scattering   the scattering function
 *  @param real         the optional real part of the anamolous form factor
 *  @param imaginary    the optional imaginary part of the anamolous form factor
 */
CoherentDistributionData( ReferenceFrame&& frame,
                          TabulatedScatteringFunction&& scattering,
                          std::optional< TabulatedFormFactor >&& real,
                          std::optional< TabulatedFormFactor >&& imaginary ) :
    frame_( std::move( frame ) ), scattering_( std::move( scattering ) ),
    real_( std::move( real ) ), imaginary_( std::move( imaginary ) ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
CoherentDistributionData() = default;

CoherentDistributionData( const CoherentDistributionData& ) = default;
CoherentDistributionData( CoherentDistributionData&& ) = default;

CoherentDistributionData& operator=( const CoherentDistributionData& ) = default;
CoherentDistributionData& operator=( CoherentDistributionData&& ) = default;

/**
 *  @brief Constructor (no anomolous form factors)
 *
 *  @param frame        the reference frame of the distribution data
 *  @param scattering   the scattering function
 */
CoherentDistributionData( ReferenceFrame frame,
                          TabulatedScatteringFunction scattering ) :
    CoherentDistributionData( std::move( frame ), std::move( scattering ),
                              std::nullopt, std::nullopt ) {}

/**
 *  @brief Constructor (with anomolous form factors)
 *
 *  @param frame        the reference frame of the distribution data
 *  @param scattering   the scattering function
 *  @param real         the real part of the anamolous form factor
 *  @param imaginary    the imaginary part of the anamolous form factor
 */
CoherentDistributionData( ReferenceFrame frame,
                          TabulatedScatteringFunction scattering,
                          TabulatedFormFactor real,
                          TabulatedFormFactor imaginary ) :
    CoherentDistributionData( std::move( frame ), std::move( scattering ),
                              std::make_optional( std::move( real ) ),
                              std::make_optional( std::move( imaginary ) ) ) {}
