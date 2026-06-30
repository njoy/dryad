/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
UnresolvedChannel() = default;

UnresolvedChannel( const UnresolvedChannel& ) = default;
UnresolvedChannel( UnresolvedChannel&& ) = default;

UnresolvedChannel& operator=( const UnresolvedChannel& ) = default;
UnresolvedChannel& operator=( UnresolvedChannel&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] channel             the underlying channel
 *  @param[in] conversion          the width conversion strategy (one of
 *                                 ConstantWidthConversion or
 *                                 NeutronWidthConversion)
 *                                 
 *  @param[in] reference_energy    the energy at which reduced widths are
 *                                 defined; defaults to 1 eV
 */
UnresolvedChannel( Channel channel,
                   double reference_energy = 1. ) : 
    Channel( std::move( channel) ),
    reference_energy_( reference_energy ),
    conversion_factor_( 
        selectWidthConversionFactor( Channel::quantumNumbers().orbitalAngularMomentum(),
                                     reference_energy,
                                     Channel::outgoingParticlePair() ) ) {}

UnresolvedChannel(  id::ChannelID identifier,
                    ParticlePair incident,
                    std::optional< ParticlePair > outgoing,
                    double qValue,
                    std::optional< double > boundary,
                    ChannelRadii radii,
                    Kinematics kinematics = Kinematics::NonRelativistic,
                    std::optional< Background > background = std::nullopt,
                    double reference_energy = 1. ) :
    UnresolvedChannel( Channel( std::move( identifier ), 
                                std::move( incident ), 
                                std::move( outgoing ), 
                                qValue, 
                                std::move( boundary ),
                                std::move( radii ),
                                std::move( kinematics ),
                                std::move( background )
                                ),
                        reference_energy ) {}

