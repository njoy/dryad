TwoBodyDistributionData( const TwoBodyDistributionData& ) = default;
TwoBodyDistributionData( TwoBodyDistributionData&& ) = default;

TwoBodyDistributionData& operator=( const TwoBodyDistributionData& ) = default;
TwoBodyDistributionData& operator=( TwoBodyDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param frame   the reference frame of the distribution data
 *  @param angle   the angular distributions
 */
TwoBodyDistributionData( ReferenceFrame frame,
                         AngularDistributions angle ) :
    frame_( std::move( frame ) ), angle_( std::move( angle ) ) {}
