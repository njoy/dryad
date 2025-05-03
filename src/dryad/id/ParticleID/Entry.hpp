/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  int number_;
  id::ElementID element_;
  short mass_;
  id::LevelID level_;
  std::string symbol_;
  std::vector< std::string > alternatives_;

public:

  /* constructor */
  Entry( int number, id::ElementID element, short mass, id::LevelID level,
         std::string symbol, std::vector< std::string > alternatives ) :
    number_( number ), element_( std::move( element ) ), mass_( mass ),
    level_( std::move( level ) ), symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ) {}

  /* methods */
  int number() const { return this->number_; }
  const id::ElementID& element();
  short mass();
  const id::LevelID& level();
  const std::string& symbol() const { return this->symbol_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }
};
