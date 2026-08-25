#ifndef NJOY_DRYAD_ID_ELECTRONSUBSHELLID
#define NJOY_DRYAD_ID_ELECTRONSUBSHELLID

// system includes
#include <array>
#include <cmath>
#include <optional>
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
   */
  class ElectronSubshellID {

  public:

    // the numbers representing the relativistic subshell
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

    /**
     *  @class
     *  @brief Private helper class
     */
    class Entry {

      /* fields */

      // tuple for logical ordering:
      // - principal quantum number
      // - azimuthal quantum number
      // - total angular momentum = l +/- 1/2
      std::tuple< short, short, std::optional< double > > numbers_;

      std::optional< short > mt_;
      std::string symbol_;
      std::vector< std::string > alternatives_;

      std::size_t hash_;

    public:

      /* constructor */
      Entry( short n, short l, double j, short mt,
             std::string symbol,
             std::vector< std::string > alternatives = {} ) :
          numbers_( n, l, j ), mt_( mt ),
          symbol_( std::move( symbol ) ),
          alternatives_( std::move( alternatives ) ) {

        this->hash_ = std::hash< std::string >{}( this->symbol() );
      }

      Entry( short n, short l, std::string symbol ) :
          numbers_( n, l, std::nullopt ), mt_( std::nullopt ),
          symbol_( std::move( symbol ) ) {

        this->hash_ = std::hash< std::string >{}( this->symbol() );
      }

      /* methods */
      const std::tuple< short, short, std::optional< double > >& quantumNumbers() const { return this->numbers_; }
      short principalQuantumNumber() const { return std::get<0>( this->quantumNumbers() ); }
      short azimuthalQuantumNumber() const { return std::get<1>( this->quantumNumbers() ); }
      const std::optional< double >& totalAngularMomentum() const { return std::get<2>( this->quantumNumbers() ); }

      const std::optional< short >& mt() const { return this->mt_; }
      const std::string& symbol() const { return this->symbol_; }
      const std::vector< std::string >& alternatives() const { return this->alternatives_; }

      std::size_t hash() const { return this->hash_; }
    };

    /* static fields */

    static inline const std::vector< Entry > entries{

      Entry{ 1, 0, 0.5,  K , "1s1/2" , { "1s", "1s+", "K" } },
      Entry{ 2, 0, 0.5,  L1, "2s1/2" , { "2s", "2s+", "L1" } },
      Entry{ 2, 1          , "2p" },
      Entry{ 2, 1, 0.5,  L2, "2p1/2" , { "2p-", "L2" } },
      Entry{ 2, 1, 1.5,  L3, "2p3/2" , { "2p+", "L3" } },
      Entry{ 3, 0, 0.5,  M1, "3s1/2" , { "3s", "3s+", "M1" } },
      Entry{ 3, 1          , "3p" },
      Entry{ 3, 1, 0.5,  M2, "3p1/2" , { "3p-", "M2" } },
      Entry{ 3, 1, 1.5,  M3, "3p3/2" , { "3p+", "M3" } },
      Entry{ 3, 2          , "3d" },
      Entry{ 3, 2, 1.5,  M4, "3d3/2" , { "3d-", "M4" } },
      Entry{ 3, 2, 2.5,  M5, "3d5/2" , { "3d+", "M5" } },
      Entry{ 4, 0, 0.5,  N1, "4s1/2" , { "4s", "4s+", "N1" } },
      Entry{ 4, 1          , "4p" },
      Entry{ 4, 1, 0.5,  N2, "4p1/2" , { "4p-", "N2" } },
      Entry{ 4, 1, 1.5,  N3, "4p3/2" , { "4p+", "N3" } },
      Entry{ 4, 2          , "4d" },
      Entry{ 4, 2, 1.5,  N4, "4d3/2" , { "4d-", "N4" } },
      Entry{ 4, 2, 2.5,  N5, "4d5/2" , { "4d+", "N5" } },
      Entry{ 4, 3          , "4f" },
      Entry{ 4, 3, 2.5,  N6, "4f5/2" , { "4f-", "N6" } },
      Entry{ 4, 3, 3.5,  N7, "4f7/2" , { "4f+", "N7" } },
      Entry{ 5, 0, 0.5,  O1, "5s1/2" , { "5s", "5s+", "O1" } },
      Entry{ 5, 1          , "5p" },
      Entry{ 5, 1, 0.5,  O2, "5p1/2" , { "5p-", "O2" } },
      Entry{ 5, 1, 1.5,  O3, "5p3/2" , { "5p+", "O3" } },
      Entry{ 5, 2          , "5d" },
      Entry{ 5, 2, 1.5,  O4, "5d3/2" , { "5d-", "O4" } },
      Entry{ 5, 2, 2.5,  O5, "5d5/2" , { "5d+", "O5" } },
      Entry{ 5, 3          , "5f" },
      Entry{ 5, 3, 2.5,  O6, "5f5/2" , { "5f-", "O6" } },
      Entry{ 5, 3, 3.5,  O7, "5f7/2" , { "5f+", "O7" } },
      Entry{ 5, 4          , "5g" },
      Entry{ 5, 4, 3.5,  O8, "5g7/2" , { "5g-", "O8" } },
      Entry{ 5, 4, 4.5,  O9, "5g9/2" , { "5g+", "O9" } },
      Entry{ 6, 0, 0.5,  P1, "6s1/2" , { "6s", "6s+", "P1" } },
      Entry{ 6, 1          , "6p" },
      Entry{ 6, 1, 0.5,  P2, "6p1/2" , { "6p-", "P2" } },
      Entry{ 6, 1, 1.5,  P3, "6p3/2" , { "6p+", "P3" } },
      Entry{ 6, 2          , "6d" },
      Entry{ 6, 2, 1.5,  P4, "6d3/2" , { "6d-", "P4" } },
      Entry{ 6, 2, 2.5,  P5, "6d5/2" , { "6d+", "P5" } },
      Entry{ 6, 3          , "6f" },
      Entry{ 6, 3, 2.5,  P6, "6f5/2" , { "6f-", "P6" } },
      Entry{ 6, 3, 3.5,  P7, "6f7/2" , { "6f+", "P7" } },
      Entry{ 6, 4          , "6g" },
      Entry{ 6, 4, 3.5,  P8, "6g7/2" , { "6g-", "P8" } },
      Entry{ 6, 4, 4.5,  P9, "6g9/2" , { "6g+", "P9" } },
      Entry{ 6, 5          , "6h" },
      Entry{ 6, 5, 4.5, P10, "6h9/2" , { "6h-", "P10" } },
      Entry{ 6, 5, 5.5, P11, "6h11/2", { "6h+", "P11" } },
      Entry{ 7, 0, 0.5,  Q1, "7s1/2" , { "7s", "7s+", "Q1" } },
      Entry{ 7, 1          , "7p" },
      Entry{ 7, 1, 0.5,  Q2, "7p1/2" , { "7p-", "Q2" } },
      Entry{ 7, 1, 1.5,  Q3, "7p3/2" , { "7p+", "Q3" } },
      Entry{ 7, 2          , "7d" },
      Entry{ 7, 2, 1.5,  Q4, "7d3/2" , { "7d-", "Q4" } },
      Entry{ 7, 2, 2.5,  Q5, "7d5/2" , { "7d+", "Q5" } },
      Entry{ 7, 3          , "7f" },
      Entry{ 7, 3, 2.5,  Q6, "7f5/2" , { "7f-", "Q6" } },
      Entry{ 7, 3, 3.5,  Q7, "7f7/2" , { "7f+", "Q7" } },
      Entry{ 7, 4          , "7g" },
      Entry{ 7, 4, 3.5,  Q8, "7g7/2" , { "7g-", "Q8" } },
      Entry{ 7, 4, 4.5,  Q9, "7g9/2" , { "7g+", "Q9" } },
      Entry{ 7, 5          , "7h" },
      Entry{ 7, 5, 4.5, Q10, "7h9/2" , { "7h-", "Q10" } },
      Entry{ 7, 5, 5.5, Q11, "7h11/2", { "7h+", "Q11" } },
      Entry{ 7, 6          , "7i" },
      Entry{ 7, 6, 5.5, Q12, "7i11/2", { "7i-", "Q12" } },
      Entry{ 7, 6, 6.5, Q13, "7i13/2", { "7i+", "Q13" } }
    };
    static inline const std::unordered_map< std::string, std::size_t >
    string_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< std::string, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        conversion[ entries[ index ].symbol() ] = index;
        for ( const auto& alternative : entries[ index ].alternatives() ) {

          conversion[ alternative ] = index;
        }
      }
      return conversion;
    }( entries );
    static inline const std::unordered_map< int, std::size_t >
    number_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< int, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        if ( entries[ index ].mt().has_value() ) {

          conversion[ entries[ index ].mt().value() ] = index;
        }
      }
      return conversion;
    }( entries );

    /* fields */

    std::size_t index_;

    /* auxiliary functions */

    /**
     *  @brief Retrieve the index to the subshell information entry
     *
     *  @param number    the subshell number
     */
    static std::size_t getIndex( int number ) {

      try {

        return number_conversion_dictionary.at( number );
      }
      catch ( ... ) {

        throw std::invalid_argument( "Not a subshell number: \'" + std::to_string( number ) + "\'" );
      }
    }

    /**
     *  @brief Retrieve the index to the subshell information entry
     *
     *  @param string    the subshell symbol or alternatives
     */
    static std::size_t getIndex( const std::string& string ) {

      try {

        return string_conversion_dictionary.at( string );
      }
      catch ( ... ) {

        throw std::invalid_argument( "Not a subshell symbol or name: \'" + string + "\'" );
      }
    }

    /**
     *  @brief Retrieve the index to the subshell information entry
     *
     *  @param principal    the principal quantum number
     *  @param azimuthal    the azimuthal quantum number
     *  @param angular      the angular momentum (equal to azimuthal +/- 1/2)
     */
    static std::size_t getIndex( std::size_t principal, std::size_t azimuthal, double angular ) {

      auto toHalfIntegerString = [] ( const double a ) {

        double half;
        return std::modf( a, &half ) == 0. ?
                   // a is a full integer
                   std::to_string( static_cast< int >( half ) ) :
                   // a is a half integer value
                   std::to_string( 2 * static_cast< int >( half ) + 1 ) + "/2";
      };

      std::array< char, 7 > letters = { 's', 'p', 'd', 'f', 'g', 'h', 'i' };

      std::string string = std::to_string( principal );
      string += letters[azimuthal];
      string += toHalfIntegerString( angular );

      return getIndex( string );
    }

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ElectronSubshellID() = default;

    ElectronSubshellID( const ElectronSubshellID& ) = default;
    ElectronSubshellID( ElectronSubshellID&& ) = default;

    ElectronSubshellID& operator=( const ElectronSubshellID& ) = default;
    ElectronSubshellID& operator=( ElectronSubshellID&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param number   the subshell number
     */
    ElectronSubshellID( int number ) : index_( getIndex( number ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param string   the subshell identifier
     */
    ElectronSubshellID( const std::string& string ) : index_( getIndex( string ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param principal    the principal quantum number
     *  @param azimuthal    the azimuthal quantum number
     *  @param angular      the angular momentum (equal to azimuthal +/- 1/2)
     */
    ElectronSubshellID( std::size_t principal, std::size_t azimuthal, double angular ) :
        index_( getIndex( principal, azimuthal, angular ) ) {}

    /* methods */

    /**
     *  @brief Return the subshell principal quantum number
     */
    short principalQuantumNumber() const {

      return entries[ this->index_ ].principalQuantumNumber();
    }

    /**
     *  @brief Return the subshell azimuthal quantum number
     */
    short azimuthalQuantumNumber() const {

      return entries[ this->index_ ].azimuthalQuantumNumber();
    }

    /**
     *  @brief Return the subshell total angular momentum (if defined)
     */
    const std::optional< double >& totalAngularMomentum() const {

      return entries[ this->index_ ].totalAngularMomentum();
    }

    /**
     *  @brief Return whether or not the subshell identifier is relativistic
     */
    bool isRelativistic() const {

      return entries[ this->index_ ].totalAngularMomentum().has_value();
    }

    /**
     *  @brief Return whether or not the subshell identifier is non-relativistic
     */
    bool isNonRelativistic() const {

      return ! this->isRelativistic();
    }

    /**
     *  @brief Return the subshell symbol
     */
    const std::string& symbol() const {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the subshell mt number (if defined)
     */
    const std::optional< short >& mt() const {

      return entries[ this->index_ ].mt();
    }

    /**
     *  @brief Return the subshell alternative symbols
     */
    const std::vector< std::string >& alternatives() const {

      return entries[ this->index_ ].alternatives();
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
    friend auto operator==( const ElectronSubshellID& left, const ElectronSubshellID& right ) {

      return entries[ left.index_ ].quantumNumbers() == entries[ right.index_ ].quantumNumbers();
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

      return entries[ left.index_ ].quantumNumbers() < entries[ right.index_ ].quantumNumbers();
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

      return key.hash();
    }
  };

} // namespace std

#endif
