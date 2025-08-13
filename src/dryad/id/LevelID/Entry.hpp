/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  // unsigned char has a max value of 255

  /* fields */
  unsigned char number_;
  std::string symbol_;

public:

  /* constructor */
  Entry( unsigned char number, std::string symbol ) :
    number_( number ), symbol_( std::move( symbol ) ) {}

  /* methods */
  unsigned char number() const { return this->number_; }
  const std::string& symbol() const { return this->symbol_; }
};
