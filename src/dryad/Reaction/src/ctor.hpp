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
          std::optional< std::vector< id::ReactionID > >&& summation,
          TabulatedCrossSection&& xs,
          std::vector< ReactionProduct >&& products,
          std::optional< double >&& mass_q,
          std::optional< double >&& reaction_q,
          bool linearised ) :
    id_( std::move( id ) ), type_( std::move( type ) ),
    partials_( std::move( summation ) ),
    mass_difference_qvalue_( mass_q ),
    reaction_qvalue_( reaction_q ),
    xs_( std::move( xs ) ),
    products_( std::move( products ) ),
    linearised_( linearised ) {}

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
Reaction() = default;

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
              std::nullopt,
              std::move( xs ),
              std::move( products ),
              std::move( mass_q ),
              std::move( reaction_q ),
              xs.isLinearised() ? true : false ) {}

/**
 *  @brief Constructor for primary reactions
 *
 *  @param id           the reaction identifier
 *  @param xs           the cross section of the reaction
 *  @param products     the reaction products
 *  @param mass_q       the mass difference Q value
 *  @param reaction_q   the reaction Q value
 */
Reaction( id::ReactionID id,
          TabulatedCrossSection xs,
          std::vector< ReactionProduct > products = {},
          std::optional< double > mass_q = std::nullopt,
          std::optional< double > reaction_q = std::nullopt ) :
    Reaction( std::move( id ),
              ReactionType::Primary,
              std::nullopt,
              std::move( xs ),
              std::move( products ),
              std::move( mass_q ),
              std::move( reaction_q ),
              xs.isLinearised() ? true : false ) {}

/**
 *  @brief Constructor for summation reactions
 *
 *  @param id          the reaction identifier
 *  @param xs          the cross section of the reaction
 *  @param partials    the identifiers of the partials of the reaction
 */
Reaction( id::ReactionID id,
          std::vector< id::ReactionID > partials,
          TabulatedCrossSection xs ) :
    Reaction( std::move( id ),
              ReactionType::Summation,
              std::move( partials ),
              std::move( xs ),
              {},
              std::nullopt,
              std::nullopt,
              xs.isLinearised() ? true : false ) {}
