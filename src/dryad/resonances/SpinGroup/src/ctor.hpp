/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
SpinGroup() = default;

SpinGroup( const SpinGroup& ) = default;
SpinGroup( SpinGroup&& ) = default;

SpinGroup& operator=( const SpinGroup& ) = default;
SpinGroup& operator=( SpinGroup&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] channels     the channels in the spingroup
 *  @param[in] resonances   the resonance table of the spingroup
 */
SpinGroup( std::vector< Channel > channels,
           ResonanceTable resonances ) :
    channels_( std::move( channels ) ),
    resonances_( std::move( resonances ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] channels     the channels in the spingroup
 *  @param[in] resonances   the resonance table of the spingroup
 */
SpinGroup( std::vector< ChannelData > channels ) :
    channels_( createChannels( channels ) ),
    resonances_( createResonanceTable( channels ) ) {}
