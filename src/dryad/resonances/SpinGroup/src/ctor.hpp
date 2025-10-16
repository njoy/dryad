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
 *  The SpinGroup class takes the reduced amplitude widths for a
 *  number of channels (at least one channel must be given).
 *
 *  @param[in] channels     the channel identifiers (nc values)
 *  @param[in] energies     the resonance energies (ne values)
 *  @param[in] amplitudes   the reduced amplitude widths (nc arrays of ne values)
 */
SpinGroup( std::vector< Channel > channels,
           ResonanceTable resonances ) :
    channels_( std::move( channels ) ),
    resonances_( std::move( resonances ) ) {}
