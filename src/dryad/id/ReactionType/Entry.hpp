/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  long number_;
  std::optional< short > mt_;
  std::optional< std::vector< std::pair< ParticleID, short > > > ejectiles_;
  std::string symbol_;
  std::vector< std::string > alternatives_;
  InteractionType interaction_;
  std::optional< short > level_;
  std::optional< int > dza_;

  static std::optional< int >
  calculateDZA( const InteractionType& type,
                const std::optional< std::vector< std::pair< ParticleID, short > > >& ejectiles ) {

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
  Entry( long number, std::optional< short > mt,
         std::optional< std::vector< std::pair< ParticleID, short > > > ejectiles,
         std::string symbol, std::vector< std::string > alternatives,
         InteractionType interaction, std::optional< short > level ) :
    number_( std::move( number ) ),
    mt_( std::move( mt ) ),
    ejectiles_( std::move( ejectiles ) ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ),
    interaction_( std::move( interaction ) ),
    level_( std::move( level ) ),
    dza_( std::nullopt ) {

    this->dza_ = calculateDZA( this->type(), this->particles() );
  }

public:

  /* constructor */

  // special reaction without an mt number
  Entry( long number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives ) :
    Entry( std::move( number ), std::nullopt, std::nullopt,
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::nullopt ) {}

  // special reaction with an mt number
  Entry( long number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives ) :
    Entry( std::move( number ), std::move( mt ), std::nullopt,
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction with an mt number but no defined level/subshell
  Entry( long number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::vector< std::pair< ParticleID, short > > ejectiles ) :
    Entry( std::move( number ), std::move( mt ),
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction with an mt number and level/subshell
  Entry( long number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::vector< std::pair< ParticleID, short > > ejectiles,
         short level ) :
    Entry( std::move( number ), std::move( mt ),
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::move( level ) ) {}

  // normal reaction without an mt number and no defined level/subshell
  Entry( long number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::vector< std::pair< ParticleID, short > > ejectiles ) :
    Entry( std::move( number ), std::nullopt,
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::nullopt ) {}

  // normal reaction without an mt number and a level/subshell
  Entry( long number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::vector< std::pair< ParticleID, short > > ejectiles,
         short level ) :
    Entry( std::move( number ), std::nullopt,
           std::make_optional( std::move( ejectiles ) ),
           std::move( symbol ), std::move( alternatives ),
           std::move( interaction ), std::move( level ) ) {}

  /* methods */
  long number() const { return this->number_; }
  const std::optional< short >& mt() const { return this->mt_; }
  const std::string& symbol() const { return this->symbol_; }
  const std::vector< std::string >& alternatives() const { return this->alternatives_; }
  const InteractionType& type() const { return this->interaction_; }
  const std::optional< std::vector< std::pair< ParticleID, short > > >& particles() const {

    return this->ejectiles_;
  }
  const std::optional< short >& level() const { return this->level_; }
  const std::optional< int >& dza() const { return this->dza_; }
};
