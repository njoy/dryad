/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ResonanceTable() = default;

ResonanceTable( const ResonanceTable& ) = default;
ResonanceTable( ResonanceTable&& ) = default;

ResonanceTable& operator=( const ResonanceTable& ) = default;
ResonanceTable& operator=( ResonanceTable&& ) = default;

/**
 *  @brief Constructor
 *
 *  The ResonanceTable class takes the reduced amplitude widths for a
 *  number of channels (at least one channel must be given).
 *
 *  @param[in] channels     the channel identifiers (nc values)
 *  @param[in] energies     the resonance energies (ne values)
 *  @param[in] amplitudes   the reduced width amplitudes (nc arrays of ne values)
 */
ResonanceTable( std::vector< id::ChannelID > channels,
                std::vector< double > energies,
                std::vector< std::vector< double > > amplitudes ) :
    channels_( std::move( channels ) ),
    energies_( std::move( energies ) ),
    amplitudes_( std::move( amplitudes ) ) {

  this->verifyTable( this->channels(), this->energies(),
                     this->reducedWidthAmplitudes() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] channel      the channel identifier
 *  @param[in] energies     the resonance energies
 *  @param[in] amplitudes   the reduced width amplitudes
 */
ResonanceTable( id::ChannelID channel,
                std::vector< double > energies,
                std::vector< double > amplitudes ) :
    ResonanceTable( std::vector< id::ChannelID >{ std::move( channel ) },
                    std::move( energies ),
                    std::vector< std::vector< double > >{ std::move( amplitudes ) } ) {}
