private:

/**
 *  @brief Private constructor taking an index
 */
constexpr ReactionType( std::size_t index ) : index_( index ) {};

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ReactionType() = default;

ReactionType( const ReactionType& ) = default;
ReactionType( ReactionType&& ) = default;

ReactionType& operator=( const ReactionType& ) = default;
ReactionType& operator=( ReactionType&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param mt   the mt number
 */
ReactionType( int mt ) : index_( getIndex( mt ) ) {}

// /**
//  *  @brief Constructor
//  *
//  *  @param particle   the particle identifier
//  */
// ReactionType( const std::string& particle ) : index_( getIndex( particle ) ) {}
