UncorrelatedDistributionData( const UncorrelatedDistributionData& ) = default;
UncorrelatedDistributionData( UncorrelatedDistributionData&& ) = default;

UncorrelatedDistributionData& operator=( const UncorrelatedDistributionData& ) = default;
UncorrelatedDistributionData& operator=( UncorrelatedDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param frame    the reference frame of the distribution data
 *  @param angle    the angular distributions
 *  @param energy   the energy distributions
 */
UncorrelatedDistributionData( ReferenceFrame frame,
                              AngularDistributions angle,
                              EnergyDistributions energy ) :
    frame_( std::move( frame ) ),
    angle_( std::move( angle ) ),
    energy_( std::move( energy ) ) {}
