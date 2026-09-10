#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTDOCUMENTATION
#define NJOY_FORMAT_GNDS_WRITE_INSERTDOCUMENTATION

// system includes
#include <optional>
#include <sstream>
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/Documentation.hpp"
#include "njoy/format/gnds/write/determineDepth.hpp"
#include "njoy/format/gnds/write/Options.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a documentation gnds node
   *
   *  @param[in,out] parent          the parent node
   *  @param[in]     option          the gnds write options
   *  @param[in]     documentation   the documentation
   */
  inline pugi::xml_node
  insertDocumentation( pugi::xml_node& parent,
                       const Options& options,
                       const dryad::Documentation& documentation ) {

    pugi::xml_node node;

    if ( documentation.description().has_value() ) {

      node = parent.append_child( "documentation" );

      pugi::xml_node body = node.append_child( "body" );

      std::size_t depth = determineDepth( body );
      std::string indent( options.indent * ( depth - 1 ), ' ' );

      std::ostringstream out;
      out << documentation.description().value() << indent;
      body.text().set( out.str() );
    }

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
