//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
/**
 *  @brief Default constructor - only enabled for pybind11
 */
IncoherentDistributionData() = default;
#endif

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
