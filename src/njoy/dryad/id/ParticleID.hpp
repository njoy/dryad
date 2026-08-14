#ifndef NJOY_DRYAD_ID_PARTICLEID
#define NJOY_DRYAD_ID_PARTICLEID

// system includes
#include <cmath>
#include <regex>
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>

// other includes
#include "tools/split.hpp"
#include "njoy/dryad/id/ElectronSubshellID.hpp"
#include "njoy/dryad/id/ElementID.hpp"
#include "njoy/dryad/id/LevelID.hpp"

namespace njoy {
namespace dryad {
namespace id {

  /**
   *  @class
   *  @brief The particle identifier, with associated symbol and aliases
   *
   *  Comparison operators are provided using the logical order given by the
   *  element number. A hash function and override for std::hash is also
   *  provided.
   *
   *  For more information on how to create instances of ParticleID, see the
   *  Jupyter notebook dryad-identifiers.ipynb under python/examples.
   */
  class ParticleID {

    /* helper class */

    /**
     *  @class
     *  @brief Private helper class
     */
    class Entry {

      /* fields */

      // tuple for logical ordering:
      // - za or order number for fundamental particles
      // - optional level number
      // - vector of vacancies
      std::tuple< int, std::optional< std::vector< ElectronSubshellID > > > tuple_;

      short z_;
      short a_;
      short e_;
      int za_;

      std::string symbol_;
      std::vector< std::string > alternatives_;

      std::size_t hash_;

    public:

      /* constructor */

      // elements
      Entry( ElementID element, std::string symbol, std::vector< std::string > alternatives ) :
          tuple_( element.number() * 1000000, std::nullopt ),
          z_( element.number() ),
          a_( 0 ),
          e_( 0 ),
          za_( element.number() * 1000 ),
          symbol_( std::move( symbol ) ),
          alternatives_( std::move( alternatives ) ) {

        this->hash_ = std::hash< std::string >{}( this->symbol() );
      }

      // ions
      Entry( ElementID element, std::vector< ElectronSubshellID > vacancies,
             std::string symbol, std::vector< std::string > alternatives ) :
          tuple_( element.number() * 1000000, std::move( vacancies ) ),
          z_( element.number() ),
          a_( 0 ),
          e_( 0 ),
          za_( element.number() * 1000 ),
          symbol_( std::move( symbol ) ),
          alternatives_( std::move( alternatives ) ) {

        this->hash_ = std::hash< std::string >{}( this->symbol() );
      }

      // nuclides
      Entry( ElementID element, short mass, LevelID level,
             std::string symbol, std::vector< std::string > alternatives ) :
          tuple_( ( element.number() * 1000 + mass ) * 1000 + level.number(), std::nullopt ),
          z_( element.number() ),
          a_( mass ),
          e_( level.number() ),
          za_( element.number() * 1000 + mass ),
          symbol_( std::move( symbol ) ),
          alternatives_( std::move( alternatives ) ) {

        this->hash_ = std::hash< std::string >{}( this->symbol() );
      }

      // fundamental particles
      Entry( int number, short z, short a,
             std::string symbol, std::vector< std::string > alternatives ) :
          tuple_( number, std::nullopt ),
          z_( z ),
          a_( a ),
          e_( 0 ),
          za_( z * 1000 + a ),
          symbol_( std::move( symbol ) ),
          alternatives_( std::move( alternatives ) ) {

        this->hash_ = std::hash< std::string >{}( this->symbol() );
      }

      /* methods */
      const std::tuple< int, std::optional< std::vector< ElectronSubshellID > > >& tuple() const { return this->tuple_; }
      short z() const { return this->z_; }
      short a() const { return this->a_; }
      short e() const { return this->e_; }
      int za() const { return this->za_; }
      const std::optional< std::vector< ElectronSubshellID > >& vacancies() const { return std::get< 1 >( this->tuple() ); }
      const std::string& symbol() const { return this->symbol_; }
      const std::vector< std::string >& alternatives() const { return this->alternatives_; }

      std::size_t hash() const { return this->hash_; }
    };

    /* static fields */

