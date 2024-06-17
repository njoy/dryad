/**
 *  @brief Constructor
 *
 *  @param id             the reaction product identifier
 *  @param multiplicity   the multiplicity of the reaction product
 *  @param linearised     a flag indicating whether or not the data is
 *                        linearised
 */
ReactionProduct( ParticleID&& id,
                 Multiplicity&& multiplicity, bool linearised ) :
    id_( std::move( id ) ), multiplicity_( std::move( multiplicity ) ),
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
ReactionProduct( ParticleID id,
                 Multiplicity multiplicity ) :
    ReactionProduct( std::move( id ),
                     std::move( multiplicity ), true ) {}
