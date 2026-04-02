/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ResonanceTable() = default;

ResonanceTable( const ResonanceTable& ) = default;
ResonanceTable( ResonanceTable&& ) = default;

ResonanceTable& operator=( const ResonanceTable& ) = default;
ResonanceTable& operator=( ResonanceTable&& ) = default;

private:

/**
 *  @brief Private intermediate constructor
 */
ResonanceTable( std::tuple< std::vector< id::ChannelID >,
                            std::vector< double >,
                            std::vector< std::vector< double > > >&& data ) :
    channels_( std::move( std::get< 0 >( data ) ) ),
    energies_( std::move( std::get< 1 >( data ) ) ),
    amplitudes_( std::move( std::get< 2 >( data ) ) ) {

  this->verifyTable( this->channels(), this->energies(),
                     this->reducedWidthAmplitudes() );
}

public:

/**
 *  @brief Constructor
 *
 *  The energies and channels do not have to be sorted (they will be sorted
 *  upon construction).
 *
 *  @param[in] channels     the channel identifiers (nc values)
 *  @param[in] energies     the level energies (ne values)
 *  @param[in] amplitudes   the reduced width amplitudes (nc arrays of ne values)
 */
ResonanceTable( std::vector< id::ChannelID > channels,
                std::vector< double > energies,
                std::vector< std::vector< double > > amplitudes ) :
    ResonanceTable( processTable( std::move( channels ),
                                  std::move( energies ),
                                  std::move( amplitudes ) ) ) {}

/**
 *  @brief Constructor
 *
 *  The energies do not have to be sorted (they will be sorted upon construction).
 *
 *  @param[in] channel      the channel identifier
 *  @param[in] energies     the level energies
 *  @param[in] amplitudes   the reduced width amplitudes
 */
ResonanceTable( id::ChannelID channel,
                std::vector< double > energies,
                std::vector< double > amplitudes ) :
    ResonanceTable( std::vector< id::ChannelID >{ std::move( channel ) },
                    std::move( energies ),
                    std::vector< std::vector< double > >{ std::move( amplitudes ) } ) {}

/**
 *  @brief Constructor for an empty table
 *
 *  @param[in] channels   the channel identifiers (nc values)
 */
ResonanceTable( std::vector< id::ChannelID > channels ) :
    ResonanceTable( processTable( std::move( channels ) ) ) {}

/**
 *  @brief Constructor for an empty table
 *
 *  @param[in] channel   the channel identifier
 */
ResonanceTable( id::ChannelID channel ) :
    ResonanceTable( std::vector< id::ChannelID >{ std::move( channel ) } ) {}