    static inline const std::regex nuclide_id_regex{ "^(([A-Z][a-z]?)(\\d{1,3}))((_e(\\d+))|(\\[all\\])|(\\[continuum\\]))?$" };
    static inline const std::regex ion_id_regex{ "^([A-Z][a-z]?)\\{(.+)\\}$" };
    static inline std::vector< Entry > entries{

      // fundamental particles
      Entry{  0,   0, 0, "g" , { "photon", "gamma", "x-ray" } },
      Entry{  1,  -1, 0, "e-", { "electron", "beta-" } },
      Entry{  2,   1, 0, "e+", { "positron", "beta+", "e-_anti" } },
      Entry{ 10,   0, 1, "n" , { "neutron" } },
      Entry{ 11,   1, 1, "p" , { "proton" } },
      Entry{ 12,   1, 2, "d" , { "deuteron" } },
      Entry{ 13,   1, 3, "t" , { "triton" } },
      Entry{ 23,   2, 3, "h" , { "helion" } },
      Entry{ 24,   2, 4, "a" , { "alpha" } },
      // elements
      Entry{   1, "H" , { "Hydrogen" } },
      Entry{   2, "He", { "Helium" } },
      Entry{   3, "Li", { "Lithium" } },
      Entry{   4, "Be", { "Beryllium" } },
      Entry{   5, "B" , { "Boron" } },
      Entry{   6, "C" , { "Carbon" } },
      Entry{   7, "N" , { "Nitrogen" } },
      Entry{   8, "O" , { "Oxygen" } },
      Entry{   9, "F" , { "Fluorine" } },
      Entry{  10, "Ne", { "Neon" } },
      Entry{  11, "Na", { "Sodium" } },
      Entry{  12, "Mg", { "Magnesium" } },
      Entry{  13, "Al", { "Aluminium", "Aluminum" } },
      Entry{  14, "Si", { "Silicon" } },
      Entry{  15, "P" , { "Phosphorus" } },
      Entry{  16, "S" , { "Sulfur" } },
      Entry{  17, "Cl", { "Chlorine" } },
      Entry{  18, "Ar", { "Argon" } },
      Entry{  19, "K" , { "Potassium" } },
      Entry{  20, "Ca", { "Calcium" } },
      Entry{  21, "Sc", { "Scandium" } },
      Entry{  22, "Ti", { "Titanium" } },
      Entry{  23, "V" , { "Vanadium" } },
      Entry{  24, "Cr", { "Chromium" } },
      Entry{  25, "Mn", { "Manganese" } },
      Entry{  26, "Fe", { "Iron" } },
      Entry{  27, "Co", { "Cobalt" } },
      Entry{  28, "Ni", { "Nickel" } },
      Entry{  29, "Cu", { "Copper" } },
      Entry{  30, "Zn", { "Zinc" } },
      Entry{  31, "Ga", { "Gallium" } },
      Entry{  32, "Ge", { "Germanium" } },
      Entry{  33, "As", { "Arsenic" } },
      Entry{  34, "Se", { "Selenium" } },
      Entry{  35, "Br", { "Bromine" } },
      Entry{  36, "Kr", { "Krypton" } },
      Entry{  37, "Rb", { "Rubidium" } },
      Entry{  38, "Sr", { "Strontium" } },
      Entry{  39, "Y" , { "Yttrium" } },
      Entry{  40, "Zr", { "Zirconium" } },
      Entry{  41, "Nb", { "Niobium" } },
      Entry{  42, "Mo", { "Molybdenum" } },
      Entry{  43, "Tc", { "Technetium" } },
      Entry{  44, "Ru", { "Ruthenium" } },
      Entry{  45, "Rh", { "Rhodium" } },
      Entry{  46, "Pd", { "Palladium" } },
      Entry{  47, "Ag", { "Silver" } },
      Entry{  48, "Cd", { "Cadmium" } },
      Entry{  49, "In", { "Indium" } },
      Entry{  50, "Sn", { "Tin" } },
      Entry{  51, "Sb", { "Antimony" } },
      Entry{  52, "Te", { "Tellurium" } },
      Entry{  53, "I" , { "Iodine" } },
      Entry{  54, "Xe", { "Xenon" } },
      Entry{  55, "Cs", { "Caesium", "Cesium" } },
      Entry{  56, "Ba", { "Barium" } },
      Entry{  57, "La", { "Lanthanum" } },
      Entry{  58, "Ce", { "Cerium" } },
      Entry{  59, "Pr", { "Praseodymium" } },
      Entry{  60, "Nd", { "Neodymium" } },
      Entry{  61, "Pm", { "Promethium" } },
      Entry{  62, "Sm", { "Samarium" } },
      Entry{  63, "Eu", { "Europium" } },
      Entry{  64, "Gd", { "Gadolinium" } },
      Entry{  65, "Tb", { "Terbium" } },
      Entry{  66, "Dy", { "Dysprosium" } },
      Entry{  67, "Ho", { "Holmium" } },
      Entry{  68, "Er", { "Erbium" } },
      Entry{  69, "Tm", { "Thulium" } },
      Entry{  70, "Yb", { "Ytterbium" } },
      Entry{  71, "Lu", { "Lutetium" } },
      Entry{  72, "Hf", { "Hafnium" } },
      Entry{  73, "Ta", { "Tantalum" } },
      Entry{  74, "W" , { "Tungsten" } },
      Entry{  75, "Re", { "Rhenium" } },
      Entry{  76, "Os", { "Osmium" } },
      Entry{  77, "Ir", { "Iridium" } },
      Entry{  78, "Pt", { "Platinum" } },
      Entry{  79, "Au", { "Gold" } },
      Entry{  80, "Hg", { "Mercury" } },
      Entry{  81, "Tl", { "Thallium" } },
      Entry{  82, "Pb", { "Lead" } },
      Entry{  83, "Bi", { "Bismuth" } },
      Entry{  84, "Po", { "Polonium" } },
      Entry{  85, "At", { "Astatine" } },
      Entry{  86, "Rn", { "Radon" } },
      Entry{  87, "Fr", { "Francium" } },
      Entry{  88, "Ra", { "Radium" } },
      Entry{  89, "Ac", { "Actinium" } },
      Entry{  90, "Th", { "Thorium" } },
      Entry{  91, "Pa", { "Protactinium" } },
      Entry{  92, "U" , { "Uranium" } },
      Entry{  93, "Np", { "Neptunium" } },
      Entry{  94, "Pu", { "Plutonium" } },
      Entry{  95, "Am", { "Americium" } },
      Entry{  96, "Cm", { "Curium" } },
      Entry{  97, "Bk", { "Berkelium" } },
      Entry{  98, "Cf", { "Californium" } },
      Entry{  99, "Es", { "Einsteinium" } },
      Entry{ 100, "Fm", { "Fermium" } },
      Entry{ 101, "Md", { "Mendelevium" } },
      Entry{ 102, "No", { "Nobelium" } },
      Entry{ 103, "Lr", { "Lawrencium" } },
      Entry{ 104, "Rf", { "Rutherfordium"} },
      Entry{ 105, "Db", { "Dubnium" } },
      Entry{ 106, "Sg", { "Seaborgium" } },
      Entry{ 107, "Bh", { "Bohrium" } },
      Entry{ 108, "Hs", { "Hassium" } },
      Entry{ 109, "Mt", { "Meitnerium" } },
      Entry{ 110, "Ds", { "Darmstadtium" } },
      Entry{ 111, "Rg", { "Roentgenium" } },
      Entry{ 112, "Cn", { "Copernicium" } },
      Entry{ 113, "Nh", { "Nihonium" } },
      Entry{ 114, "Fl", { "Flerovium" } },
      Entry{ 115, "Mc", { "Moscovium" } },
      Entry{ 116, "Lv", { "Livermorium" } },
      Entry{ 117, "Ts", { "Tennessine" } },
      Entry{ 118, "Og", { "Oganesson" } }
    };
    static inline std::unordered_map< std::string, std::size_t >
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
    static inline std::unordered_map< int, std::size_t >
    number_conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< int, std::size_t > conversion;
      // do not include the fundamental particles
      for ( std::size_t index = 9; index < entries.size(); ++index ) {

        auto number = ( entries[ index ].z() * 1000 + entries[ index ].a() ) * 1000 + entries[ index ].e();
        conversion[ number ] = index;
      }
      return conversion;
    }( entries );

