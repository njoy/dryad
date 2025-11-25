/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */

  // tuple for logical ordering:
  // - za or order number for fundamental particles
  // - optional level number
  // - vector of vacancies
  std::tuple< int, std::optional< LevelID >, std::optional< std::vector< ElectronSubshellID > > > tuple_;

  short z_;
  short a_;
  short e_;
  int za_;

  std::string symbol_;
  std::vector< std::string > alternatives_;

  std::size_t hash_;

public:

  /* constructor */

  // elements
  Entry( ElementID element, std::string symbol, std::vector< std::string > alternatives ) :
      tuple_( element.number() * 1000, std::nullopt, std::nullopt ),
      z_( element.number() ),
      a_( 0 ),
      e_( 0 ),
      za_( element.number() * 1000 ),
      symbol_( std::move( symbol ) ),
      alternatives_( std::move( alternatives ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  // ions
  Entry( ElementID element, std::vector< ElectronSubshellID > vacancies,
         std::string symbol, std::vector< std::string > alternatives ) :
      tuple_( element.number() * 1000, std::nullopt, std::move( vacancies ) ),
      z_( element.number() ),
      a_( 0 ),
      e_( 0 ),
      za_( element.number() * 1000 ),
      symbol_( std::move( symbol ) ),
      alternatives_( std::move( alternatives ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  // nuclides
  Entry( ElementID element, short mass, LevelID level,
         std::string symbol, std::vector< std::string > alternatives ) :
      tuple_( element.number() * 1000 + mass, std::move( level ), std::nullopt ),
      z_( element.number() ),
      a_( mass ),
      e_( level.number() ),
      za_( element.number() * 1000 + mass ),
      symbol_( std::move( symbol ) ),
      alternatives_( std::move( alternatives ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  // fundamental particles
  Entry( int number, short z, short a,
         std::string symbol, std::vector< std::string > alternatives ) :
      tuple_( number, std::nullopt, {} ),
      z_( z ),
      a_( a ),
      e_( 0 ),
      za_( z * 1000 + a ),
      symbol_( std::move( symbol ) ),
      alternatives_( std::move( alternatives ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  /* methods */
  const std::tuple< int, std::optional< LevelID >, std::optional< std::vector< ElectronSubshellID > > >& tuple() const { return this->tuple_; }
  short z() const { return this->z_; }
  short a() const { return this->a_; }
  short e() const { return this->e_; }
  int za() const { return this->za_; }
  const std::optional< std::vector< ElectronSubshellID > >& subshell() const { return std::get< 2 >( this->tuple() ); }
  const std::string& symbol() const { return this->symbol_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }

  std::size_t hash() const { return this->hash_; }
};
