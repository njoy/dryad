/**
 *  @brief Private constructor
 */
Reaction( id::ReactionID&& id,
          ReactionCategory&& type,
          std::optional< std::vector< id::ReactionID > >&& partials,
          TabulatedCrossSection&& xs,
          std::vector< ReactionProduct >&& products,
          std::optional< double >&& mass_q,
          std::optional< double >&& reaction_q,
          bool normalise ) :
    id_( std::move( id ) ), category_( std::move( type ) ),
    partials_( std::move( partials ) ),
    mass_difference_qvalue_( mass_q ),
    reaction_qvalue_( reaction_q ),
    xs_( std::move( xs ) ),
    products_( std::move( products ) ) {

  if ( normalise ) {

    this->normalise();
  }
}

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
 *  @brief Constructor for primary reactions
 *
 *  @param id           the reaction identifier
 *  @param xs           the cross section of the reaction
 *  @param products     the reaction products
 *  @param mass_q       the mass difference Q value
 *  @param reaction_q   the reaction Q value
 *  @param normalise    option to indicate whether or not to normalise
 *                      all probability data (default: no normalisation)
 */
Reaction( id::ReactionID id,
          TabulatedCrossSection xs,
          std::vector< ReactionProduct > products = {},
          std::optional< double > mass_q = std::nullopt,
          std::optional< double > reaction_q = std::nullopt,
          bool normalise = false ) :
    Reaction( std::move( id ),
              ReactionCategory::Primary,
              std::nullopt,
              std::move( xs ),
              std::move( products ),
              std::move( mass_q ),
              std::move( reaction_q ),
              normalise ) {}

/**
 *  @brief Constructor for summation reactions
 *
 *  Summation reactions do not have Q values associated to them. A cross section
 *  weighted Q value could be calculated using the partial reactions making up
 *  the summation reaction.
 *
 *  @param id          the reaction identifier
 *  @param xs          the cross section of the reaction
 *  @param partials    the identifiers of the partials of the reaction
 *  @param products    the reaction products associated to the summation reaction
 *                     (defaults to no reaction products)
 *  @param normalise   option to indicate whether or not to normalise
 *                     all probability data (default: no normalisation)
 */
Reaction( id::ReactionID id,
          std::vector< id::ReactionID > partials,
          TabulatedCrossSection xs,
          std::vector< ReactionProduct > products = {},
          bool normalise = false ) :
    Reaction( std::move( id ),
              ReactionCategory::Summation,
              std::move( partials ),
              std::move( xs ),
              std::move( products ),
              std::nullopt,
              std::nullopt,
              normalise ) {}
