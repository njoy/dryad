/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
FrohnerBackground() = default;

FrohnerBackground( const FrohnerBackground& ) = default;
FrohnerBackground( FrohnerBackground&& ) = default;

FrohnerBackground& operator=( const FrohnerBackground& ) = default;
FrohnerBackground& operator=( FrohnerBackground&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] distantLevelParameter   the distant level parameter
 *  @param[in] poleStrength            the pole strength
 *  @param[in] averageRadiationWidth   the average radiation width
 *  @param[in] lowerSingularity        the lower logarithmic singularity values
 *  @param[in] upperSingularity        the upper logarithmic singularity values
 */
FrohnerBackground( double distantLevelParameter,
                   double poleStrength,
                   double averageRadiationWidth,
                   double lowerSingularity,
                   double upperSingularity ) :
  distant_level_( distantLevelParameter ),
  pole_strength_( poleStrength ),
  average_radiation_width_( averageRadiationWidth ),
  lower_singularity_( lowerSingularity ),
  upper_singularity_( upperSingularity ) {}
