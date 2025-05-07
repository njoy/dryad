#ifndef NJOY_DRYAD_ID_PARTICLEID
#define NJOY_DRYAD_ID_PARTICLEID

// system includes
#include <regex>
#include <string>
#include <optional>
#include <unordered_map>
#include <vector>

// other includes
#include "dryad/id/ElectronSubshellID.hpp"
#include "dryad/id/ElementID.hpp"
#include "dryad/id/LevelID.hpp"

namespace njoy {
namespace dryad {
namespace id {

  /**
   *  @class
   *  @brief The particle identifier, with associated symbol and aliases
   *
   *  The ParticleID can be used to identify the following particle types (the
   *  numbers between parentheses are the internal logic numbers assigned to them):
   *    - fundamental particles: g (0), e- (1), e+ (2), n (10), p (1001), d (1002),
   *      t (1003), h (2003), a (2004)
   *    - elements (z * 1000000)
   *    - nuclides (z * 1000000 + a * 1000 + l, with l = 0 .. 150 with 150 being
   *      defined as the continuum )
   *    - ions (z * 1000000 + s, with s = K(534) .. Q11(580) - basically the ENDF
   *      mt numbers for the subshell ionisation)
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
    #include "dryad/id/ParticleID/Entry.hpp"

    /* static fields */
    static inline const std::regex nuclide_id_regex{ "^(([A-Z][a-z]?)(\\d{1,3}))((_e(\\d+))|(\\[continuum\\]))?$" };
    static inline const std::regex ion_id_regex{ "^([A-Z][a-z]?)\\{(.+)\\}$" };
    static inline std::vector< Entry > entries{

      // fundamental particles
      Entry{         0,   0, 0, 0, "g" , { "photon", "gamma", "x-ray" } },
      Entry{         1,  -1, 0, 0, "e-", { "electron", "beta-" } },
      Entry{         2,   1, 0, 0, "e+", { "positron", "beta+", "e-_anti" } },
      Entry{        10,   0, 1, 0, "n" , { "neutron" } },
      Entry{      1001,   1, 1, 0, "p" , { "proton" } },
      Entry{      1002,   1, 2, 0, "d" , { "deuteron" } },
      Entry{      1003,   1, 3, 0, "t" , { "triton" } },
      Entry{      2003,   2, 3, 0, "h" , { "helion" } },
      Entry{      2004,   2, 4, 0, "a" , { "alpha" } },
      // elements
      Entry{   1000000,   1, 0, 0, "H" , { "Hydrogen" } },
      Entry{   2000000,   2, 0, 0, "He", { "Helium" } },
      Entry{   3000000,   3, 0, 0, "Li", { "Lithium" } },
      Entry{   4000000,   4, 0, 0, "Be", { "Beryllium" } },
      Entry{   5000000,   5, 0, 0, "B" , { "Boron" } },
      Entry{   6000000,   6, 0, 0, "C" , { "Carbon" } },
      Entry{   7000000,   7, 0, 0, "N" , { "Nitrogen" } },
      Entry{   8000000,   8, 0, 0, "O" , { "Oxygen" } },
      Entry{   9000000,   9, 0, 0, "F" , { "Fluorine" } },
      Entry{  10000000,  10, 0, 0, "Ne", { "Neon" } },
      Entry{  11000000,  11, 0, 0, "Na", { "Sodium" } },
      Entry{  12000000,  12, 0, 0, "Mg", { "Magnesium" } },
      Entry{  13000000,  13, 0, 0, "Al", { "Aluminium", "Aluminum" } },
      Entry{  14000000,  14, 0, 0, "Si", { "Silicon" } },
      Entry{  15000000,  15, 0, 0, "P" , { "Phosphorus" } },
      Entry{  16000000,  16, 0, 0, "S" , { "Sulfur" } },
      Entry{  17000000,  17, 0, 0, "Cl", { "Chlorine" } },
      Entry{  18000000,  18, 0, 0, "Ar", { "Argon" } },
      Entry{  19000000,  19, 0, 0, "K" , { "Potassium" } },
      Entry{  20000000,  20, 0, 0, "Ca", { "Calcium" } },
      Entry{  21000000,  21, 0, 0, "Sc", { "Scandium" } },
      Entry{  22000000,  22, 0, 0, "Ti", { "Titanium" } },
      Entry{  23000000,  23, 0, 0, "V" , { "Vanadium" } },
      Entry{  24000000,  24, 0, 0, "Cr", { "Chromium" } },
      Entry{  25000000,  25, 0, 0, "Mn", { "Manganese" } },
      Entry{  26000000,  26, 0, 0, "Fe", { "Iron" } },
      Entry{  27000000,  27, 0, 0, "Co", { "Cobalt" } },
      Entry{  28000000,  28, 0, 0, "Ni", { "Nickel" } },
      Entry{  29000000,  29, 0, 0, "Cu", { "Copper" } },
      Entry{  30000000,  30, 0, 0, "Zn", { "Zinc" } },
      Entry{  31000000,  31, 0, 0, "Ga", { "Gallium" } },
      Entry{  32000000,  32, 0, 0, "Ge", { "Germanium" } },
      Entry{  33000000,  33, 0, 0, "As", { "Arsenic" } },
      Entry{  34000000,  34, 0, 0, "Se", { "Selenium" } },
      Entry{  35000000,  35, 0, 0, "Br", { "Bromine" } },
      Entry{  36000000,  36, 0, 0, "Kr", { "Krypton" } },
      Entry{  37000000,  37, 0, 0, "Rb", { "Rubidium" } },
      Entry{  38000000,  38, 0, 0, "Sr", { "Strontium" } },
      Entry{  39000000,  39, 0, 0, "Y" , { "Yttrium" } },
      Entry{  40000000,  40, 0, 0, "Zr", { "Zirconium" } },
      Entry{  41000000,  41, 0, 0, "Nb", { "Niobium" } },
      Entry{  42000000,  42, 0, 0, "Mo", { "Molybdenum" } },
      Entry{  43000000,  43, 0, 0, "Tc", { "Technetium" } },
      Entry{  44000000,  44, 0, 0, "Ru", { "Ruthenium" } },
      Entry{  45000000,  45, 0, 0, "Rh", { "Rhodium" } },
      Entry{  46000000,  46, 0, 0, "Pd", { "Palladium" } },
      Entry{  47000000,  47, 0, 0, "Ag", { "Silver" } },
      Entry{  48000000,  48, 0, 0, "Cd", { "Cadmium" } },
      Entry{  49000000,  49, 0, 0, "In", { "Indium" } },
      Entry{  50000000,  50, 0, 0, "Sn", { "Tin" } },
      Entry{  51000000,  51, 0, 0, "Sb", { "Antimony" } },
      Entry{  52000000,  52, 0, 0, "Te", { "Tellurium" } },
      Entry{  53000000,  53, 0, 0, "I" , { "Iodine" } },
      Entry{  54000000,  54, 0, 0, "Xe", { "Xenon" } },
      Entry{  55000000,  55, 0, 0, "Cs", { "Caesium", "Cesium" } },
      Entry{  56000000,  56, 0, 0, "Ba", { "Barium" } },
      Entry{  57000000,  57, 0, 0, "La", { "Lanthanum" } },
      Entry{  58000000,  58, 0, 0, "Ce", { "Cerium" } },
      Entry{  59000000,  59, 0, 0, "Pr", { "Praseodymium" } },
      Entry{  60000000,  60, 0, 0, "Nd", { "Neodymium" } },
      Entry{  61000000,  61, 0, 0, "Pm", { "Promethium" } },
      Entry{  62000000,  62, 0, 0, "Sm", { "Samarium" } },
      Entry{  63000000,  63, 0, 0, "Eu", { "Europium" } },
      Entry{  64000000,  64, 0, 0, "Gd", { "Gadolinium" } },
      Entry{  65000000,  65, 0, 0, "Tb", { "Terbium" } },
      Entry{  66000000,  66, 0, 0, "Dy", { "Dysprosium" } },
      Entry{  67000000,  67, 0, 0, "Ho", { "Holmium" } },
      Entry{  68000000,  68, 0, 0, "Er", { "Erbium" } },
      Entry{  69000000,  69, 0, 0, "Tm", { "Thulium" } },
      Entry{  70000000,  70, 0, 0, "Yb", { "Ytterbium" } },
      Entry{  71000000,  71, 0, 0, "Lu", { "Lutetium" } },
      Entry{  72000000,  72, 0, 0, "Hf", { "Hafnium" } },
      Entry{  73000000,  73, 0, 0, "Ta", { "Tantalum" } },
      Entry{  74000000,  74, 0, 0, "W" , { "Tungsten" } },
      Entry{  75000000,  75, 0, 0, "Re", { "Rhenium" } },
      Entry{  76000000,  76, 0, 0, "Os", { "Osmium" } },
      Entry{  77000000,  77, 0, 0, "Ir", { "Iridium" } },
      Entry{  78000000,  78, 0, 0, "Pt", { "Platinum" } },
      Entry{  79000000,  79, 0, 0, "Au", { "Gold" } },
      Entry{  80000000,  80, 0, 0, "Hg", { "Mercury" } },
      Entry{  81000000,  81, 0, 0, "Tl", { "Thallium" } },
      Entry{  82000000,  82, 0, 0, "Pb", { "Lead" } },
      Entry{  83000000,  83, 0, 0, "Bi", { "Bismuth" } },
      Entry{  84000000,  84, 0, 0, "Po", { "Polonium" } },
      Entry{  85000000,  85, 0, 0, "At", { "Astatine" } },
      Entry{  86000000,  86, 0, 0, "Rn", { "Radon" } },
      Entry{  87000000,  87, 0, 0, "Fr", { "Francium" } },
      Entry{  88000000,  88, 0, 0, "Ra", { "Radium" } },
      Entry{  89000000,  89, 0, 0, "Ac", { "Actinium" } },
      Entry{  90000000,  90, 0, 0, "Th", { "Thorium" } },
      Entry{  91000000,  91, 0, 0, "Pa", { "Protactinium" } },
      Entry{  92000000,  92, 0, 0, "U" , { "Uranium" } },
      Entry{  93000000,  93, 0, 0, "Np", { "Neptunium" } },
      Entry{  94000000,  94, 0, 0, "Pu", { "Plutonium" } },
      Entry{  95000000,  95, 0, 0, "Am", { "Americium" } },
      Entry{  96000000,  96, 0, 0, "Cm", { "Curium" } },
      Entry{  97000000,  97, 0, 0, "Bk", { "Berkelium" } },
      Entry{  98000000,  98, 0, 0, "Cf", { "Californium" } },
      Entry{  99000000,  99, 0, 0, "Es", { "Einsteinium" } },
      Entry{ 100000000, 100, 0, 0, "Fm", { "Fermium" } },
      Entry{ 101000000, 101, 0, 0, "Md", { "Mendelevium" } },
      Entry{ 102000000, 102, 0, 0, "No", { "Nobelium" } },
      Entry{ 103000000, 103, 0, 0, "Lr", { "Lawrencium" } },
      Entry{ 104000000, 104, 0, 0, "Rf", { "Rutherfordium"} },
      Entry{ 105000000, 105, 0, 0, "Db", { "Dubnium" } },
      Entry{ 106000000, 106, 0, 0, "Sg", { "Seaborgium" } },
      Entry{ 107000000, 107, 0, 0, "Bh", { "Bohrium" } },
      Entry{ 108000000, 108, 0, 0, "Hs", { "Hassium" } },
      Entry{ 109000000, 109, 0, 0, "Mt", { "Meitnerium" } },
      Entry{ 110000000, 110, 0, 0, "Ds", { "Darmstadtium" } },
      Entry{ 111000000, 111, 0, 0, "Rg", { "Roentgenium" } },
      Entry{ 112000000, 112, 0, 0, "Cn", { "Copernicium" } },
      Entry{ 113000000, 113, 0, 0, "Nh", { "Nihonium" } },
      Entry{ 114000000, 114, 0, 0, "Fl", { "Flerovium" } },
      Entry{ 115000000, 115, 0, 0, "Mc", { "Moscovium" } },
      Entry{ 116000000, 116, 0, 0, "Lv", { "Livermorium" } },
      Entry{ 117000000, 117, 0, 0, "Ts", { "Tennessine" } },
      Entry{ 118000000, 118, 0, 0, "Og", { "Oganesson" } }
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
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        conversion[ entries[ index ].number() ] = index;
      }
      return conversion;
    }( entries );

