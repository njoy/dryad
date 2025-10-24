/**
 *  @brief Constructor
 *
 *  @param[in] radius   the channel radius to be used for P, S and phi
 */
ChannelRadii( Radius radius ) :
    penetrability_( std::move( radius ) ),
    shift_factor_( std::nullopt ),
    phase_shift_( std::nullopt ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] trueRadius        the channel radius to be used for P and S
 *  @param[in] effectiveRadius   the channel radius to be used for phi
 */
ChannelRadii( Radius trueRadius,
              Radius effectiveRadius ) :
    penetrability_( std::move( trueRadius ) ),
    shift_factor_( std::nullopt ),
    phase_shift_( std::move( effectiveRadius ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] penetrabilityRadius   the channel radius to be used for P
 *  @param[in] shiftFactorRadius     the channel radius to be used for S
 *  @param[in] phaseShiftRadius      the channel radius to be used for phi
 */
ChannelRadii( Radius penetrabilityRadius,
              Radius shiftFactorRadius,
              Radius phaseShiftRadius ) :
    penetrability_( std::move( penetrabilityRadius ) ),
    shift_factor_( std::move( shiftFactorRadius ) ),
    phase_shift_( std::move( phaseShiftRadius ) ) {}
