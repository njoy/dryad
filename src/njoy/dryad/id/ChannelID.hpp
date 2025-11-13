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
    #include "njoy/dryad/id/ChannelID/Entry.hpp"

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
    #include "njoy/dryad/id/ChannelID/src/getIndex.hpp"

  public:

    /* constructor */
    #include "njoy/dryad/id/ChannelID/src/ctor.hpp"

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

      return std::tie( left.quantumNumbers(), left.reaction(), left.partial() ) <
             std::tie( right.quantumNumbers(), right.reaction(), right.partial() );
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

      return std::hash< std::string >{}( key.symbol() );
    }
  };

} // namespace std

#endif
