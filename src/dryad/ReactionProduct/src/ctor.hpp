/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ReactionProduct() = default;

ReactionProduct( const ReactionProduct& ) = default;
ReactionProduct( ReactionProduct&& ) = default;

ReactionProduct& operator=( const ReactionProduct& ) = default;
ReactionProduct& operator=( ReactionProduct&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param id              the reaction product identifier
 *  @param multiplicity    the multiplicity of the reaction product
 *  @param distribution    the optional reaction product distribution data
 *  @param averageEnergy   the optional average reaction product energy
 */
ReactionProduct( id::ParticleID id,
                 Multiplicity multiplicity,
                 std::optional< DistributionData > distribution = std::nullopt,
                 std::optional< TabulatedAverageEnergy > averageEnergy = std::nullopt ) :
    id_( std::move( id ) ),
    multiplicity_( std::move( multiplicity ) ),
    distribution_( std::move( distribution ) ),
    average_energy_( std::move( averageEnergy ) ) {}

/**
 *  @brief Constructor
 *
 *  @param id              the reaction product identifier
 *  @param multiplicity    the reaction product multiplicity
 *  @param averageEnergy   the average reaction product energy
 */
ReactionProduct( id::ParticleID id,
                 Multiplicity multiplicity,
                 TabulatedAverageEnergy averageEnergy ) :
    ReactionProduct( std::move( id ),
                     std::move( multiplicity ),
                     std::nullopt,
                     std::move( averageEnergy ) ) {}
