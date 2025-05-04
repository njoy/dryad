#ifndef NJOY_DRYAD_ID_ELECTRONSUBSHELLID
#define NJOY_DRYAD_ID_ELECTRONSUBSHELLID

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
   *  @brief The electron subshell identifier, with associated symbol and aliases
   *
   *  Comparison operators are provided using the logical order given by the
   *  ENDF mt numbers. A hash function and override for std::hash is also
   *  provided.
   */
  class ElectronSubshellID {

    /* helper class */
    #include "dryad/id/ElectronSubshellID/Entry.hpp"

    /* static fields */
    static inline const std::vector< Entry > entries{

      Entry{ 534, "1s1/2", "K" },
      Entry{ 535, "2s1/2", "L1" },
      Entry{ 536, "2p1/2", "L2" },
      Entry{ 537, "2p3/2", "L3" },
      Entry{ 538, "3s1/2", "M1" },
      Entry{ 539, "3p1/2", "M2" },
      Entry{ 540, "3p3/2", "M3" },
      Entry{ 541, "3d3/2", "M4" },
      Entry{ 542, "3d5/2", "M5" },
      Entry{ 543, "4s1/2", "N1" },
      Entry{ 544, "4p1/2", "N2" },
      Entry{ 545, "4p3/2", "N3" },
      Entry{ 546, "4d3/2", "N4" },
      Entry{ 547, "4d5/2", "N5" },
      Entry{ 548, "4f5/2", "N6" },
      Entry{ 549, "4f7/2", "N7" },
      Entry{ 550, "5s1/2", "O1" },
      Entry{ 551, "5p1/2", "O2" },
      Entry{ 552, "5p3/2", "O3" },
      Entry{ 553, "5d3/2", "O4" },
      Entry{ 554, "5d5/2", "O5" },
      Entry{ 555, "5f5/2", "O6" },
      Entry{ 556, "5f7/2", "O7" },
      Entry{ 557, "5g7/2", "O8" },
      Entry{ 558, "5g9/2", "O9" },
      Entry{ 559, "6s1/2", "P1" },
      Entry{ 560, "6p1/2", "P2" },
      Entry{ 561, "6p3/2", "P3" },
      Entry{ 562, "6d3/2", "P4" },
      Entry{ 563, "6d5/2", "P5" },
      Entry{ 564, "6f5/2", "P6" },
      Entry{ 565, "6f7/2", "P7" },
      Entry{ 566, "6g7/2", "P8" },
      Entry{ 567, "6g9/2", "P9" },
      Entry{ 568, "6h9/2", "P10" },
      Entry{ 569, "6h11/2", "P11" },
      Entry{ 570, "7s1/2", "Q1" },
      Entry{ 571, "7p1/2", "Q2" },
      Entry{ 572, "7p3/2", "Q3" },
      Entry{ 573, "7d3/2", "Q4" },
      Entry{ 574, "7d5/2", "Q5" },
      Entry{ 575, "7f5/2", "Q6" },
      Entry{ 576, "7f7/2", "Q7" },
      Entry{ 577, "7g7/2", "Q8" },
      Entry{ 578, "7g9/2", "Q9" },
      Entry{ 579, "7h9/2", "Q10" },
      Entry{ 580, "7h11/2", "Q11" }
    };
    static inline const std::unordered_map< std::string, std::size_t >
    string_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< std::string, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        conversion[ entries[ index ].symbol() ] = index;
        conversion[ entries[ index ].name() ] = index;
      }
      return conversion;
    }( entries );
    static inline const std::unordered_map< int, std::size_t >
    number_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< int, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        conversion[ entries[ index ].number() ] = index;
      }
      return conversion;
    }( entries );

    /* fields */
    std::size_t index_;

    /* auxiliary functions */
    #include "dryad/id/ElectronSubshellID/src/getIndex.hpp"

  public:

    /* constructor */
    #include "dryad/id/ElectronSubshellID/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the subshell number
     */
    short number() const noexcept {

      return entries[ this->index_ ].number();
    }

    /**
     *  @brief Return the subshell symbol
     */
    const std::string& symbol() const noexcept {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the subshell name
     */
    const std::string& name() const noexcept {

      return entries[ this->index_ ].name();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator==( const ElectronSubshellID& left, const ElectronSubshellID& right ) {

      return left.number() == right.number();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator!=( const ElectronSubshellID& left, const ElectronSubshellID& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<( const ElectronSubshellID& left, const ElectronSubshellID& right ) {

      return left.number() < right.number();
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>( const ElectronSubshellID& left, const ElectronSubshellID& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<=( const ElectronSubshellID& left, const ElectronSubshellID& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>=( const ElectronSubshellID& left, const ElectronSubshellID& right ) {

      return ! ( left < right );
    }
  };

} // id namespace
} // dryad namespace
} // njoy namespace

namespace std {

  // std::hash override for the ElectronSubshellID class
  template <>
  struct hash< njoy::dryad::id::ElectronSubshellID > {

    size_t operator()( const njoy::dryad::id::ElectronSubshellID& key ) const {

      return key.number();
    }
  };

} // namespace std

#endif
