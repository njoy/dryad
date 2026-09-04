#ifndef NJOY_FORMAT_GNDS_READ_READVALUES
#define NJOY_FORMAT_GNDS_READ_READVALUES

// system includes
#include <type_traits>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/disco/FreeFormatReal.hpp"
#include "tools/disco/FreeFormatInteger.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Read data from a GNDS values node
   *
   *  @param[in] values   the gnds values node
   */
  template < typename Type = double >
  std::vector< Type >
  readValues( const pugi::xml_node& values ) {

    throwExceptionOnWrongNode( values, "values" );

    using namespace njoy::tools;

    // get tabulated values
    std::vector< Type > data;
    std::string text = values.text().get();
    auto iter = text.begin();
    auto end = text.end();
    while ( iter != end ) {

      if constexpr ( std::is_integral_v< Type > ) {

        data.emplace_back( disco::FreeFormatInteger::read< Type >( iter, end ) );
      }
      else {

        data.emplace_back( disco::FreeFormatReal::read< Type >( iter, end ) );
      }
      iter = std::find_if( iter, end,
                           [] ( auto&& value )
                              { return ! std::isspace( value ); }  );
    }

    return data;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
