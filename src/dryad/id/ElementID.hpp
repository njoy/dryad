#ifndef NJOY_ELEMENTARY_ELEMENTID
#define NJOY_ELEMENTARY_ELEMENTID

// system includes
#include <memory>
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
    static inline const std::unordered_map< int, Entry > element_dictionary{

      {   1, Entry{   1, "H" , "Hydrogen"     , {} } },
      {   2, Entry{   2, "He", "Helium"       , {} } },
      {   3, Entry{   3, "Li", "Lithium"      , {} } },
      {   4, Entry{   4, "Be", "Beryllium"    , {} } },
      {   5, Entry{   5, "B" , "Boron"        , {} } },
      {   6, Entry{   6, "C" , "Carbon"       , {} } },
      {   7, Entry{   7, "N" , "Nitrogen"     , {} } },
      {   8, Entry{   8, "O" , "Oxygen"       , {} } },
      {   9, Entry{   9, "F" , "Fluorine"     , {} } },
      {  10, Entry{  10, "Ne", "Neon"         , {} } },
      {  11, Entry{  11, "Na", "Sodium"       , {} } },
      {  12, Entry{  12, "Mg", "Magnesium"    , {} } },
      {  13, Entry{  13, "Al", "Aluminium"    , { "Aluminum" } } },
      {  14, Entry{  14, "Si", "Silicon"      , {} } },
      {  15, Entry{  15, "P" , "Phosphorus"   , {} } },
      {  16, Entry{  16, "S" , "Sulfur"       , {} } },
      {  17, Entry{  17, "Cl", "Chlorine"     , {} } },
      {  18, Entry{  18, "Ar", "Argon"        , {} } },
      {  19, Entry{  19, "K" , "Potassium"    , {} } },
      {  20, Entry{  20, "Ca", "Calcium"      , {} } },
      {  21, Entry{  21, "Sc", "Scandium"     , {} } },
      {  22, Entry{  22, "Ti", "Titanium"     , {} } },
      {  23, Entry{  23, "V" , "Vanadium"     , {} } },
      {  24, Entry{  24, "Cr", "Chromium"     , {} } },
      {  25, Entry{  25, "Mn", "Manganese"    , {} } },
      {  26, Entry{  26, "Fe", "Iron"         , {} } },
      {  27, Entry{  27, "Co", "Cobalt"       , {} } },
      {  28, Entry{  28, "Ni", "Nickel"       , {} } },
      {  29, Entry{  29, "Cu", "Copper"       , {} } },
      {  30, Entry{  30, "Zn", "Zinc"         , {} } },
      {  31, Entry{  31, "Ga", "Gallium"      , {} } },
      {  32, Entry{  32, "Ge", "Germanium"    , {} } },
      {  33, Entry{  33, "As", "Arsenic"      , {} } },
      {  34, Entry{  34, "Se", "Selenium"     , {} } },
      {  35, Entry{  35, "Br", "Bromine"      , {} } },
      {  36, Entry{  36, "Kr", "Krypton"      , {} } },
      {  37, Entry{  37, "Rb", "Rubidium"     , {} } },
      {  38, Entry{  38, "Sr", "Strontium"    , {} } },
      {  39, Entry{  39, "Y" , "Yttrium"      , {} } },
      {  40, Entry{  40, "Zr", "Zirconium"    , {} } },
      {  41, Entry{  41, "Nb", "Niobium"      , {} } },
      {  42, Entry{  42, "Mo", "Molybdenum"   , {} } },
      {  43, Entry{  43, "Tc", "Technetium"   , {} } },
      {  44, Entry{  44, "Ru", "Ruthenium"    , {} } },
      {  45, Entry{  45, "Rh", "Rhodium"      , {} } },
      {  46, Entry{  46, "Pd", "Palladium"    , {} } },
      {  47, Entry{  47, "Ag", "Silver"       , {} } },
      {  48, Entry{  48, "Cd", "Cadmium"      , {} } },
      {  49, Entry{  49, "In", "Indium"       , {} } },
      {  50, Entry{  50, "Sn", "Tin"          , {} } },
      {  51, Entry{  51, "Sb", "Antimony"     , {} } },
      {  52, Entry{  52, "Te", "Tellurium"    , {} } },
      {  53, Entry{  53, "I" , "Iodine"       , {} } },
      {  54, Entry{  54, "Xe", "Xenon"        , {} } },
      {  55, Entry{  55, "Cs", "Caesium"      , { "Cesium" } } },
      {  56, Entry{  56, "Ba", "Barium"       , {} } },
      {  57, Entry{  57, "La", "Lanthanum"    , {} } },
      {  58, Entry{  58, "Ce", "Cerium"       , {} } },
      {  59, Entry{  59, "Pr", "Praseodymium" , {} } },
      {  60, Entry{  60, "Nd", "Neodymium"    , {} } },
      {  61, Entry{  61, "Pm", "Promethium"   , {} } },
      {  62, Entry{  62, "Sm", "Samarium"     , {} } },
      {  63, Entry{  63, "Eu", "Europium"     , {} } },
      {  64, Entry{  64, "Gd", "Gadolinium"   , {} } },
      {  65, Entry{  65, "Tb", "Terbium"      , {} } },
      {  66, Entry{  66, "Dy", "Dysprosium"   , {} } },
      {  67, Entry{  67, "Ho", "Holmium"      , {} } },
      {  68, Entry{  68, "Er", "Erbium"       , {} } },
      {  69, Entry{  69, "Tm", "Thulium"      , {} } },
      {  70, Entry{  70, "Yb", "Ytterbium"    , {} } },
      {  71, Entry{  71, "Lu", "Lutetium"     , {} } },
      {  72, Entry{  72, "Hf", "Hafnium"      , {} } },
      {  73, Entry{  73, "Ta", "Tantalum"     , {} } },
      {  74, Entry{  74, "W" , "Tungsten"     , {} } },
      {  75, Entry{  75, "Re", "Rhenium"      , {} } },
      {  76, Entry{  76, "Os", "Osmium"       , {} } },
      {  77, Entry{  77, "Ir", "Iridium"      , {} } },
      {  78, Entry{  78, "Pt", "Platinum"     , {} } },
      {  79, Entry{  79, "Au", "Gold"         , {} } },
      {  80, Entry{  80, "Hg", "Mercury"      , {} } },
      {  81, Entry{  81, "Tl", "Thallium"     , {} } },
      {  82, Entry{  82, "Pb", "Lead"         , {} } },
      {  83, Entry{  83, "Bi", "Bismuth"      , {} } },
      {  84, Entry{  84, "Po", "Polonium"     , {} } },
      {  85, Entry{  85, "At", "Astatine"     , {} } },
      {  86, Entry{  86, "Rn", "Radon"        , {} } },
      {  87, Entry{  87, "Fr", "Francium"     , {} } },
      {  88, Entry{  88, "Ra", "Radium"       , {} } },
      {  89, Entry{  89, "Ac", "Actinium"     , {} } },
      {  90, Entry{  90, "Th", "Thorium"      , {} } },
      {  91, Entry{  91, "Pa", "Protactinium" , {} } },
      {  92, Entry{  92, "U" , "Uranium"      , {} } },
      {  93, Entry{  93, "Np", "Neptunium"    , {} } },
      {  94, Entry{  94, "Pu", "Plutonium"    , {} } },
      {  95, Entry{  95, "Am", "Americium"    , {} } },
      {  96, Entry{  96, "Cm", "Curium"       , {} } },
      {  97, Entry{  97, "Bk", "Berkelium"    , {} } },
      {  98, Entry{  98, "Cf", "Californium"  , {} } },
      {  99, Entry{  99, "Es", "Einsteinium"  , {} } },
      { 100, Entry{ 100, "Fm", "Fermium"      , {} } },
      { 101, Entry{ 101, "Md", "Mendelevium"  , {} } },
      { 102, Entry{ 102, "No", "Nobelium"     , {} } },
      { 103, Entry{ 103, "Lr", "Lawrencium"   , {} } },
      { 104, Entry{ 104, "Rf", "Rutherfordium", {} } },
      { 105, Entry{ 105, "Db", "Dubnium"      , {} } },
      { 106, Entry{ 106, "Sg", "Seaborgium"   , {} } },
      { 107, Entry{ 107, "Bh", "Bohrium"      , {} } },
      { 108, Entry{ 108, "Hs", "Hassium"      , {} } },
      { 109, Entry{ 109, "Mt", "Meitnerium"   , {} } },
      { 110, Entry{ 110, "Ds", "Darmstadtium" , {} } },
      { 111, Entry{ 111, "Rg", "Roentgenium"  , {} } },
      { 112, Entry{ 112, "Cn", "Copernicium"  , {} } },
      { 113, Entry{ 113, "Nh", "Nihonium"     , {} } },
      { 114, Entry{ 114, "Fl", "Flerovium"    , {} } },
      { 115, Entry{ 115, "Mc", "Moscovium"    , {} } },
      { 116, Entry{ 116, "Lv", "Livermorium"  , {} } },
      { 117, Entry{ 117, "Ts", "Tennessine"   , {} } },
      { 118, Entry{ 118, "Og", "Oganesson"    , {} } }
    };
    static inline const std::unordered_map< std::string, int > conversion_dictionary = [] ( const auto& dictionary ) {

      std::unordered_map< std::string, int > conversion;
      for ( const auto& [ number, entry ] : dictionary ) {

        conversion[ entry.symbol() ] = number;
        conversion[ entry.name() ] = number;
        for ( const auto& alternative : entry.alternatives() ) {

          conversion[ alternative ] = number;
        }
      }
      return conversion;
    }( element_dictionary );

    /* fields */
    const Entry* entry_;

    /* auxiliary functions */
    #include "dryad/id/ElementID/src/getPointer.hpp"

  public:

    /* constructor */
    #include "dryad/id/ElementID/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the element number
     */
    int number() const noexcept {

      return this->entry_->number();
    }

    /**
     *  @brief Return the element symbol
     */
    const std::string& symbol() const noexcept {

      return this->entry_->symbol();
    }

    /**
     *  @brief Return the element name
     */
    const std::string& name() const noexcept {

      return this->entry_->name();
    }

    /**
     *  @brief Equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend constexpr auto operator==( const ElementID& left, const ElementID& right ) {

      return left.number() == right.number();
    }

    /**
     *  @brief Inequality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend constexpr auto operator!=( const ElementID& left, const ElementID& right ) {

      return ! ( left == right );
    }

    /**
     *  @brief Less than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend constexpr auto operator<( const ElementID& left, const ElementID& right ) {

      return left.number() < right.number();
    }

    /**
     *  @brief Greater than comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend constexpr auto operator>( const ElementID& left, const ElementID& right ) {

      return right < left;
    }

    /**
     *  @brief Less than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend constexpr auto operator<=( const ElementID& left, const ElementID& right ) {

      return ! ( right < left );
    }

    /**
     *  @brief Greater than or equality comparison
     *
     *  @param[in] left    the id on the left
     *  @param[in] right   the id on the right
     */
    friend constexpr auto operator>=( const ElementID& left, const ElementID& right ) {

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

    size_t operator()( const njoy::dryad::id::ElementID& key ) const {

      return key.number();
    }
  };

} // namespace std

#endif
