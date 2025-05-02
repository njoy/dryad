/**
 *  @class
 *  @brief Private helper class to retrieve symbols, names and alternatives
 */
class Entry {

  // unsigned char has a max value of 255

  /* fields */
  unsigned char number_;
  std::string symbol_;
  std::string name_;
  std::vector< std::string > alternatives_;

public:

  /* constructor */
  Entry( int number, std::string symbol, std::string name,
         std::vector< std::string > alternatives ) :
    number_( number ), symbol_( std::move( symbol ) ),
    name_( std::move( name ) ), alternatives_( std::move( alternatives ) ) {}

  /* methods */
  unsigned char number() const { return this->number_; }
  const std::string& symbol() const { return this->symbol_; }
  const std::string& name() const { return this->name_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }
};
