#ifndef NJOY_FORMAT_GNDS_READ_PROCESSEXTERNALFILES
#define NJOY_FORMAT_GNDS_READ_PROCESSEXTERNALFILES

// system includes

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace read {

  /**
   *  @brief Traverse a node and all its descendants and apply a function on each
   *
   *  @param[in] node       the gnds node
   *  @param[in] function   the to be applied
   */
  template < typename Functor >
  void traverseNodesAndApply( pugi::xml_node node, Functor function ) {

    function( node );
    for ( pugi::xml_node child = node.first_child(); child; child = child.next_sibling() ) {

        traverseNodesAndApply( child, function );
    }
  }

  /**
   *  @brief Process external file data in the document
   *
   *  This function copies all nodes from each external file defined in the
   *  reactionSuite and update the href values accordingly. If after these
   *  updates there is a covariance suite, the external files for those are
   *  analysed to retrieve projectile and target info material cross terms.
   *
   *  @param[in] document   the gnds xml document
   *  @param[in] path       the common file path
   */
  inline void processExternalFiles( pugi::xml_document& document,
                                    const std::string& path ) {

    // copy external files for the reaction suite and update hrefs
    auto suite = document.child( "reactionSuite" );
    auto files = suite.child( "externalFiles" );

    std::string covariances_path;

    for ( pugi::xml_node file = files.child( "externalFile" ); file;
          file = file.next_sibling( "externalFile" ) ) {

      std::string filename = file.attribute( "path" ).as_string();
      if ( filename.front() != '/' ) {

        filename.insert( 0, path );
      }

      std::string label = file.attribute( "label" ).as_string();
      if ( label == "covariances" ) {

        covariances_path = filename;
        auto pos = covariances_path.find_last_of( '/' );
        if ( pos != std::string::npos ) {

          covariances_path.erase( pos + 1, covariances_path.size() );
        }
        else {

          covariances_path = "";
        }
      }
      label = "$" + label + "#";

      pugi::xml_document external;
      external.load_file( filename.c_str() );
      if ( external ) {

        // go over all top level nodes in the external file and copy to the current
        // gnds document
        for ( pugi::xml_node node : external.children() ) {

          document.append_copy( node );
        }

        // recursively loop over all children in the reaction suite and look for
        // href attributes that uses this external file
        auto update_href = [&] ( pugi::xml_node node ) {

          auto href = node.attribute( "href" );
          if ( href ) {

            if ( strncmp( href.as_string(), label.c_str(), label.size() ) == 0 ) {

              std::string path = href.as_string();
              path.erase( 0, label.size() );

              href.set_value( path.c_str() );
            }
          }
        };
        traverseNodesAndApply( suite, update_href );
      }
      else {

        Log::error( "The external GNDS file \'{}\' does not exist or is not an XML file",
                    filename );
        throw std::exception();
      }
    }

    // update the file paths for external files in the covariance suite
    suite = document.child( "covarianceSuite" );
    files = suite.child( "externalFiles" );

    for ( pugi::xml_node file = files.child( "externalFile" ); file;
          file = file.next_sibling( "externalFile" ) ) {

      std::string filename = file.attribute( "path" ).as_string();
      if ( filename.front() != '/' ) {

        filename.insert( 0, covariances_path );
        file.attribute( "path" ).set_value( filename.c_str() );
      }

      pugi::xml_document external;
      external.load_file( filename.c_str() );
      if ( ! external ) {

        Log::error( "The external GNDS file \'{}\' does not exist or is not an XML file",
                    filename );
        throw std::exception();
      }
    }
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
