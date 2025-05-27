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

public:

  /* constructor */
  Entry( long number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives ) :
    number_( number ),
    mt_( std::nullopt ),
    ejectiles_( std::nullopt ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ),
    interaction_( interaction ),
    level_( std::nullopt ) {}
  Entry( long number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives ) :
    number_( number ),
    mt_( mt ),
    ejectiles_( std::nullopt ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ),
    interaction_( interaction ),
    level_( std::nullopt ) {}
  Entry( long number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::vector< std::pair< ParticleID, short > > ejectiles ) :
    number_( number ),
    mt_( mt ),
    ejectiles_( std::move( ejectiles ) ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ),
    interaction_( interaction ),
    level_( std::nullopt ) {}
  Entry( long number, short mt, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::vector< std::pair< ParticleID, short > > ejectiles,
         short level ) :
    number_( number ),
    mt_( mt ),
    ejectiles_( std::move( ejectiles ) ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ),
    interaction_( interaction ),
    level_( level ) {}
  Entry( long number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::vector< std::pair< ParticleID, short > > ejectiles ) :
    number_( number ),
    mt_( std::nullopt ),
    ejectiles_( std::move( ejectiles ) ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ),
    interaction_( interaction ),
    level_( std::nullopt ) {}
  Entry( long number, InteractionType interaction, std::string symbol,
         std::vector< std::string > alternatives,
         std::vector< std::pair< ParticleID, short > > ejectiles,
         short level ) :
    number_( number ),
    mt_( std::nullopt ),
    ejectiles_( std::move( ejectiles ) ),
    symbol_( std::move( symbol ) ),
    alternatives_( std::move( alternatives ) ),
    interaction_( interaction ),
    level_( level ) {}

  /* methods */
  long number() const noexcept { return this->number_; }
  const std::optional< short >& mt() const noexcept { return this->mt_; }
  const std::string& symbol() const noexcept { return this->symbol_; }
  const std::vector< std::string >& alternatives() const noexcept { return this->alternatives_; }
  const InteractionType& type() const { return this->interaction_; }
  const std::optional< std::vector< std::pair< ParticleID, short > > >& particles() const noexcept {

    return this->ejectiles_;
  }
  const std::optional< short >& level() const noexcept { return this->level_; }
};
