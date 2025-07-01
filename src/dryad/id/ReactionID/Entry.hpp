/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  ParticleID projectile_;
  ParticleID target_;
  ReactionType type_;
  std::optional< ParticleID > residual_;
//  std::string short_symbol_;
  std::string long_symbol_;

  static std::optional< ParticleID >
  generateResidual( const ParticleID& projectile,
                    const ParticleID& target,
                    const ReactionType& type ) {

    if ( type.isSpecial() ) {

      return std::nullopt;
    }
    else {

      return type.resolve( projectile, target );
    }
  }

  static std::string
  generateLongSymbol( const ParticleID& projectile,
                      const ParticleID& target,
                      const ReactionType& type ) {

    std::string symbol( projectile.symbol() + "," + target.symbol() + "->" );
    if ( type.isSpecial() ) {

      symbol += type.symbol();
    }
    else {

      if ( type.particles()->size() == 0 ) {

        symbol += "g,";
      }
      else {

        for ( const auto& pair : type.particles().value() ) {

          if ( pair.second > 1 ) {

            symbol += std::to_string( pair.second );
          }
          symbol += pair.first.symbol();
          symbol += ",";
        }
      }
      symbol += type.resolve( projectile, target ).symbol();

      if ( type.hasPartialDesignator() ) {

        symbol += "[" + type.partialDesignator().value() + "]";
      }
    }
    return symbol;
  }

public:

  /* constructor */
  Entry( ParticleID projectile, ParticleID target, ReactionType type ) :
    projectile_( std::move( projectile ) ),
    target_( std::move( target ) ),
    type_( std::move( type ) ),
//    short_symbol_( generateShortSymbol( projectile, target, type ) ),
    long_symbol_( generateLongSymbol( projectile, target, type ) ),
    residual_( generateResidual( projectile, target, type ) ) {}

  /* methods */
  const ParticleID& projectile() const noexcept { return this->projectile_; }
  const ParticleID& target() const noexcept { return this->target_; }
  const ReactionType& reactionType() const noexcept { return this->type_; }
  const std::optional< ParticleID >& residual() const noexcept { return this->residual_; }
//  const std::string& shortSymbol() const noexcept { return this->short_symbol_; }
  const std::string& longSymbol() const noexcept { return this->long_symbol_; }
};
