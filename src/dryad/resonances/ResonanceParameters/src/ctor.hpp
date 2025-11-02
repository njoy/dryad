/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ResonanceParameters() = default;

ResonanceParameters( const ResonanceParameters& ) = default;
ResonanceParameters( ResonanceParameters&& ) = default;

ResonanceParameters& operator=( const ResonanceParameters& ) = default;
ResonanceParameters& operator=( ResonanceParameters&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] resolved   the resolved resonance compound systems
 */
ResonanceParameters( std::vector< CompoundSystem > resolved ) :
    resolved_( std::move( resolved ) ) {}
