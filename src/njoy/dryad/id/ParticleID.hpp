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
    #include "njoy/dryad/id/ParticleID/Entry.hpp"

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
    number_conversion_dictionary;

    /* fields */
    std::size_t index_;

    /* auxiliary functions */
    #include "njoy/dryad/id/ParticleID/src/getIndex.hpp"

  public:

    /* constructor */
    #include "njoy/dryad/id/ParticleID/src/ctor.hpp"

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
     *  @param za       the particle za number
     *  @param number   the particle level or subshell number (default is zero)
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

      if ( entries[ this->index_ ].subshell().has_value() ) {

        return ParticleID( this->index_ );
      }
      else {

        return ParticleID::nuclide( this->za(), 0 );
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
    const std::optional< std::vector< ElectronSubshellID > >& subshell() const {

      return entries[ this->index_ ].subshell();
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
