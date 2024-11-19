#ifndef NJOY_DRYAD_FORMAT_GNDS_READVALUES
#define NJOY_DRYAD_FORMAT_GNDS_READVALUES

// system includes
#include <vector>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "dryad/format/gnds/throwExceptionOnWrongNode.hpp"
#include "tools/disco/FreeFormatReal.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {

  /**
   *  @brief Read data from a GNDS values node
   */
  static std::vector< double >
  readValues( const pugi::xml_node& values ) {

    throwExceptionOnWrongNode( values, "values" );

    using namespace njoy::tools;

    // get tabulated values
    std::vector< double > data;
    std::string text = values.text().get();
    auto iter = text.begin();
    auto end = text.end();
    while ( iter != end ) {

      data.emplace_back( disco::FreeFormatReal::read< double >( iter, end ) );
      iter = std::find_if( iter, end,
                           [] ( auto&& value )
                              { return ! std::isspace( value ); }  );
    }

    return data;
  }

} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
