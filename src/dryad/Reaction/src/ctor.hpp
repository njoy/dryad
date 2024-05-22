/**
 *  @brief Constructor
 *
 *  @param id           the reaction identifier
 *  @param mass_q       the mass difference Q value
 *  @param reaction_q   the reaction Q value
 *  @param xs           the cross section of the reaction
 *  @param linearised   a flag indicating whether or not the data is
 *                      linearised
 */
Reaction( ReactionID&& id, double mass_q, double reaction_q,
          CrossSection&& xs, bool linearised ) :
    id_( std::move( id ) ), mass_difference_qvalue_( mass_q ),
    reaction_qvalue_( reaction_q ), xs_( std::move( xs ) ),
    linearised_( linearised ) {}

public:

Reaction( const Reaction& ) = default;
Reaction( Reaction&& ) = default;

Reaction& operator=( const Reaction& ) = default;
Reaction& operator=( Reaction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param id   the reaction identifier
 *  @param mass_q       the mass difference Q value
 *  @param reaction_q   the reaction Q value
 *  @param xs   the cross section of the reaction
 */
Reaction( ReactionID id, double mass_q, double reaction_q, CrossSection xs ) :
    Reaction( std::move( id ),
              mass_q,
              reaction_q,
              std::move( xs ),
              xs.isLinearised() ? true : false ) {}
