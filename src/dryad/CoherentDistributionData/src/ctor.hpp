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
                          std::optional< TabulatedFormFactor >&& imaginary > ) :
    frame_( std::move( frame ) ), scattering_( std::move( scattering ) ),
    real_( std::move( real ) ), imaginary_( std::move( imaginary ) ) {}

public:

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
CoherentDistributionData() = default;
#endif

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
                              std::move( real ), std::move( imaginary ) ) {}
