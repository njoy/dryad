#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTFRACTION
#define NJOY_FORMAT_GNDS_WRITE_INSERTFRACTION

// system includes
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a fraction xml node
   *
   *  @param[in,out] parent        the parent node
   *  @param[in]     option        the gnds write options
   *  @param[in]     numerator     the numerator value
   *  @param[in]     denominator   the denominator value
   *  @param[in]     label         the optional label
   *  @param[in]     unit          the optional unit
   */
  inline pugi::xml_node
  insertFraction( pugi::xml_node& parent,
                  const Options& options,
                  int numerator,
                  int denominator,
                  const std::optional< std::string >& label = std::nullopt,
                  const std::optional< std::string >& unit = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "fraction" );
    if ( label.has_value() ) {

      node.append_attribute( "label" ) = std::move( label.value() );
    }
    if ( denominator == 1 || numerator == 0 ) {

      node.append_attribute( "value" ) = std::to_string( numerator );
    }
    else {

      node.append_attribute( "value" ) = std::to_string( numerator ) + '/' + std::to_string( denominator );
    }
    if ( unit.has_value() ) {

      node.append_attribute( "unit" ) = std::move( unit.value() );
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
