/**
 *  @brief Constructor
 *
 *  @param id           the reaction identifier
 *  @param xs           the cross section of the reaction
 *  @param linearised   a flag indicating whether or not the data is
 *                      linearised
 */
Reaction( ReactionID&& id, CrossSection&& xs,
          bool linearised ) :
    id_( std::move( id ) ), xs_( std::move( xs ) ),
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
 *  @param xs   the cross section of the reaction
 */
Reaction( ReactionID id, CrossSection xs ) :
    Reaction( std::move( id ),
              std::move( xs ),
              xs.isLinearised() ? true : false ) {}
