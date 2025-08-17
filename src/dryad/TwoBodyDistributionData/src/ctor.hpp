/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
TwoBodyDistributionData() = default;

TwoBodyDistributionData( const TwoBodyDistributionData& ) = default;
TwoBodyDistributionData( TwoBodyDistributionData&& ) = default;

TwoBodyDistributionData& operator=( const TwoBodyDistributionData& ) = default;
TwoBodyDistributionData& operator=( TwoBodyDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param frame       the reference frame of the distribution data
 *  @param angle       the angular distributions
 *  @param normalise   option to indicate whether or not to normalise
 *                     all probability data (default: no normalisation)
 */
TwoBodyDistributionData( ReferenceFrame frame,
                         AngularDistributions angle,
                         bool normalise = false ) :
    frame_( std::move( frame ) ), angle_( std::move( angle ) ) {

  if ( normalise ) {

    this->normalise();
  }
}
