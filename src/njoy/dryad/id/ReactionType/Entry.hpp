/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */

  // tuple for logical ordering:
  // - flag for special reactions
  // - interaction type (nuclear or atomic)
  // - outgoing particle number with level, subshell or mt
  std::tuple< InteractionType, bool, std::int64_t > tuple_;

  std::optional< short > mt_;
  std::optional< std::map< ParticleID, short > > ejectiles_;
  std::vector< std::string > symbols_;
  std::optional< std::string > designator_;
  std::optional< short > level_;
  std::optional< int > dza_;

  std::size_t hash_;

  static std::optional< std::string >
  getDesignator( const InteractionType& type,
                 const std::vector< std::string >& symbols ) {

    if ( ( type == InteractionType::Atomic ) &&
         ( symbols.size() > 1 ) ){

      return symbols.front();
    }
    else {

      return std::nullopt;
    }
  }

  static std::optional< int >
  calculateDZA( const InteractionType& type,
                const std::optional< std::map< ParticleID, short > >& ejectiles ) {

    if ( ( type == InteractionType::Nuclear ) && ( ejectiles.has_value() ) ){

      return std::accumulate( ejectiles->begin(), ejectiles->end(), 0,
                              [] ( int result, const auto& pair )
                                 { return result + pair.second * pair.first.za(); } );
    }
    else {

      return std::nullopt;
    }
  }

  /* constructor */
  Entry( bool special, std::int64_t number, std::optional< short > mt,
         std::optional< std::map< ParticleID, short > > ejectiles,
         std::vector< std::string > symbols,
         InteractionType interaction, std::optional< short > level ) :
    tuple_( std::move( interaction ), special, number ),
    mt_( std::move( mt ) ),
    ejectiles_( std::move( ejectiles ) ),
    symbols_( std::move( symbols ) ),
    designator_( std::nullopt ),
    level_( std::move( level ) ),
    dza_( std::nullopt ) {

    this->dza_ = calculateDZA( this->type(), this->particles() );
    this->designator_ = getDesignator( this->type(), this->symbols() );

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

public:

  /* constructor */

//  // special reaction without an mt number
//  Entry( std::int64_t number, InteractionType interaction,
//         std::vector< std::string > symbols ) :
//    Entry( std::move( number ), std::nullopt, std::nullopt,
//           std::move( symbols ),
//           std::move( interaction ), std::nullopt ) {}

  // special reaction with an mt number
  Entry( std::int64_t number, short mt, InteractionType interaction,
         std::vector< std::string > symbols ) :
    Entry( true, std::move( number ), std::move( mt ), std::nullopt,
           std::move( symbols ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction with an mt number but no defined level/subshell
  Entry( std::int64_t number, short mt, InteractionType interaction,
         std::vector< std::string > symbols,
         std::map< ParticleID, short > ejectiles ) :
    Entry( false, std::move( number ), std::move( mt ),
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbols ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction with an mt number and level/subshell
  Entry( std::int64_t number, short mt, InteractionType interaction,
         std::vector< std::string > symbols,
         std::map< ParticleID, short > ejectiles,
         short level ) :
    Entry( false, std::move( number ), std::move( mt ),
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbols ),
           std::move( interaction ), std::move( level ) ) {}

  // normal reaction without an mt number and no defined level/subshell
  Entry( std::int64_t number, InteractionType interaction,
         std::vector< std::string > symbols,
         std::map< ParticleID, short > ejectiles ) :
    Entry( false, std::move( number ), std::nullopt,
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbols ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction without an mt number and a level/subshell
  Entry( std::int64_t number, InteractionType interaction,
         std::vector< std::string > symbols,
         std::map< ParticleID, short > ejectiles,
         short level ) :
    Entry( false, std::move( number ), std::nullopt,
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbols ),
           std::move( interaction ), std::move( level ) ) {}

  /* methods */
  const std::tuple< InteractionType, bool, std::int64_t >& tuple() const { return this->tuple_; }
  const InteractionType& type() const { return std::get< 0 >( this->tuple() ); }
  std::int64_t number() const { return std::get< 2 >( this->tuple() ); }

  const std::optional< short >& mt() const { return this->mt_; }
  const std::string& symbol() const { return this->symbols().front(); }
  const std::vector< std::string >& symbols() const { return this->symbols_; }
  const std::optional< std::map< ParticleID, short > >& particles() const {

    return this->ejectiles_;
  }
  const std::optional< short >& level() const { return this->level_; }
  const std::optional< int >& dza() const { return this->dza_; }
  const std::optional< std::string >& partialDesignator() const { return this->designator_; }

  std::size_t hash() const { return this->hash_; }
};
