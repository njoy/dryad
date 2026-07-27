#ifndef NJOY_FORMAT_GNDS_READ_READDATA
#define NJOY_FORMAT_GNDS_READ_READDATA

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"
#include "tools/disco/FreeFormatReal.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Read data from a GNDS table data node
   *
   *  @param[in] data   the gnds data node
   */
  inline std::vector< double >
  readData( const pugi::xml_node& data ) {

    throwExceptionOnWrongNode( data, "data" );

    using namespace njoy::tools;

    // get the separator - default is white space
    auto sep = data.attribute( "sep" );
    if ( sep ) {

      if ( strcmp( sep.as_string(), "whiteSpace" ) != 0 ) {

        Log::error( "Cannot handle separator \'{}\', contact a developer",
                    sep.as_string() );
      }
    }

    // get values
    std::vector< double > values;
    std::string text = data.text().get();
    auto iter = text.begin();
    auto end = text.end();
    while ( iter != end ) {

      values.emplace_back( disco::FreeFormatReal::read< double >( iter, end ) );
      iter = std::find_if( iter, end,
                           [] ( auto&& value )
                              { return ! std::isspace( value ); }  );
    }

    return values;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