    /* fields */

    std::size_t index_;

    /* auxiliary functions */

    /**
     *  @brief Generate the symbol for an atom with subshell vacancies
     *
     *  @param element     the particle element
     *  @param vacancies   the subshells with vacancies
     */
    static std::string
    generateIonSymbol( const ElementID element, const std::vector< ElectronSubshellID >& vacancies ) {

      std::string symbol = element.symbol() + '{';
      for ( unsigned int i =0; i < vacancies.size(); ++i ) {

        if ( vacancies[i].isNonRelativistic() ) {

          throw std::invalid_argument( "Electron subshell identifiers used for particle identifiers must be relativistic" );
        }

        if ( i != 0 ) {

          symbol += ',';
        }
        symbol += vacancies[i].symbol();
      }
      symbol += '}';
      return symbol;
    }

    /**
     *  @brief Generate the alternative symbols for an atom with subshell vacancies
     *
     *  @param element     the particle element
     *  @param vacancies   the subshells with vacancies
     */
    static std::vector< std::string >
    generateIonAlternatives( const std::string& symbol, const ElementID element, const std::vector< ElectronSubshellID >& vacancies ) {

      //! @todo use a proper cartesian product in the future, for now: only do this for size() < 3

      std::vector< std::string > alternatives;
      std::string prefix = element.symbol() +'{';

      if ( vacancies.size() > 2 ) {

        throw std::runtime_error( "Atoms can currently only have 2 or less vacancies, contact a developer" );
      }

      alternatives.emplace_back( vacancies.front().symbol() );
      alternatives.insert( alternatives.end(), vacancies.front().alternatives().begin(), vacancies.front().alternatives().end() );

      std::vector< std::string > temp;
      for ( unsigned int i = 1; i < vacancies.size(); ++i ) {

        for ( unsigned int j = 0; j < alternatives.size(); ++j ) {

          temp.emplace_back( alternatives[j] + ',' + vacancies[i].symbol() );
          for ( unsigned int k = 0; k < vacancies[i].alternatives().size(); ++k ) {

            temp.emplace_back( alternatives[j] + ',' + vacancies[i].alternatives()[k] );
          }
        }
        std::swap( alternatives, temp );
        temp.clear();
      }

      for ( unsigned int i = 0; i < alternatives.size(); ++i ) {

        alternatives[i].insert( 0, prefix );
        alternatives[i] += '}';
      }

      auto iter = std::find( alternatives.begin(), alternatives.end(), symbol );
      if ( iter != alternatives.end() ) {

        alternatives.erase( iter );
      }

      return alternatives;
    }

