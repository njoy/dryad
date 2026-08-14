#ifndef NJOY_DRYAD_ID_CHANNELID
#define NJOY_DRYAD_ID_CHANNELID

// system includes
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>

// other includes
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/resonances/ChannelQuantumNumbers.hpp"

namespace njoy {
namespace dryad {
namespace id {

  /**
   *  @class
   *  @brief The channel identifier, with associated reaction and quantum numbers.
   *
   *  When using comparison on the channel identifier, we use a Jpi,l,s,reaction,partial
   *  ordering.
   */
  class ChannelID {

    /* helper class */

    /**
     *  @class
     *  @brief Private helper class
     */
    class Entry {

      /* fields */
      resonances::ChannelQuantumNumbers numbers_;
      ReactionID reaction_;
      std::optional< std::size_t > partial_;

      std::vector< std::string > symbols_;

      std::size_t hash_;

      static std::vector< std::string >
      generateSymbols( const ReactionID& reaction,
                       const resonances::ChannelQuantumNumbers& numbers,
                       const std::optional< std::size_t >& partial ) {

        std::string symbol = reaction.symbol() + numbers.symbol();
        if ( partial.has_value() ) {

          symbol += "[" + std::to_string( partial.value() ) + "]";
        }
        return { symbol };
      }

    public:

      /* constructor */
      Entry( ReactionID reaction,
             resonances::ChannelQuantumNumbers numbers,
             std::optional< std::size_t > partial ) :
          numbers_( std::move( numbers ) ),
          reaction_( std::move( reaction ) ),
          partial_( std::move( partial ) ),
          symbols_( generateSymbols( reaction, numbers, partial ) ) {

        this->hash_ = std::hash< std::string >{}( this->symbol() );
      }

      /* methods */
      const ReactionID& reaction() const noexcept { return this->reaction_; }
      const resonances::ChannelQuantumNumbers& numbers() const noexcept { return this->numbers_; }
      const std::optional< std::size_t >& partial() const noexcept { return this->partial_; }
      const std::string& symbol() const noexcept { return this->symbols().front(); }
      const std::vector< std::string >& symbols() const noexcept { return this->symbols_; }

      std::size_t hash() const { return this->hash_; }
    };

    /* type aliases */

