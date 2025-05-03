#ifndef NJOY_ELEMENTARY_LEVELID
#define NJOY_ELEMENTARY_LEVELID

// system includes
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// other includes

namespace njoy {
namespace dryad {
namespace id {

  /**
   *  @class
   *  @brief The excited state or level identifier
   *
   *  Comparison operators are provided using the logical order given by the
   *  level number. A hash function and override for std::hash is also
   *  provided.
   */
  class LevelID {

  public:

    // the value representing the continuum level
    static constexpr unsigned char continuum = 150;

  private:

    /* helper class */
    #include "dryad/id/LevelID/Entry.hpp"

    /* static fields */
    static inline const std::vector< Entry > entries = [] () {

      std::vector< Entry > entries;
      entries.emplace_back( 0, "" );
      for ( unsigned char level = 1; level < continuum; ++level ) {

        entries.emplace_back( level, std::string( "_e" ) + std::to_string( level ) );
      }
      entries.emplace_back( continuum, "[continuum]" );
      return entries;
    }();
    static inline const std::unordered_map< std::string, const Entry* >
    conversion_dictionary = [] ( const auto& vector ) {

      std::unordered_map< std::string, const Entry* > conversion;
      for ( const auto& entry : vector ) {

        const Entry* pointer = std::addressof( entry );
        conversion[ entry.symbol() ] = pointer;
      }
      return conversion;
    }( entries );

    /* fields */
    const Entry* entry_;

    /* auxiliary functions */
    #include "dryad/id/LevelID/src/getPointer.hpp"

  public:

    /* constructor */
    #include "dryad/id/LevelID/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the level number
     */
    unsigned char number() const noexcept {

      return this->entry_->number();
    }

    /**
     *  @brief Return the element symbol
     */
    const std::string& symbol() const noexcept {

      return this->entry_->symbol();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator==( const LevelID& left, const LevelID& right ) {

      return left.number() == right.number();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator!=( const LevelID& left, const LevelID& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<( const LevelID& left, const LevelID& right ) {

      return left.number() < right.number();
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>( const LevelID& left, const LevelID& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<=( const LevelID& left, const LevelID& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>=( const LevelID& left, const LevelID& right ) {

      return ! ( left < right );
    }
  };

} // id namespace
} // dryad namespace
} // njoy namespace

namespace std {

  // std::hash override for the LevelID class
  template <>
  struct hash< njoy::dryad::id::LevelID > {

    size_t operator()( const njoy::dryad::id::LevelID& key ) const {

      return key.number();
    }
  };

} // namespace std

#endif
