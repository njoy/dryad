#ifndef NJOY_DRYAD_ID_LEVELID
#define NJOY_DRYAD_ID_LEVELID

// system includes
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
    static constexpr short continuum = 998;

    // the value representing any level
    static constexpr short all = continuum + 1;

  private:

    /* helper class */

    /**
     *  @class
     *  @brief Private helper class
     */
    class Entry {

      // we need at least 999 as the max value so short is sufficient

      /* fields */
      short number_;

      std::string symbol_;

    public:

      /* constructor */
      Entry( short number, std::string symbol ) :
        number_( number ), symbol_( std::move( symbol ) ) {}

      /* methods */
      short number() const { return this->number_; }
      const std::string& symbol() const { return this->symbol_; }
    };

    /* static fields */

    static inline const std::vector< Entry > entries = [] () {

      std::vector< Entry > entries;
      entries.emplace_back( 0, "" );
      for ( short level = 1; level < continuum; ++level ) {

        entries.emplace_back( level, std::string( "_e" ) + std::to_string( level ) );
      }
      entries.emplace_back( continuum, "[continuum]" );
      entries.emplace_back( all, "[all]" );
      return entries;
    }();
    static inline const std::unordered_map< std::string, std::size_t >
    conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< std::string, std::size_t > conversion;
      conversion[ "_e0" ] = 0;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        conversion[ entries[ index ].symbol() ] = index;
      }
      return conversion;
    }( entries );

    /* fields */
    std::size_t index_;

    /* auxiliary functions */

    /**
     *  @brief Retrieve the index to the level information entry
     *
     *  @param number    the level number
     */
    static std::size_t getIndex( int number ) {

      if ( ( number < 0 ) || ( number >= static_cast< int >( entries.size() ) ) ) {

        throw std::invalid_argument( "Not a level number: \'" + std::to_string( number ) + "\'" );
      }

      return static_cast< std::size_t >( number );
    }

    /**
     *  @brief Retrieve the index to the level information entry
     *
     *  @param string    the level symbol
     */
    static std::size_t getIndex( const std::string& string ) {

      try {

        return conversion_dictionary.at( string );
      }
      catch ( ... ) {

        throw std::invalid_argument( "Not an element symbol or name: \'" + string + "\'" );
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    LevelID() = default;

    LevelID( const LevelID& ) = default;
    LevelID( LevelID&& ) = default;

    LevelID& operator=( const LevelID& ) = default;
    LevelID& operator=( LevelID&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param number   the level number
     */
    LevelID( int number ) : index_( getIndex( number ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param string   the level identifier
     */
    LevelID( const std::string& string ) : index_( getIndex( string ) ) {}

    /* methods */

    /**
     *  @brief Return the number of currently registered level numbers
     */
    static std::size_t size() {

      return entries.size();
    }

    /**
     *  @brief Return the level number
     */
    short number() const {

      return entries[ this->index_ ].number();
    }

    /**
     *  @brief Return the element symbol
     */
    const std::string& symbol() const {

      return entries[ this->index_ ].symbol();
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
