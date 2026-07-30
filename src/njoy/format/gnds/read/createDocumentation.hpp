#ifndef NJOY_FORMAT_GNDS_READ_CREATEDOCUMENTATION
#define NJOY_FORMAT_GNDS_READ_CREATEDOCUMENTATION

// system includes
#include <iomanip>
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "tools/split.hpp"
#include "njoy/dryad/Documentation.hpp"
#include "njoy/format/gnds/read/throwExceptionOnWrongNode.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Create Documentation from a GNDS documentation node
   *
   *  @param[in] documentation   the GNDS documentation node
   */
  inline dryad::Documentation
  createDocumentation( pugi::xml_node documentation, const std::string& style = "eval" ) {

    // check that this is a valid documentation node
    throwExceptionOnWrongNode( documentation, "documentation" );

    std::optional< int > library = std::nullopt;
    std::optional< std::pair< int, int > > version = std::nullopt;

    std::optional< std::string > description = std::nullopt;
    auto body = documentation.child( "body" );
    auto endf = documentation.child( "endfCompatible" );
    if ( body || endf ) {

      // read the endf one first before trying the body one
      if ( endf ) {

        description = endf.text().as_string();
      }
      else {

        description = body.text().as_string();
      }

      // remove trailing whitespace (just in case)
      auto iter = std::find_if( description->rbegin(), description->rend(),
                                [] ( unsigned char c ) { return ! std::isspace( c ); } ).base();

      if ( iter != std::prev( description->end() ) ) {

        description->erase( iter, description->end() );
      }

      // set to 66 characters and add newline character
      // !@todo split lines that are over 66 characters
      std::istringstream in( description.value() );
      std::ostringstream out;
      std::string line;
      while ( std::getline( in, line ) ) {

        out << std::left << std::setw( 66 ) << line << '\n';
      }
      description = out.str();
    }

    return dryad::Documentation( std::move( library ), std::move( version ),
                                 std::move( description ) );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
