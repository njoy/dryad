/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  resonances::ChannelQuantumNumbers numbers_;
  ReactionID reaction_;
  std::optional< std::size_t > partial_;

  std::vector< std::string > symbols_;

  static std::vector< std::string >
  generateSymbols( const ReactionID& reaction,
                   const resonances::ChannelQuantumNumbers& numbers,
                   const std::optional< std::size_t >& partial ) {

    std::string symbol = reaction.symbol() + numbers.symbol();
    if ( partial.has_value() ) {

      symbol += "[" + std::to_string( partial.value() ) + "]";
    }
    return { symbol };
  }

public:

  /* constructor */
  Entry( ReactionID reaction,
         resonances::ChannelQuantumNumbers numbers,
         std::optional< std::size_t > partial ) :
    numbers_( std::move( numbers ) ),
    reaction_( std::move( reaction ) ),
    partial_( std::move( partial ) ),
    symbols_( generateSymbols( reaction, numbers, partial ) ) {}

  /* methods */
  const ReactionID& reaction() const noexcept { return this->reaction_; }
  const resonances::ChannelQuantumNumbers& numbers() const noexcept { return this->numbers_; }
  const std::optional< std::size_t >& partial() const noexcept { return this->partial_; }
  const std::string& symbol() const noexcept { return this->symbols().front(); }
  const std::vector< std::string >& symbols() const noexcept { return this->symbols_; }
};
