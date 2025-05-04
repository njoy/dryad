#ifndef NJOY_ELEMENTARY_ELEMENTID
#define NJOY_ELEMENTARY_ELEMENTID

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
   *  @brief The element identifier, with associated element symbol, name and aliases
   *
   *  Comparison operators are provided using the logical order given by the
   *  element number. A hash function and override for std::hash is also
   *  provided.
   */
  class ElementID {

    /* helper class */
    #include "dryad/id/ElementID/Entry.hpp"

    /* static fields */
    static inline const std::vector< Entry > entries{

      Entry{   0, ""  , ""             , {} },
      Entry{   1, "H" , "Hydrogen"     , {} },
      Entry{   2, "He", "Helium"       , {} },
      Entry{   3, "Li", "Lithium"      , {} },
      Entry{   4, "Be", "Beryllium"    , {} },
      Entry{   5, "B" , "Boron"        , {} },
      Entry{   6, "C" , "Carbon"       , {} },
      Entry{   7, "N" , "Nitrogen"     , {} },
      Entry{   8, "O" , "Oxygen"       , {} },
      Entry{   9, "F" , "Fluorine"     , {} },
      Entry{  10, "Ne", "Neon"         , {} },
      Entry{  11, "Na", "Sodium"       , {} },
      Entry{  12, "Mg", "Magnesium"    , {} },
      Entry{  13, "Al", "Aluminium"    , { "Aluminum" } },
      Entry{  14, "Si", "Silicon"      , {} },
      Entry{  15, "P" , "Phosphorus"   , {} },
      Entry{  16, "S" , "Sulfur"       , {} },
      Entry{  17, "Cl", "Chlorine"     , {} },
      Entry{  18, "Ar", "Argon"        , {} },
      Entry{  19, "K" , "Potassium"    , {} },
      Entry{  20, "Ca", "Calcium"      , {} },
      Entry{  21, "Sc", "Scandium"     , {} },
      Entry{  22, "Ti", "Titanium"     , {} },
      Entry{  23, "V" , "Vanadium"     , {} },
      Entry{  24, "Cr", "Chromium"     , {} },
      Entry{  25, "Mn", "Manganese"    , {} },
      Entry{  26, "Fe", "Iron"         , {} },
      Entry{  27, "Co", "Cobalt"       , {} },
      Entry{  28, "Ni", "Nickel"       , {} },
      Entry{  29, "Cu", "Copper"       , {} },
      Entry{  30, "Zn", "Zinc"         , {} },
      Entry{  31, "Ga", "Gallium"      , {} },
      Entry{  32, "Ge", "Germanium"    , {} },
      Entry{  33, "As", "Arsenic"      , {} },
      Entry{  34, "Se", "Selenium"     , {} },
      Entry{  35, "Br", "Bromine"      , {} },
      Entry{  36, "Kr", "Krypton"      , {} },
      Entry{  37, "Rb", "Rubidium"     , {} },
      Entry{  38, "Sr", "Strontium"    , {} },
      Entry{  39, "Y" , "Yttrium"      , {} },
      Entry{  40, "Zr", "Zirconium"    , {} },
      Entry{  41, "Nb", "Niobium"      , {} },
      Entry{  42, "Mo", "Molybdenum"   , {} },
      Entry{  43, "Tc", "Technetium"   , {} },
      Entry{  44, "Ru", "Ruthenium"    , {} },
      Entry{  45, "Rh", "Rhodium"      , {} },
      Entry{  46, "Pd", "Palladium"    , {} },
      Entry{  47, "Ag", "Silver"       , {} },
      Entry{  48, "Cd", "Cadmium"      , {} },
      Entry{  49, "In", "Indium"       , {} },
      Entry{  50, "Sn", "Tin"          , {} },
      Entry{  51, "Sb", "Antimony"     , {} },
      Entry{  52, "Te", "Tellurium"    , {} },
      Entry{  53, "I" , "Iodine"       , {} },
      Entry{  54, "Xe", "Xenon"        , {} },
      Entry{  55, "Cs", "Caesium"      , { "Cesium" } },
      Entry{  56, "Ba", "Barium"       , {} },
      Entry{  57, "La", "Lanthanum"    , {} },
      Entry{  58, "Ce", "Cerium"       , {} },
      Entry{  59, "Pr", "Praseodymium" , {} },
      Entry{  60, "Nd", "Neodymium"    , {} },
      Entry{  61, "Pm", "Promethium"   , {} },
      Entry{  62, "Sm", "Samarium"     , {} },
      Entry{  63, "Eu", "Europium"     , {} },
      Entry{  64, "Gd", "Gadolinium"   , {} },
      Entry{  65, "Tb", "Terbium"      , {} },
      Entry{  66, "Dy", "Dysprosium"   , {} },
      Entry{  67, "Ho", "Holmium"      , {} },
      Entry{  68, "Er", "Erbium"       , {} },
      Entry{  69, "Tm", "Thulium"      , {} },
      Entry{  70, "Yb", "Ytterbium"    , {} },
      Entry{  71, "Lu", "Lutetium"     , {} },
      Entry{  72, "Hf", "Hafnium"      , {} },
      Entry{  73, "Ta", "Tantalum"     , {} },
      Entry{  74, "W" , "Tungsten"     , {} },
      Entry{  75, "Re", "Rhenium"      , {} },
      Entry{  76, "Os", "Osmium"       , {} },
      Entry{  77, "Ir", "Iridium"      , {} },
      Entry{  78, "Pt", "Platinum"     , {} },
      Entry{  79, "Au", "Gold"         , {} },
      Entry{  80, "Hg", "Mercury"      , {} },
      Entry{  81, "Tl", "Thallium"     , {} },
      Entry{  82, "Pb", "Lead"         , {} },
      Entry{  83, "Bi", "Bismuth"      , {} },
      Entry{  84, "Po", "Polonium"     , {} },
      Entry{  85, "At", "Astatine"     , {} },
      Entry{  86, "Rn", "Radon"        , {} },
      Entry{  87, "Fr", "Francium"     , {} },
      Entry{  88, "Ra", "Radium"       , {} },
      Entry{  89, "Ac", "Actinium"     , {} },
      Entry{  90, "Th", "Thorium"      , {} },
      Entry{  91, "Pa", "Protactinium" , {} },
      Entry{  92, "U" , "Uranium"      , {} },
      Entry{  93, "Np", "Neptunium"    , {} },
      Entry{  94, "Pu", "Plutonium"    , {} },
      Entry{  95, "Am", "Americium"    , {} },
      Entry{  96, "Cm", "Curium"       , {} },
      Entry{  97, "Bk", "Berkelium"    , {} },
      Entry{  98, "Cf", "Californium"  , {} },
      Entry{  99, "Es", "Einsteinium"  , {} },
      Entry{ 100, "Fm", "Fermium"      , {} },
      Entry{ 101, "Md", "Mendelevium"  , {} },
      Entry{ 102, "No", "Nobelium"     , {} },
      Entry{ 103, "Lr", "Lawrencium"   , {} },
      Entry{ 104, "Rf", "Rutherfordium", {} },
      Entry{ 105, "Db", "Dubnium"      , {} },
      Entry{ 106, "Sg", "Seaborgium"   , {} },
      Entry{ 107, "Bh", "Bohrium"      , {} },
      Entry{ 108, "Hs", "Hassium"      , {} },
      Entry{ 109, "Mt", "Meitnerium"   , {} },
      Entry{ 110, "Ds", "Darmstadtium" , {} },
      Entry{ 111, "Rg", "Roentgenium"  , {} },
      Entry{ 112, "Cn", "Copernicium"  , {} },
      Entry{ 113, "Nh", "Nihonium"     , {} },
      Entry{ 114, "Fl", "Flerovium"    , {} },
      Entry{ 115, "Mc", "Moscovium"    , {} },
      Entry{ 116, "Lv", "Livermorium"  , {} },
      Entry{ 117, "Ts", "Tennessine"   , {} },
      Entry{ 118, "Og", "Oganesson"    , {} }
    };
    static inline const std::unordered_map< std::string, std::size_t >
    conversion_dictionary = [] ( const auto& entries ) {

      std::unordered_map< std::string, std::size_t > conversion;
      for ( std::size_t index = 0; index < entries.size(); ++index ) {

        conversion[ entries[ index ].symbol() ] = index;
        conversion[ entries[ index ].name() ] = index;
        for ( const auto& alternative : entries[ index ].alternatives() ) {

          conversion[ alternative ] = index;
        }
      }
      return conversion;
    }( entries );

    /* fields */
    std::size_t index_;

    /* auxiliary functions */
    #include "dryad/id/ElementID/src/getIndex.hpp"

  public:

    /* constructor */
    #include "dryad/id/ElementID/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the element number
     */
    unsigned char number() const noexcept {

      return entries[ this->index_ ].number();
    }

    /**
     *  @brief Return the element symbol
     */
    const std::string& symbol() const noexcept {

      return entries[ this->index_ ].symbol();
    }

    /**
     *  @brief Return the element name
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
    friend auto operator==( const ElementID& left, const ElementID& right ) {

      return left.number() == right.number();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator!=( const ElementID& left, const ElementID& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<( const ElementID& left, const ElementID& right ) {

      return left.number() < right.number();
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>( const ElementID& left, const ElementID& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator<=( const ElementID& left, const ElementID& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend auto operator>=( const ElementID& left, const ElementID& right ) {

      return ! ( left < right );
    }
  };

} // id namespace
} // dryad namespace
} // njoy namespace

namespace std {

  // std::hash override for the ElementID class
  template <>
  struct hash< njoy::dryad::id::ElementID > {

    size_t operator()( const njoy::dryad::id::ElementID& key ) const noexcept {

      return key.number();
    }
  };

} // namespace std

#endif
