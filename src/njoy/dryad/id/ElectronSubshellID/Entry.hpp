/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */

  short n_; // principal quantum number
  short l_; // azimuthal quantum number
  std::optional< double > j_; // total angular momentum = l +/- 1/2

  std::optional< short > mt_;
  std::string symbol_;
  std::vector< std::string > alternatives_;

  std::size_t hash_;

public:

  /* constructor */
  Entry( short n, short l, double j, short mt,
         std::string symbol,
         std::vector< std::string > alternatives = {} ) :
      n_( n ), l_( l ), j_( std::move( j ) ), mt_( mt ),
      symbol_( std::move( symbol ) ),
      alternatives_( std::move( alternatives ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  Entry( short n, short l,
         std::string symbol ) :
      n_( n ), l_( l ), j_( std::nullopt ), mt_( std::nullopt ),
      symbol_( std::move( symbol ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  /* methods */
  const short& principalQuantumNumber() const { return this->n_; }
  const short& azimuthalQuantumNumber() const { return this->l_; }
  const std::optional< double >& totalAngularMomentum() const { return this->j_; }

  const std::optional< short >& mt() const { return this->mt_; }
  const std::string& symbol() const { return this->symbol_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }

  std::size_t hash() const { return this->hash_; }
};
