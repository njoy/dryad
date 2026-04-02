#ifndef NJOY_DRYAD_FORMAT_GNDS_READFRACTION
#define NJOY_DRYAD_FORMAT_GNDS_READFRACTION

// system includes
#include <optional>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/Log.hpp"
#include "tools/split.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  using Fraction = std::pair< double, std::optional< std::string > >;

  /**
   *  @brief Read data from a GNDS fraction node
   */
  inline Fraction readFraction( const pugi::xml_node& node ) {

    throwExceptionOnWrongNode( node, "fraction" );

    Fraction data;
    data.second = std::nullopt;

    // get the value (required)
    auto value = node.attribute( "value" );
    if ( value ) {

      auto pieces = tools::split( value.as_string(), '/' );
      if ( pieces.size() > 0 && pieces.size() < 3 ) {

        data.first = std::stod( pieces[0].c_str() );
        if ( pieces.size() == 2 ) {

          data.first = std::stod( pieces[0].c_str() ) / std::stod( pieces[1].c_str() );
        }
      }
      else {

        Log::error( "The value attribute does not appear to be a proper fraction: \'{}\'",
                    value.as_string() );
        throw std::exception();
      }
    }
    else {

      Log::error( "Did not find the required \'value\' attribute in the fraction node "
                  "with label \'{}\'", node.attribute( "label" ).as_string() );
      throw std::exception();
    }

    // get the unit (optional)
    auto unit = node.attribute( "unit" );
    if ( unit ) {

      data.second = unit.as_string();
    }

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