    using Key = std::tuple< ReactionID, resonances::ChannelQuantumNumbers,
                            std::optional< std::size_t > >;

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
     *  @param reaction   the reaction
     *  @param numbers    the channel quantum numbers
     */
    static std::size_t getIndex( const ReactionID& reaction,
                                 const resonances::ChannelQuantumNumbers& numbers,
                                 const std::optional< std::size_t >& partial ) {

      auto key = std::make_tuple( reaction, numbers, partial );
      auto iter = tuple_conversion_dictionary.find( key );
      if ( iter != tuple_conversion_dictionary.end() ) {

        return iter->second;
      }
      else {

        // index of the new entry
        auto index = entries.size();

        // create entry and set up lookup
        entries.emplace_back( reaction, numbers, partial );
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

        std::string id = string;
        std::optional< std::size_t > partial = std::nullopt;

        // check for a partial
        if ( string.back() == ']' ) {

          auto pos = id.rfind( '[' );
          if ( pos != std::string::npos ) {

            std::string temp = id.substr( pos );
            id.erase( pos );

            try {

              partial = std::stoi( temp.substr( 1, temp.size() - 1 ) );
            }
            catch ( ... ) {

              // if you get to this point, this is not a channel id string
              throw std::invalid_argument( "\'" + string + "\' does not define a "
                                           "channel identifier string" );
            }
          }
          else {

            // if you get to this point, this is not a channel id string
            throw std::invalid_argument( "\'" + string + "\' does not define a "
                                         "channel identifier string" );
          }
        }

        // get the quantum numbers
        auto pos = id.rfind( '{' );
        if ( pos != std::string::npos ) {

          try {

            // channel numbers and reaction id
            resonances::ChannelQuantumNumbers numbers( id.substr( pos ) );
            id.erase( pos );
            ReactionID reaction( id );

            // index of the new entry
            auto index = entries.size();

            // create entry and set up lookup
            auto key = std::make_tuple( reaction, numbers, partial );
            entries.emplace_back( reaction, numbers, partial );
            tuple_conversion_dictionary[ key ] = index;
            for ( const auto& symbol : entries.back().symbols() ) {

              string_conversion_dictionary[ symbol ] = index;
            }

            return index;
          }
          catch ( ... ) {

            // if you get to this point, this is not a channel id string
            throw std::invalid_argument( "\'" + string + "\' does not define a "
                                         "channel identifier string" );
          }
        }

        // if you get to this point, this is not a channel id string
        throw std::invalid_argument( "\'" + string + "\' does not define a "
                                     "channel identifier string" );
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor taking an index
     */
    constexpr ChannelID( std::size_t index ) : index_( index ) {};

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ChannelID() = default;

    ChannelID( const ChannelID& ) = default;
    ChannelID( ChannelID&& ) = default;

    ChannelID& operator=( const ChannelID& ) = default;
    ChannelID& operator=( ChannelID&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param reaction   the reaction
     *  @param numbers    the channel quantum numbers
     *  @param partial    the optional partial index
     */
    ChannelID( const ReactionID& reaction,
               const resonances::ChannelQuantumNumbers& numbers,
               const std::optional< std::size_t >& partial = std::nullopt ) :
      index_( getIndex( reaction, numbers, partial ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param string   the channel symbol
     */
    ChannelID( const std::string& symbol ) :
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
     *  @brief Return the reaction
     */
    const ReactionID& reaction() const {

      return entries[ this->index_ ].reaction();
    }

    /**
     *  @brief Return the quantum numbers
     */
    const resonances::ChannelQuantumNumbers& quantumNumbers() const {

      return entries[ this->index_ ].numbers();
    }

    /**
     *  @brief Return the partial number (if defined)
     */
    const std::optional< std::size_t >& partial() const {

      return entries[ this->index_ ].partial();
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
    friend auto operator==( const ChannelID& left, const ChannelID& right ) {

      return std::tie( left.quantumNumbers(), left.reaction(), left.partial() ) ==
             std::tie( right.quantumNumbers(), right.reaction(), right.partial() );
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator!=( const ChannelID& left, const ChannelID& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<( const ChannelID& left, const ChannelID& right ) {

      auto leftQNum = left.quantumNumbers();
      auto rightQNum = right.quantumNumbers();

      // Test order:
      // J, parity, reationID, l, s, partial
      if ( leftQNum.totalAngularMomentum() < rightQNum.totalAngularMomentum() ) {

        return true;
      }
      else if ( leftQNum.totalAngularMomentum() > rightQNum.totalAngularMomentum() ) {

        return false;
      }

      if ( leftQNum.parity() < rightQNum.parity() ) {

        return true;
      }
      else if ( leftQNum.parity() > rightQNum.parity() ) {

        return false;
      }

      if ( left.reaction() < right.reaction() ) {

        return true;
      }
      else if ( left.reaction() > right.reaction() ) {

        return false;
      }

      if ( left.quantumNumbers() < right.quantumNumbers() ) {

        return true;
      }
      else if ( left.quantumNumbers() > right.quantumNumbers() ) {

        return false;
      }

      if ( left.partial() < right.partial() ) {

        return true;
      }

      return false;
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>( const ChannelID& left, const ChannelID& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<=( const ChannelID& left, const ChannelID& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>=( const ChannelID& left, const ChannelID& right ) {

      return ! ( left < right );
    }
  };

} // id namespace
} // dryad namespace
} // njoy namespace

namespace std {

  // std::hash override for the ChannelID class
  template <>
  struct hash< njoy::dryad::id::ChannelID > {

    std::size_t operator()( const njoy::dryad::id::ChannelID& key ) const {

      return key.hash();
    }
  };

} // namespace std

#endif
