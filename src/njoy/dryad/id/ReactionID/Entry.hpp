/**
 *  @class
 *  @brief Private helper class
 */
class Entry {

  /* fields */

  // tuple for logical ordering:
  // - projectile
  // - target
  // - reaction type
  std::tuple< ParticleID, ParticleID, ReactionType > tuple_;

  std::vector< std::string > symbols_;
  std::optional< ParticleID > residual_;

  std::size_t hash_;

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
    if ( ! type.isSpecial() ) {

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

    for ( const auto& symbol : type.symbols() ) {

      symbols.emplace_back( incident + symbol );
    }

    return symbols;
  }

public:

  /* constructor */
  Entry( ParticleID projectile, ParticleID target, ReactionType type ) :
      tuple_( std::move( projectile ), std::move( target ), std::move( type ) ),
      symbols_( generateSymbols( projectile, target, type ) ),
      residual_( generateResidual( projectile, target, type ) ) {

    this->hash_ = std::hash< std::string >{}( this->symbol() );
  }

  /* methods */
  const std::tuple< ParticleID, ParticleID, ReactionType >& reaction() const noexcept { return this->tuple_; }
  const ParticleID& projectile() const noexcept { return std::get< 0 >( this->reaction() ); }
  const ParticleID& target() const noexcept { return std::get< 1 >( this->reaction() ); }
  const ReactionType& reactionType() const noexcept { return std::get< 2 >( this->reaction() ); }
  const std::optional< ParticleID >& residual() const noexcept { return this->residual_; }
  const std::string& symbol() const noexcept { return this->symbols().front(); }
  const std::vector< std::string >& symbols() const noexcept { return this->symbols_; }

  std::size_t hash() const { return this->hash_; }
};
