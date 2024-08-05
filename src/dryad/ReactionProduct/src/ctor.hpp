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
                 bool linearised ) :
    id_( std::move( id ) ),
    multiplicity_( std::move( multiplicity ) ),
    distribution_( std::move( distribution ) ),
    linearised_( linearised ) {}

public:

ReactionProduct( const ReactionProduct& ) = default;
ReactionProduct( ReactionProduct&& ) = default;

ReactionProduct& operator=( const ReactionProduct& ) = default;
ReactionProduct& operator=( ReactionProduct&& ) = default;

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
                     std::visit(
                         tools::overload{
                             [] ( int ) { return true; },
                             [] ( const TabulatedMultiplicity& multiplicity )
                                { return multiplicity.isLinearised(); } },
                         multiplicity ) ) {}

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
                     std::visit(
                         tools::overload{
                             [] ( int ) { return true; },
                             [] ( const TabulatedMultiplicity& multiplicity )
                                { return multiplicity.isLinearised(); } },
                         multiplicity ) ) {}
