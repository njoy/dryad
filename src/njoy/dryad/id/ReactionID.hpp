#ifndef NJOY_DRYAD_ID_REACTIONID
#define NJOY_DRYAD_ID_REACTIONID

// system includes
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>

// other includes
#include "tools/split.hpp"
#include "njoy/dryad/InteractionType.hpp"
#include "njoy/dryad/id/ParticleID.hpp"
#include "njoy/dryad/id/ReactionType.hpp"

namespace njoy {
namespace dryad {
namespace id {

  /**
   *  @class
   *  @brief The reaction identifier, with associated symbols, aliases, particles, etc.
   */
  class ReactionID {

    /* helper class */

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

    /* type aliases */

    using Key = std::tuple< ParticleID, ParticleID, ReactionType >;

    /* static data */

    static inline std::vector< Entry > entries{};
    static inline std::unordered_map< std::string, std::size_t > string_conversion_dictionary{};
    static inline std::map< Key, std::size_t > tuple_conversion_dictionary{};

    /* fields */

    std::size_t index_;

    /* auxiliary functions */

    /**
     *  @brief Retrieve the index to the reaction identifier information entry
     *
     *  @param projectile   the projectile
     *  @param target       the target
     *  @param type         the reaction type
     */
    static std::size_t getIndex( const ParticleID& projectile, const ParticleID& target,
                                 const ReactionType& type ) {

      auto key = std::make_tuple( projectile, target, type );
      auto iter = tuple_conversion_dictionary.find( key );
      if ( iter != tuple_conversion_dictionary.end() ) {

        return iter->second;
      }
      else {

        // index of the new entry
        auto index = entries.size();

        // create entry and set up lookup
        entries.emplace_back( projectile, target, type );
        tuple_conversion_dictionary[ key ] = index;
        for ( const auto& symbol : entries.back().symbols() ) {

          string_conversion_dictionary[ symbol ] = index;
        }

        return index;
      }
    }

