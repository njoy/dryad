/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */
  ParticleID projectile_;
  ParticleID target_;
  ReactionType type_;
  // std::string short_symbol_;
  std::vector< std::string > symbols_;
  std::optional< ParticleID > residual_;

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

  static std::vector< std::string >
  generateSymbols( const ParticleID& projectile,
                   const ParticleID& target,
                   const ReactionType& type ) {

    std::vector< std::string > symbols;
    std::string incident( projectile.symbol() + "," + target.symbol() + "->" );
    if ( type.isSpecial() ) {

      symbols.emplace_back( incident + type.symbol() );
    }
    else {

      if ( type.particles()->size() == 0 ) {

        symbols.emplace_back( incident + "g" );
      }
      else {

        symbols.emplace_back( incident );
        if ( type.particles().value().size() > 1 ) {

          symbols.emplace_back( incident );
        }

        auto size = type.particles().value().size() - 1;
        for ( auto iter = type.particles().value().begin();
              iter != type.particles().value().end(); ++iter ) {

          std::string particle;
          if ( iter->second > 1 ) {

            particle = std::to_string( iter->second );
          }
          particle += iter->first.symbol();
          for ( auto& symbol: symbols ) {

            symbol += particle;
          }
          if ( size != 0 ) {

            symbols.front() += ",";
            --size;
          }
        }
      }

      auto residual = generateResidual( projectile, target, type ).value().symbol();
      for ( auto& symbol: symbols ) {

        symbol += "," + residual;
      }

      if ( type.hasPartialDesignator() ) {

        std::string partial = "[" + type.partialDesignator().value() + "]";
        for ( auto& symbol: symbols ) {

          symbol += partial;
        }
      }
    }
    return symbols;
  }

public:

  /* constructor */
  Entry( ParticleID projectile, ParticleID target, ReactionType type ) :
    projectile_( std::move( projectile ) ),
    target_( std::move( target ) ),
    type_( std::move( type ) ),
    // short_symbol_( generateShortSymbol( projectile, target, type ) ),
    symbols_( generateSymbols( projectile, target, type ) ),
    residual_( generateResidual( projectile, target, type ) ) {}

  /* methods */
  const ParticleID& projectile() const noexcept { return this->projectile_; }
  const ParticleID& target() const noexcept { return this->target_; }
  const ReactionType& reactionType() const noexcept { return this->type_; }
  const std::optional< ParticleID >& residual() const noexcept { return this->residual_; }
  // const std::string& shortSymbol() const noexcept { return this->short_symbol_; }
  const std::string& longSymbol() const noexcept { return this->symbols().front(); }
  const std::vector< std::string >& symbols() const noexcept { return this->symbols_; }
};
