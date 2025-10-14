private:

/**
 *  @brief Private constructor taking an index
 */
constexpr ChannelID( std::size_t index ) : index_( index ) {};

public:

/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ChannelID() = default;

ChannelID( const ChannelID& ) = default;
ChannelID( ChannelID&& ) = default;

ChannelID& operator=( const ChannelID& ) = default;
ChannelID& operator=( ChannelID&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param reaction   the reaction
 *  @param numbers    the channel quantum numbers
 */
ChannelID( const ReactionID& reaction,
           const resonances::ChannelQuantumNumbers& numbers,
           const std::optional< std::size_t >& partial = std::nullopt ) :
  index_( getIndex( reaction, numbers, partial ) ) {}

/**
 *  @brief Constructor
 *
 *  @param string   the channel symbol
 */
ChannelID( const std::string& symbol ) :
  index_( getIndex( symbol ) ) {}