    /**
     *  @brief Retrieve the index to the reaction identifier information entry
     *
     *  @param string   the reaction identifier string
     */
    static std::size_t getIndex( const std::string& string ) {

      auto iter = string_conversion_dictionary.find( string );
      if ( iter != string_conversion_dictionary.end() ) {

        return iter->second;
      }
      else {

        // split the reaction symbol in incident and outgoing particles
        auto strings = njoy::tools::split( string, "->" );
        if ( strings.size() == 2 ) {

          // split the projectile and target
          auto incident = njoy::tools::split( strings[0], ',' );
          if ( incident.size() == 2 ) {

            ParticleID projectile( incident[0] );
            ParticleID target( incident[1] );

            // check for a registered type
            if ( ReactionType::isRegistered( strings[1] ) ) {

              // create the reaction type
              auto type = ReactionType( strings[1] );
              return getIndex( projectile, target, type );
            }
            else {

              // check for partial designator [xxxx]
              if ( strings[1].back() == ']' &&
                   strings[1].find( "[all]" ) == std::string::npos &&
                   strings[1].find( "[continuum]" ) == std::string::npos ) {

                auto pos = strings[1].find( '[' );
                if ( pos != std::string::npos ) {

                  // create the reaction type
                  auto type = ReactionType( strings[1].substr( pos + 1, strings[1].size() - pos - 2 ) );
                  return getIndex( projectile, target, type );
                }
              }
              else {

                // split the outgoing particles
                auto outgoing = njoy::tools::split( strings[1], ',' );
                if ( outgoing.size() > 1 ) {

                  // the last one should be the residual
                  ParticleID residual( outgoing.back() );

                  // get the outgoing particles
                  auto particles = strings[1].substr( 0, strings[1].size() - outgoing.back().size() - 1 );
                  if ( residual.e() != LevelID::all ) {

                    if ( residual.e() == LevelID::continuum ) {

                      particles += "(c)";
                    }
                    else {

                      particles += "(" + std::to_string( residual.e() ) + ")";
                    }
                  }

                  // create the reaction type and verify against the residual
                  auto type = ReactionType( particles );
                  if ( type.resolve( projectile, target ) == residual ) {

                    return getIndex( projectile, target, type );
                  }
                }
              }
            }
          }
        }

        // if you get to this point, this is not a reaction string
        throw std::invalid_argument( "\'" + string + "\' does not define a "
                                     "reaction identifier string" );
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor taking an index
     */
    constexpr ReactionID( std::size_t index ) : index_( index ) {};

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ReactionID() = default;

    ReactionID( const ReactionID& ) = default;
    ReactionID( ReactionID&& ) = default;

    ReactionID& operator=( const ReactionID& ) = default;
    ReactionID& operator=( ReactionID&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param projectile   the projectile
     *  @param target       the target
     *  @param type         the reaction type
     */
    ReactionID( const ParticleID& projectile, const ParticleID& target,
                const ReactionType& type ) :
      index_( getIndex( projectile, target, type ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param projectile   the projectile
     *  @param target       the target
     *  @param mt           the mt number
     */
    ReactionID( const ParticleID& projectile, const ParticleID& target, int mt ) :
      ReactionID( projectile, target, ReactionType( projectile, mt, target.e() ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param projectile   the projectile
     *  @param target       the target
     *  @param type         the string representing the reaction type
     */
    ReactionID( const ParticleID& projectile, const ParticleID& target,
                const std::string& type ) :
      ReactionID( projectile, target, ReactionType( type ) ) {}

    // /**
    //  *  @brief Constructor
    //  *
    //  *  @param projectile   the projectile
    //  *  @param target       the target
    //  *  @param particles    the outgoing particles (excluding the residual)
    //  *  @param level        the level number of the residual
    //  */
    // ReactionID( const ParticleID& projectile, const ParticleID& target,
    //                const std::map< ParticleID, short >& particles, int level ) :
    //   ReactionID( projectile, target, ReactionType( particles, level ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param string   the reaction symbol
     */
    ReactionID( const std::string& symbol ) :
      index_( getIndex( symbol ) ) {}

    /* static methods */

    /**
     *  @brief Return the number of currently registered identifiers
     */
    static std::size_t size() noexcept {

      return entries.size();
    }

    /* methods */

    /**
     *  @brief Return the projectile
     */
    const ParticleID& projectile() const {

      return entries[ this->index_ ].projectile();
    }

    /**
     *  @brief Return the target
     */
    const ParticleID& target() const {

      return entries[ this->index_ ].target();
    }

    /**
     *  @brief Return the reaction type
     */
    const ReactionType& reactionType() const {

      return entries[ this->index_ ].reactionType();
    }

    /**
     *  @brief Return the outgoing particles (excluding the residual)
     */
    const std::optional< std::map< ParticleID, short > >& particles() const {

      return this->reactionType().particles();
    }

    /**
     *  @brief Return the residual
     */
    const std::optional< ParticleID >& residual() const {

      return entries[ this->index_ ].residual();
    }

    /**
     *  @brief Return the interaction type (nuclear or atomic)
     */
    const InteractionType& interactionType() const {

      return this->reactionType().interactionType();
    }

    /**
     *  @brief Return the mt number for this reaction type
     */
    const std::optional< short >& mt() const {

      return this->reactionType().mt();
    }

    /**
     *  @brief Return whether or not the reaction type is ENDF compatible
     */
    bool isCompatibleWithENDF() const {

      return this->reactionType().isCompatibleWithENDF();
    }

    /**
     *  @brief Return the symbol
     */
    const std::string& symbol() const {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the hash
     */
    std::size_t hash() const {

      return entries[ this->index_ ].hash();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator==( const ReactionID& left, const ReactionID& right ) {

      return entries[ left.index_ ].reaction() == entries[ right.index_ ].reaction();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator!=( const ReactionID& left, const ReactionID& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<( const ReactionID& left, const ReactionID& right ) {

      return entries[ left.index_ ].reaction() < entries[ right.index_ ].reaction();
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>( const ReactionID& left, const ReactionID& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<=( const ReactionID& left, const ReactionID& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>=( const ReactionID& left, const ReactionID& right ) {

      return ! ( left < right );
    }
  };

} // id namespace
} // dryad namespace
} // njoy namespace

namespace std {

  // std::hash override for the ReactionID class
  template <>
  struct hash< njoy::dryad::id::ReactionID > {

    std::size_t operator()( const njoy::dryad::id::ReactionID& key ) const {

      return key.hash();
    }
  };

} // namespace std

#endif
