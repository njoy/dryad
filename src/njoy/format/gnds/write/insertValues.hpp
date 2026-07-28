#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTVALUES
#define NJOY_FORMAT_GNDS_WRITE_INSERTVALUES

// system includes
#include <optional>
#include <string>
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
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     values   the values
   *  @param[in]     start    the optional starting index
   *  @param[in]     length   the optional length
   *  @param[in]     href     the optional href
   *  @param[in]     start    the optional starting index (used with href)
   *  @param[in]     count    the optional number of elements (used with href)
   */
  inline pugi::xml_node
  insertValues( pugi::xml_node& parent,
                const Options& options,
                const std::vector< double >& values,
                const std::optional< std::size_t >& start = std::nullopt,
                const std::optional< std::size_t >& length = std::nullopt,
                const std::optional< std::string >& href = std::nullopt,
                const std::optional< std::size_t >& index = std::nullopt,
                const std::optional< std::size_t >& count = std::nullopt ) {

    pugi::xml_node node = parent.append_child( "values" );
    if ( start.has_value() ) {

      node.append_attribute( "start" ) = std::move( start.value() );
    }
    if ( length.has_value() ) {

      node.append_attribute( "length" ) = std::move( length.value() );
    }
    if ( href.has_value() ) {

      node.append_attribute( "href" ) = std::move( href.value() );
    }
    if ( index.has_value() ) {

      node.append_attribute( "startIndex" ) = std::move( index.value() );
    }
    if ( count.has_value() ) {

      node.append_attribute( "count" ) = std::move( count.value() );
    }

    // doing shenanigans to make sure we indent the bodytext properly
    std::size_t depth = determineDepth( node );
    std::string single( options.indent, ' ' );
    std::string indent( options.indent * ( depth - 1 ), ' ' );

    std::ostringstream out;
    for ( std::size_t i = 0; i < values.size(); ++i ) {

      if ( i % 6 == 0 ) {

        out << '\n' << indent << single;
      }
      else if ( i != 0 ) {

        out << ' ';
      }
      out << toString( options, values[i] );
    }
    out << '\n' << indent;
    node.text().set( out.str() );

    return node;
  }

  /**
   *  @brief Insert a values xml node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     x        the x values
   *  @param[in]     y        the x values
   *  @param[in]     start    the optional starting index
   *  @param[in]     length   the optional length
   *  @param[in]     href     the optional href
   *  @param[in]     start    the optional starting index (used with href)
   *  @param[in]     count    the optional number of elements (used with href)
   */
  inline pugi::xml_node
  insertValues( pugi::xml_node& parent,
                const Options& options,
                const std::vector< double >& x,
                const std::vector< double >& y,
                const std::optional< std::size_t >& start = std::nullopt,
                const std::optional< std::size_t >& length = std::nullopt,
                const std::optional< std::string >& href = std::nullopt,
                const std::optional< std::size_t >& index = std::nullopt,
                const std::optional< std::size_t >& count = std::nullopt ) {

    if ( x.size() != y.size() ) {

      throw std::runtime_error( "x and y values do not have the same size in a insertValues(...) function" );
    }

    std::vector< double > values;
    values.reserve( 2 * x.size() );
    for ( std::size_t i = 0; i < x.size(); ++i ) {

      values.emplace_back( x[i] );
      values.emplace_back( y[i] );
    }

    return insertValues( parent, options, values, start, length, href, index, count );
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
