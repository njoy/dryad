/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
IncoherentDistributionData() = default;

IncoherentDistributionData( const IncoherentDistributionData& ) = default;
IncoherentDistributionData( IncoherentDistributionData&& ) = default;

IncoherentDistributionData& operator=( const IncoherentDistributionData& ) = default;
IncoherentDistributionData& operator=( IncoherentDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param frame        the reference frame of the distribution data
 *  @param scattering   the scattering function
 */
IncoherentDistributionData( ReferenceFrame frame,
                            TabulatedScatteringFunction scattering ) :
    frame_( std::move( frame ) ), scattering_( std::move( scattering ) ) {}
