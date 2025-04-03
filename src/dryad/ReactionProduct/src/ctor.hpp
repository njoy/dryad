/**
 *  @brief Constructor
 *
 *  @param id             the reaction product identifier
 *  @param multiplicity   the multiplicity of the reaction product
 *  @param linearised     a flag indicating whether or not the data is
 *                        linearised
 */
ReactionProduct( id::ParticleID&& id,
                 Multiplicity&& multiplicity,
                 std::optional< DistributionData >&& distribution,
                 std::optional< TabulatedAverageEnergy >&& averageEnergy,
                 bool linearised ) :
    id_( std::move( id ) ),
    multiplicity_( std::move( multiplicity ) ),
    distribution_( std::move( distribution ) ),
    average_energy_( std::move( averageEnergy ) ),
    linearised_( linearised ) {}

public:

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
                 std::optional< DistributionData > distribution,
                 std::optional< TabulatedAverageEnergy > averageEnergy ) :
    ReactionProduct( std::move( id ),
                     std::move( multiplicity ),
                     std::move( distribution ),
                     std::move( averageEnergy ),
                     std::visit(
                         tools::overload{
                             [] ( int ) { return true; },
                             [] ( const TabulatedMultiplicity& multiplicity )
                                { return multiplicity.isLinearised(); },
                             [] ( const PolynomialMultiplicity& )
                                { return false; } },
                         multiplicity ) ) {}

/**
 *  @brief Constructor
 *
 *  @param id             the reaction product identifier
 *  @param multiplicity   the reaction product multiplicity
 */
ReactionProduct( id::ParticleID id,
                 Multiplicity multiplicity ) :
    ReactionProduct( std::move( id ),
                     std::move( multiplicity ),
                     std::nullopt,
                     std::nullopt ) {}

/**
 *  @brief Constructor
 *
 *  @param id             the reaction product identifier
 *  @param multiplicity   the reaction product multiplicity
 *  @param distribution   the reaction product distribution data
 */
ReactionProduct( id::ParticleID id,
                 Multiplicity multiplicity,
                 DistributionData distribution ) :
    ReactionProduct( std::move( id ),
                     std::move( multiplicity ),
                     std::move( distribution ),
                     std::nullopt ) {}

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
