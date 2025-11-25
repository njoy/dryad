/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */

  // tuple for logical ordering:
  // - principal quantum number
  // - azimuthal quantum number
  // - total angular momentum = l +/- 1/2
  std::tuple< short, short, std::optional< double > > numbers_;

  std::optional< short > mt_;
  std::string symbol_;
  std::vector< std::string > alternatives_;

  std::size_t hash_;

public:

  /* constructor */
  Entry( short n, short l, double j, short mt,
         std::string symbol,
         std::vector< std::string > alternatives = {} ) :
      numbers_( n, l, j ), mt_( mt ),
      symbol_( std::move( symbol ) ),
      alternatives_( std::move( alternatives ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  Entry( short n, short l, std::string symbol ) :
      numbers_( n, l, std::nullopt ), mt_( std::nullopt ),
      symbol_( std::move( symbol ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  /* methods */
  const std::tuple< short, short, std::optional< double > >& quantumNumbers() const { return this->numbers_; }
  short principalQuantumNumber() const { return std::get<0>( this->quantumNumbers() ); }
  short azimuthalQuantumNumber() const { return std::get<1>( this->quantumNumbers() ); }
  const std::optional< double >& totalAngularMomentum() const { return std::get<2>( this->quantumNumbers() ); }

  const std::optional< short >& mt() const { return this->mt_; }
  const std::string& symbol() const { return this->symbol_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }

  std::size_t hash() const { return this->hash_; }
};
