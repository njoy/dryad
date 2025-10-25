/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
SpinGroup() = default;

SpinGroup( const SpinGroup& ) = default;
SpinGroup( SpinGroup&& ) = default;

SpinGroup& operator=( const SpinGroup& ) = default;
SpinGroup& operator=( SpinGroup&& ) = default;

private:

/**
 *  @brief Private intermediate constructor
 */
SpinGroup( std::tuple< std::vector< Channel >, ResonanceTable > data ) :
    channels_( std::move( std::get< 0 >( data ) ) ),
    table_( std::move( std::get< 1 >( data ) ) ) {

  this->processChannels();
  verifySpinGroup( this->channels(), this->resonanceTable() );
}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] channels     the channels in the spingroup
 *  @param[in] resonances   the resonance table of the spingroup
 */
SpinGroup( std::vector< Channel > channels,
           ResonanceTable resonances ) :
    SpinGroup( createData( std::move( channels ), std::move( resonances ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] channels     the channel data in the spingroup
 */
SpinGroup( std::vector< ChannelData > channels ) :
    SpinGroup( createData( std::move( channels ) ) ) {}
