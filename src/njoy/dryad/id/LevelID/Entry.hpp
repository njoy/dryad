/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  // we need at least 999 as the max value so short is sufficient

  /* fields */
  short number_;

  std::string symbol_;

public:

  /* constructor */
  Entry( short number, std::string symbol ) :
    number_( number ), symbol_( std::move( symbol ) ) {}

  /* methods */
  short number() const { return this->number_; }
  const std::string& symbol() const { return this->symbol_; }
};
