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

  public:

    // the numbers representing the subshell
    static constexpr short K   = 534;
    static constexpr short L1  = 535;
    static constexpr short L2  = 536;
    static constexpr short L3  = 537;
    static constexpr short M1  = 538;
    static constexpr short M2  = 539;
    static constexpr short M3  = 540;
    static constexpr short M4  = 541;
    static constexpr short M5  = 542;
    static constexpr short N1  = 543;
    static constexpr short N2  = 544;
    static constexpr short N3  = 545;
    static constexpr short N4  = 546;
    static constexpr short N5  = 547;
    static constexpr short N6  = 548;
    static constexpr short N7  = 549;
    static constexpr short O1  = 550;
    static constexpr short O2  = 551;
    static constexpr short O3  = 552;
    static constexpr short O4  = 553;
    static constexpr short O5  = 554;
    static constexpr short O6  = 555;
    static constexpr short O7  = 556;
    static constexpr short O8  = 557;
    static constexpr short O9  = 558;
    static constexpr short P1  = 559;
    static constexpr short P2  = 560;
    static constexpr short P3  = 561;
    static constexpr short P4  = 562;
    static constexpr short P5  = 563;
    static constexpr short P6  = 564;
    static constexpr short P7  = 565;
    static constexpr short P8  = 566;
    static constexpr short P9  = 567;
    static constexpr short P10 = 568;
    static constexpr short P11 = 569;
    static constexpr short Q1  = 570;
    static constexpr short Q2  = 571;
    static constexpr short Q3  = 572;
    static constexpr short Q4  = 573;
    static constexpr short Q5  = 574;
    static constexpr short Q6  = 575;
    static constexpr short Q7  = 576;
    static constexpr short Q8  = 577;
    static constexpr short Q9  = 578;
    static constexpr short Q10 = 579;
    static constexpr short Q11 = 580;
    static constexpr short Q12 = 581;
    static constexpr short Q13 = 582;

  private:

    /* helper class */
    #include "dryad/id/ElectronSubshellID/Entry.hpp"

    /* static fields */
    static inline const std::vector< Entry > entries{

      Entry{ K  , "1s1/2" , "K"   },
      Entry{ L1 , "2s1/2" , "L1"  },
      Entry{ L2 , "2p1/2" , "L2"  },
      Entry{ L3 , "2p3/2" , "L3"  },
      Entry{ M1 , "3s1/2" , "M1"  },
      Entry{ M2 , "3p1/2" , "M2"  },
      Entry{ M3 , "3p3/2" , "M3"  },
      Entry{ M4 , "3d3/2" , "M4"  },
      Entry{ M5 , "3d5/2" , "M5"  },
      Entry{ N1 , "4s1/2" , "N1"  },
      Entry{ N2 , "4p1/2" , "N2"  },
      Entry{ N3 , "4p3/2" , "N3"  },
      Entry{ N4 , "4d3/2" , "N4"  },
      Entry{ N5 , "4d5/2" , "N5"  },
      Entry{ N6 , "4f5/2" , "N6"  },
      Entry{ N7 , "4f7/2" , "N7"  },
      Entry{ O1 , "5s1/2" , "O1"  },
      Entry{ O2 , "5p1/2" , "O2"  },
      Entry{ O3 , "5p3/2" , "O3"  },
      Entry{ O4 , "5d3/2" , "O4"  },
      Entry{ O5 , "5d5/2" , "O5"  },
      Entry{ O6 , "5f5/2" , "O6"  },
      Entry{ O7 , "5f7/2" , "O7"  },
      Entry{ O8 , "5g7/2" , "O8"  },
      Entry{ O9 , "5g9/2" , "O9"  },
      Entry{ P1 , "6s1/2" , "P1"  },
      Entry{ P2 , "6p1/2" , "P2"  },
      Entry{ P3 , "6p3/2" , "P3"  },
      Entry{ P4 , "6d3/2" , "P4"  },
      Entry{ P5 , "6d5/2" , "P5"  },
      Entry{ P6 , "6f5/2" , "P6"  },
      Entry{ P7 , "6f7/2" , "P7"  },
      Entry{ P8 , "6g7/2" , "P8"  },
      Entry{ P9 , "6g9/2" , "P9"  },
      Entry{ P10, "6h9/2" , "P10" },
      Entry{ P11, "6h11/2", "P11" },
      Entry{ Q1 , "7s1/2" , "Q1"  },
      Entry{ Q2 , "7p1/2" , "Q2"  },
      Entry{ Q3 , "7p3/2" , "Q3"  },
      Entry{ Q4 , "7d3/2" , "Q4"  },
      Entry{ Q5 , "7d5/2" , "Q5"  },
      Entry{ Q6 , "7f5/2" , "Q6"  },
      Entry{ Q7 , "7f7/2" , "Q7"  },
      Entry{ Q8 , "7g7/2" , "Q8"  },
      Entry{ Q9 , "7g9/2" , "Q9"  },
      Entry{ Q10, "7h9/2" , "Q10" },
      Entry{ Q11, "7h11/2", "Q11" },
      Entry{ Q12, "7i11/2", "Q12" },
      Entry{ Q13, "7i13/2", "Q13" }
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
    short number() const {

      return entries[ this->index_ ].number();
    }

    /**
     *  @brief Return the subshell symbol
     */
    const std::string& symbol() const {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the subshell name
     */
    const std::string& name() const {

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
