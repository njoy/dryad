#ifndef NJOY_DRYAD_ID_REACTIONID
#define NJOY_DRYAD_ID_REACTIONID

// system includes
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/split.hpp"
#include "dryad/InteractionType.hpp"
#include "dryad/id/ParticleID.hpp"
#include "dryad/id/ReactionType.hpp"

namespace njoy {
namespace dryad {
namespace id {

  /**
   *  @class
   *  @brief The reaction identifier, with associated symbols, aliases, particles, etc.
   */
  class ReactionID {

    /* helper class */
    #include "dryad/id/ReactionID/Entry.hpp"

    /* type aliases */
    using Key = std::tuple< ParticleID, ParticleID, ReactionType >;

    /* static data */
    static inline std::vector< Entry > entries{};
    static inline std::unordered_map< std::string, std::size_t > string_conversion_dictionary{};
    static inline std::map< Key, std::size_t > tuple_conversion_dictionary{};

    /* fields */
    std::size_t index_;

    /* auxiliary functions */
    #include "dryad/id/ReactionID/src/getIndex.hpp"

  public:

    /* constructor */
    #include "dryad/id/ReactionID/src/ctor.hpp"

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
     *  @brief Return the symbol
     */
    const std::string& symbol() const {

      return entries[ this->index_ ].longSymbol();
    }

    /**
     *  @brief Return the interaction type (nuclear or atomic)
     */
    const InteractionType& interactionType() const {

      return this->reactionType().interactionType();
    }

    /**
     *  @brief Return the reaction type
     */
    const ReactionType& reactionType() const {

      return entries[ this->index_ ].reactionType();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator==( const ReactionID& left, const ReactionID& right ) {

      return ( left.projectile() == right.projectile() ) &&
             ( left.target() == right.target() ) &&
             ( left.reactionType() == right.reactionType() );
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

      if ( left.projectile() < right.projectile() ) {

        return true;
      }
      else if ( left.target() < right.target() ) {

        return true;
      }
      else {

        return left.reactionType() < right.reactionType();
      }
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

      return std::hash< std::string >{}( key.symbol() );
    }
  };

} // namespace std

#endif
