#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTDATA
#define NJOY_FORMAT_GNDS_WRITE_INSERTDATA

// system includes
#include <sstream>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/determineDepth.hpp"
#include "njoy/format/gnds/write/toString.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a values xml node
   *
   *  Note: The table can technically store different types by columns. We'll
   *        assume it's just doubles. While there are different ways of storing
   *        a table, we're going to take row major and whitespace separators.
   *
   *  @param[in,out] parent      the parent node
   *  @param[in]     option      the gnds write options
   *  @param[in]     columns     the columns of values
   */
  inline pugi::xml_node
  insertData( pugi::xml_node& parent,
              const Options& options,
              const std::vector< std::vector< double > >& columns ) {

    pugi::xml_node node = parent.append_child( "data" );

    // doing shenanigans to make sure we indent the bodytext properly
    std::size_t depth = determineDepth( node );
    std::string single( options.indent, ' ' );
    std::string indent( options.indent * ( depth - 1 ), ' ' );

    std::ostringstream out;
    out << std::endl;
    for ( std::size_t i = 0; i < columns.front().size(); ++i ) {

      for ( std::size_t j = 0; j < columns.size(); ++j ) {

        if ( j == 0 ) {

          out << indent << single;
        }
        else {

          out << ' ';
        }

        out << toString( options, columns[j][i] );
      }
      out << std::endl;
    }
    out << indent;
    node.text().set( out.str() );

    return node;
  }

} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
