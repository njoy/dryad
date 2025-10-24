/**
 *  @brief Default constructor (for pybind11 purposes only)
 */
ChannelQuantumNumbers() = default;

ChannelQuantumNumbers( const ChannelQuantumNumbers& ) = default;
ChannelQuantumNumbers( ChannelQuantumNumbers&& ) = default;

ChannelQuantumNumbers& operator=( const ChannelQuantumNumbers& ) = default;
ChannelQuantumNumbers& operator=( ChannelQuantumNumbers&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] l        the orbital angular momentum
 *  @param[in] s        the channel spin
 *  @param[in] J        the total angular momentum
 *  @param[in] parity   the parity
 */
ChannelQuantumNumbers( unsigned int l,
                       double s,
                       double J,
                       short parity ) :
  l_( l ), s_( s ), J_( J ), parity_( parity ) {}

private:

/**
 *  @brief Private intermediate constructor
 */
ChannelQuantumNumbers( const std::tuple< unsigned int, double, double, short >& numbers ) :
  ChannelQuantumNumbers( std::get< 0 >( numbers ), std::get< 1 >( numbers ),
                         std::get< 2 >( numbers ), std::get< 3 >( numbers ) ) {}

public:

/**
 *  @brief Constructor
 *
 *  @param[in] string   the string representation
 */
ChannelQuantumNumbers( const std::string& string ) :
  ChannelQuantumNumbers( parseNumbers( string ) ) {}
