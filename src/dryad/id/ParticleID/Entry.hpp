/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  int number_;
  short z_;
  short a_;
  short e_;
  int za_;
  std::optional< id::ElectronSubshellID > subshell_;
  std::string symbol_;
  std::vector< std::string > alternatives_;

public:

  /* constructor */
  Entry( int number, short z, short a, short e,
         std::string symbol, std::vector< std::string > alternatives ) :
    number_( number ), z_( z ), a_( a ), e_( e ),
    za_( static_cast< int >( z ) * 1000 + a ),
    subshell_( std::nullopt ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ) {}
  Entry( int number, short z, id::ElectronSubshellID subshell,
         std::string symbol, std::vector< std::string > alternatives ) :
     number_( number ), z_( z ), a_( 0 ), e_( 0 ),
     za_( static_cast< int >( z ) * 1000 ),
     subshell_( std::move( subshell ) ),
     symbol_( std::move( symbol ) ),
     alternatives_( std::move( alternatives ) ) {}

  /* methods */
  int number() const { return this->number_; }
  short z() const { return this->z_; }
  short a() const { return this->a_; }
  short e() const { return this->e_; }
  int za() const { return this->za_; }
  const std::optional< id::ElectronSubshellID >& subshell() const { return this->subshell_; }
  const std::string& symbol() const { return this->symbol_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }
};
