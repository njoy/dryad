/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  std::int64_t number_;
  std::optional< short > mt_;
  std::optional< std::map< ParticleID, short > > ejectiles_;
  std::string symbol_;
  std::vector< std::string > alternatives_;
  InteractionType interaction_;
  std::optional< std::string > designator_;
  std::optional< short > level_;
  std::optional< int > dza_;

  static std::optional< std::string >
  getDesignator( const InteractionType& type,
                 const std::vector< std::string >& alternatives ) {

    if ( ( type == InteractionType::Atomic ) &&
         ( alternatives.size() > 0 ) ){

      return alternatives.front();
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
  Entry( std::int64_t number, std::optional< short > mt,
         std::optional< std::map< ParticleID, short > > ejectiles,
         std::string symbol, std::vector< std::string > alternatives,
         InteractionType interaction, std::optional< short > level ) :
    number_( std::move( number ) ),
    mt_( std::move( mt ) ),
    ejectiles_( std::move( ejectiles ) ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ),
    interaction_( std::move( interaction ) ),
    designator_( std::nullopt ),
    level_( std::move( level ) ),
    dza_( std::nullopt ) {

    this->dza_ = calculateDZA( this->type(), this->particles() );
    this->designator_ = getDesignator( this->type(), this->alternatives() );
  }

public:

  /* constructor */

  // special reaction without an mt number
  Entry( std::int64_t number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives ) :
    Entry( std::move( number ), std::nullopt, std::nullopt,
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::nullopt ) {}

  // special reaction with an mt number
  Entry( std::int64_t number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives ) :
    Entry( std::move( number ), std::move( mt ), std::nullopt,
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction with an mt number but no defined level/subshell
  Entry( std::int64_t number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::map< ParticleID, short > ejectiles ) :
    Entry( std::move( number ), std::move( mt ),
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction with an mt number and level/subshell
  Entry( std::int64_t number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::map< ParticleID, short > ejectiles,
         short level ) :
    Entry( std::move( number ), std::move( mt ),
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::move( level ) ) {}

  // normal reaction without an mt number and no defined level/subshell
  Entry( std::int64_t number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::map< ParticleID, short > ejectiles ) :
    Entry( std::move( number ), std::nullopt,
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction without an mt number and a level/subshell
  Entry( std::int64_t number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::map< ParticleID, short > ejectiles,
         short level ) :
    Entry( std::move( number ), std::nullopt,
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::move( level ) ) {}

  /* methods */
  std::int64_t number() const { return this->number_; }
  const std::optional< short >& mt() const { return this->mt_; }
  const std::string& symbol() const { return this->symbol_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }
  const InteractionType& type() const { return this->interaction_; }
  const std::optional< std::map< ParticleID, short > >& particles() const {

    return this->ejectiles_;
  }
  const std::optional< short >& level() const { return this->level_; }
  const std::optional< int >& dza() const { return this->dza_; }
  const std::optional< std::string >& partialDesignator() const { return this->designator_; }
};