    /**
     *  @brief Update registry
     *
     *  @param element   the particle element
     *  @param mass      the particle mass number
     *  @param level     the particle level
     */
    static std::size_t updateRegistry( ElementID element, int mass, LevelID level ) {

      // the index for the new identifier
      std::size_t index = entries.size();

      int number = element.number() * 1000000 + mass * 1000 + level.number();
      std::vector< std::string > alternatives = {};
      std::string symbol = element.symbol() + std::to_string( mass );
      if ( level.number() != 0 ) {

        if ( ( level.number() == LevelID::continuum ) || ( level.number() == LevelID::all ) ) {

          alternatives.emplace_back( symbol + std::string( "_e" ) +
                                     std::to_string( level.number() ) );
        }
        symbol += level.symbol();
      }
      else {

        alternatives.emplace_back( symbol + std::string( "_e0" ) );
      }

      // create the data entry and set conversion
      entries.emplace_back( element, mass, level,
                            std::move( symbol ), std::move( alternatives ) );

      number_conversion_dictionary[ number ] = index;
      string_conversion_dictionary[ entries[ index ].symbol() ] = index;
      for ( const auto& alternative : entries[ index ].alternatives() ) {

        string_conversion_dictionary[ alternative ] = index;
      }

      // return the index
      return index;
    }

    /**
     *  @brief Update registry
     *
     *  @param element     the particle element
     *  @param vacancies   the subshells with vacancies
     */
    static std::size_t updateRegistry( ElementID element,
                                       std::vector< ElectronSubshellID > vacancies ) {

      // the index for the new identifier
      std::size_t index = entries.size();

      std::string symbol = generateIonSymbol( element, vacancies );
      std::vector< std::string > alternatives = generateIonAlternatives( symbol, element, vacancies );

      // create the data entry and set conversion
      entries.emplace_back( element, std::move( vacancies ),
                            std::move( symbol ),
                            std::move( alternatives ) );

      string_conversion_dictionary[ entries[ index ].symbol() ] = index;
      for ( const auto& alternative : entries[ index ].alternatives() ) {

        string_conversion_dictionary[ alternative ] = index;
      }

      // return the index
      return index;
    }

