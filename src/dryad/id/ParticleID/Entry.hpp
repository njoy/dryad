/**
 *  @class
 *  @brief Private helper class to retrieve particle numbers, symbol and aliases
 */
class Entry {

  /* fields */
  id::ElementID element_;
  int a_;
  int l_;
  std::string symbol_;
  std::optional< std::string > name_;
  std::vector< std::string > alternatives_;

public:

  /* constructor */
  Entry( int number, std::string symbol, std::string name,
         std::vector< std::string > alternatives ) :
    number_( number ), symbol_( std::move( symbol ) ),
    name_( std::move( name ) ), alternatives_( std::move( alternatives ) ) {}

  /* methods */
  auto number() const { return this->number_; }
  const std::string& symbol() const { return this->symbol_; }
  const std::string& name() const { return this->name_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }
};