    /* fields */
    std::size_t index_;

    /* auxiliary functions */
    #include "dryad/id/ParticleID/src/getIndex.hpp"

  public:

    /* constructor */
    #include "dryad/id/ParticleID/src/ctor.hpp"

    /* predefined identifiers */

    static constexpr ParticleID photon() { return ParticleID{ static_cast< std::size_t >( 0 ) }; };
    static constexpr ParticleID electron() { return ParticleID{ static_cast< std::size_t >( 1 ) }; };
    static constexpr ParticleID positron() { return ParticleID{ static_cast< std::size_t >( 2 ) }; };
    static constexpr ParticleID neutron() { return ParticleID{ static_cast< std::size_t >( 3 ) }; };
    static constexpr ParticleID proton() { return ParticleID{ static_cast< std::size_t >( 4 ) }; };
    static constexpr ParticleID deuteron() { return ParticleID{ static_cast< std::size_t >( 5 ) }; };
    static constexpr ParticleID triton() { return ParticleID{ static_cast< std::size_t >( 6 ) }; };
    static constexpr ParticleID helion() { return ParticleID{ static_cast< std::size_t >( 7 ) }; };
    static constexpr ParticleID alpha() { return ParticleID{ static_cast< std::size_t >( 8 ) }; };

    /* methods */

