/**
 *  @brief Constructor
 *
 *  @param id           the reaction identifier
 *  @param type         the reaction type
 *  @param xs           the cross section of the reaction
 *  @param products     the reaction products
 *  @param mass_q       the mass difference Q value
 *  @param reaction_q   the reaction Q value
 *  @param linearised   a flag indicating whether or not the data is
 *                      linearised
 */
Reaction( id::ReactionID&& id,
          ReactionType&& type,
          TabulatedCrossSection&& xs,
          std::vector< ReactionProduct >&& products,
          std::optional< double >&& mass_q,
          std::optional< double >&& reaction_q,
          bool linearised ) :
    id_( std::move( id ) ), type_( std::move( type ) ),
    mass_difference_qvalue_( mass_q ),
    reaction_qvalue_( reaction_q ),
    xs_( std::move( xs ) ),
    products_( std::move( products ) ),
    linearised_( linearised ) {}

public:

Reaction( const Reaction& ) = default;
Reaction( Reaction&& ) = default;

Reaction& operator=( const Reaction& ) = default;
Reaction& operator=( Reaction&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param id           the reaction identifier
 *  @param xs           the cross section of the reaction
 *  @param products     the reaction products
 *  @param mass_q       the mass difference Q value
 *  @param reaction_q   the reaction Q value
 */
Reaction( id::ReactionID id,
          ReactionType type,
          TabulatedCrossSection xs,
          std::vector< ReactionProduct > products = {},
          std::optional< double > mass_q = std::nullopt,
          std::optional< double > reaction_q = std::nullopt ) :
    Reaction( std::move( id ),
              std::move( type ),
              std::move( xs ),
              std::move( products ),
              std::move( mass_q ),
              std::move( reaction_q ),
              xs.isLinearised() ? true : false ) {}
