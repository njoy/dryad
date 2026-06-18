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
 *                                 ParticleEmissionWidthConversion)
 *  @param[in] reference_energy    the energy at which reduced widths are
 *                                 defined; defaults to 1 eV
 */
UnresolvedChannel( Channel channel,
                   WidthConversion conversion,
                   double reference_energy = 1. ) :
    channel_( std::move( channel ) ),
    conversion_( std::move( conversion ) ),
    reference_energy_( reference_energy ) {}
