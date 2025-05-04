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
  std::optional< id::ElectronSubshellID > subshell_;
  std::string symbol_;
  std::vector< std::string > alternatives_;

public:

  /* constructor */
  Entry( int number, id::ElementID element, short mass, id::LevelID level,
         std::string symbol, std::vector< std::string > alternatives ) :
    number_( number ), element_( std::move( element ) ), mass_( mass ),
    level_( std::move( level ) ), subshell_( std::nullopt ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ) {}
  Entry( int number, id::ElementID element, id::ElectronSubshellID subshell,
         std::string symbol, std::vector< std::string > alternatives ) :
     number_( number ), element_( std::move( element ) ), mass_( 0 ),
     level_( 0 ), subshell_( std::move( subshell ) ),
     symbol_( std::move( symbol ) ),
     alternatives_( std::move( alternatives ) ) {}

  /* methods */
  int number() const noexcept { return this->number_; }
  const id::ElementID& element() const noexcept { return this->element_; }
  short mass() const noexcept { return this->mass_; }
  const id::LevelID& level() const noexcept { return this->level_; }
  const std::optional< id::ElectronSubshellID >& subshell() const noexcept { return this->subshell_; }
  const std::string& symbol() const noexcept { return this->symbol_; }
  const std::vector< std::string >& alternatives() const noexcept { return this->alternatives_; }
};
