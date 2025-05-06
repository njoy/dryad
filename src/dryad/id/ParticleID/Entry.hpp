/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  int number_;
  short element_;
  short mass_;
  short level_;
  std::optional< id::ElectronSubshellID > subshell_;
  std::string symbol_;
  std::vector< std::string > alternatives_;

public:

  /* constructor */
  Entry( int number, short element, short mass, short level,
         std::string symbol, std::vector< std::string > alternatives ) :
    number_( number ), element_( std::move( element ) ), mass_( mass ),
    level_( std::move( level ) ), subshell_( std::nullopt ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ) {}
  Entry( int number, short element, id::ElectronSubshellID subshell,
         std::string symbol, std::vector< std::string > alternatives ) :
     number_( number ), element_( std::move( element ) ), mass_( 0 ),
     level_( 0 ), subshell_( std::move( subshell ) ),
     symbol_( std::move( symbol ) ),
     alternatives_( std::move( alternatives ) ) {}

  /* methods */
  int number() const noexcept { return this->number_; }
  short z() const noexcept { return this->element_; }
  short a() const noexcept { return this->mass_; }
  short e() const noexcept { return this->level_; }
  const std::optional< id::ElectronSubshellID >& subshell() const noexcept { return this->subshell_; }
  const std::string& symbol() const noexcept { return this->symbol_; }
  const std::vector< std::string >& alternatives() const noexcept { return this->alternatives_; }
};
