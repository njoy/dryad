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

