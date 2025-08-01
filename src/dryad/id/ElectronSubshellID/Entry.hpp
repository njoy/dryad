/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  short number_;
  std::string symbol_;
  std::string name_;

public:

  /* constructor */
  Entry( short number, std::string symbol, std::string name ) :
    number_( number ), symbol_( std::move( symbol ) ),
    name_( std::move( name ) ) {}

  /* methods */
  short number() const { return this->number_; }
  const std::string& symbol() const { return this->symbol_; }
  const std::string& name() const { return this->name_; }
};