    /**
     *  @brief Return the number of currently registered identifiers
     */
    static std::size_t size() {

      return entries.size();
    }

    /**
     *  @brief Return the particle number
     */
    int number() const noexcept {

      return entries[ this->index_ ].number();
    }

    /**
     *  @brief Return the particle symbol
     */
    const std::string& symbol() const noexcept {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the particle's element number
     */
    short z() const noexcept {

      return entries[ this->index_ ].z();
    }

    /**
     *  @brief Return the particle's mass number
     */
    short a() const noexcept {

      return entries[ this->index_ ].a();
    }

    /**
     *  @brief Return the particle's level number
     */
    short e() const noexcept {

      return entries[ this->index_ ].e();
    }

    /**
     *  @brief Return the particle's za number
     */
    int za() const noexcept {

      return entries[ this->index_ ].za();
    }

    /**
     *  @brief Return the particle's subshell
     */
    const std::optional< ElectronSubshellID >& subshell() const noexcept {

      return entries[ this->index_ ].subshell();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator==( const ParticleID& left, const ParticleID& right ) {

      return left.number() == right.number();
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

      return left.number() < right.number();
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

    size_t operator()( const njoy::dryad::id::ParticleID& key ) const noexcept {

      return key.number();
    }
  };

} // namespace std

#endif