    /**
     *  @brief Retrieve the index to the particle information entry
     *
     *  @param element   the particle element
     *  @param mass      the particle mass number
     *  @param level     the particle level
     */
    static std::size_t getIndex( ElementID element, int mass, LevelID level ) {

      try {

        return number_conversion_dictionary.at( ( element.number() * 1000 + mass ) * 1000 + level.number() );
      }
      catch ( ... ) {

        // update registry and return the index
        return updateRegistry( std::move( element ), std::move( mass ), std::move( level ) );
      }
    }

    /**
     *  @brief Retrieve the index to the particle information entry
     *
     *  @param element     the particle element
     *  @param vacancies   the subshells with vacancies
     */
    static std::size_t getIndex( ElementID element, std::vector< ElectronSubshellID > vacancies ) {

      try {

        return string_conversion_dictionary.at( generateIonSymbol( element, vacancies ) );
      }
      catch ( const std::out_of_range& ) {

        // update registry and return the index
        return updateRegistry( std::move( element ), std::move( vacancies ) );
      }
    }

    /**
     *  @brief Retrieve the index to the particle information entry
     *
     *  @param string    the particle id as a string
     */
    static std::size_t getIndex( const std::string& string ) {

      try {

        return string_conversion_dictionary.at( string );
      }
      catch ( ... ) {

        std::smatch match;
        if ( std::regex_match( string, match, nuclide_id_regex ) ) {

          // data entries
          ElementID element( match[2] );
          int mass = std::stoi( match[3] );
          LevelID level( match[4] != ""
                         ? match[5] != "" ? std::stoi( match[6] )
                                          : match[7] != "" ? LevelID::all
                                                           : LevelID::continuum
                         : 0 );

          // update registry and return the index
          return updateRegistry( std::move( element ), std::move( mass ), std::move( level ) );
        }
        else if ( std::regex_match( string, match, ion_id_regex ) ) {

          // data entries
          ElementID element( match[1] );
          auto shells = tools::split( match[2], ',' );
          std::vector< ElectronSubshellID > vacancies( shells.size() );
          std::transform( shells.begin(), shells.end(), vacancies.begin(),
                          [] ( auto&& vacancy ) { return ElectronSubshellID( vacancy ); } );

          // update registry and return the index
          return updateRegistry( std::move( element ), std::move( vacancies ) );
        }

        throw std::invalid_argument( "Not a particle symbol or name: \'" + string + "\'" );
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor taking an index
     */
    constexpr ParticleID( std::size_t index ) : index_( index ) {};

  public:

    /* constructor */

    /**
     *  @brief Default constructor (for pybind11 purposes only)
     */
    ParticleID() = default;

    ParticleID( const ParticleID& ) = default;
    ParticleID( ParticleID&& ) = default;

    ParticleID& operator=( const ParticleID& ) = default;
    ParticleID& operator=( ParticleID&& ) = default;

    /**
     *  @brief Constructor
     *
     *  @param element   the particle element
     *  @param mass      the particle mass number
     *  @param level     the particle level
     */
    ParticleID( ElementID element, int mass, LevelID level ) :
        index_( getIndex( std::move( element ), mass, std::move( level ) ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param element     the particle element
     *  @param vacancies   the subshells with a vacancy
     */
    ParticleID( ElementID element, std::vector< ElectronSubshellID > vacancies ) :
        index_( getIndex( std::move( element ), std::move( vacancies ) ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param element   the particle element
     *  @param vacancy   the subshell with a vacancy
     */
    ParticleID( ElementID element, ElectronSubshellID vacancy ) :
        ParticleID( std::move( element ), std::vector< ElectronSubshellID >{ std::move( vacancy ) } ) {}

    /**
     *  @brief Constructor
     *
     *  @param string   the particle symbol, name or alternative
     */
    ParticleID( const std::string& string ) : index_( getIndex( string ) ) {}

    /* static methods for testing purposes only */

    /**
     *  @brief Return the number of currently registered identifiers
     */
    static std::size_t size() {

      return entries.size();
    }

    /**
     *  @brief Return whether or not the the numbers correspond to a registered identifier
     *
     *  @param[in] za       the particle za number
     *  @param[in] number   the particle level or subshell number (default is zero)
     */
    static bool isRegistered( int za, int number = 0 ) {

      return number_conversion_dictionary.find( za * 1000 + number ) != number_conversion_dictionary.end();
    }

    /**
     *  @brief Return whether or not the string correspond to a registered identifier
     *
     *  @param[in] string   the string
     */
    static bool isRegistered( const std::string& string ) {

      return string_conversion_dictionary.find( string ) != string_conversion_dictionary.end();
    }

    /* predefined identifiers and static functions to create identifiers */

    static constexpr ParticleID photon() { return ParticleID{ static_cast< std::size_t >( 0 ) }; };
    static constexpr ParticleID electron() { return ParticleID{ static_cast< std::size_t >( 1 ) }; };
    static constexpr ParticleID positron() { return ParticleID{ static_cast< std::size_t >( 2 ) }; };
    static constexpr ParticleID neutron() { return ParticleID{ static_cast< std::size_t >( 3 ) }; };
    static constexpr ParticleID proton() { return ParticleID{ static_cast< std::size_t >( 4 ) }; };
    static constexpr ParticleID deuteron() { return ParticleID{ static_cast< std::size_t >( 5 ) }; };
    static constexpr ParticleID triton() { return ParticleID{ static_cast< std::size_t >( 6 ) }; };
    static constexpr ParticleID helion() { return ParticleID{ static_cast< std::size_t >( 7 ) }; };
    static constexpr ParticleID alpha() { return ParticleID{ static_cast< std::size_t >( 8 ) }; };

    /**
     *  @brief Create a particle identifier for a nuclide
     *
     *  @param[in] za      the za number of the nuclide
     *  @param[in] level   the level number of the nuclide
     */
    static ParticleID nuclide( int za, int level = 0 ) {

      try {

        return ParticleID( number_conversion_dictionary.at( za * 1000 + level ) );
      }
      catch ( ... ) {

        return ParticleID( updateRegistry( ElementID( std::round( za / 1000. ) ), za % 1000, LevelID( level ) ) );
      }
    }

    /* methods */

    /**
     *  @brief Return the particle's element number
     */
    short z() const {

      return entries[ this->index_ ].z();
    }

    /**
     *  @brief Return the particle's mass number
     */
    short a() const {

      return entries[ this->index_ ].a();
    }

    /**
     *  @brief Return the particle's level number
     */
    short e() const {

      return entries[ this->index_ ].e();
    }

    /**
     *  @brief Return the particle's za number
     */
    int za() const {

      return entries[ this->index_ ].za();
    }

    /**
     *  @brief Return the particle symbol
     */
    const std::string& symbol() const {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the identifier for the particle's ground state
     */
    ParticleID groundState() const {

      if ( entries[ this->index_ ].vacancies().has_value() ) {

        return ParticleID( this->index_ );
      }
      else {

        if ( std::get< 0 >( entries[ this->index_ ].tuple() ) > 24 ) {

          return ParticleID::nuclide( this->za(), 0 );
        }
        else {

          return ParticleID( this->index_ );
        }
      }
    }

    /**
     *  @brief Return the hash
     */
    std::size_t hash() const {

      return entries[ this->index_ ].hash();
    }

    /**
     *  @brief Return the particle's subshell vacancies
     */
    const std::optional< std::vector< ElectronSubshellID > >& vacancies() const {

      return entries[ this->index_ ].vacancies();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator==( const ParticleID& left, const ParticleID& right ) {

      return entries[ left.index_ ].tuple() == entries[ right.index_ ].tuple();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator!=( const ParticleID& left, const ParticleID& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<( const ParticleID& left, const ParticleID& right ) {

      return entries[ left.index_ ].tuple() < entries[ right.index_ ].tuple();
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>( const ParticleID& left, const ParticleID& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<=( const ParticleID& left, const ParticleID& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>=( const ParticleID& left, const ParticleID& right ) {

      return ! ( left < right );
    }
  };

} // id namespace
} // dryad namespace
} // njoy namespace

namespace std {

  // std::hash override for the ParticleID class
  template <>
  struct hash< njoy::dryad::id::ParticleID > {

    size_t operator()( const njoy::dryad::id::ParticleID& key ) const {

      return key.hash();
    }
  };

} // namespace std

#endif
