#ifndef NJOY_DRYAD_FORMAT_GNDS_POPS_CREATEENERGY
#define NJOY_DRYAD_FORMAT_GNDS_POPS_CREATEENERGY

// system includes
#include <tuple>

// other includes
#include "pugixml.hpp"
#include "tools/Log.hpp"
#include "njoy/dryad/format/gnds/readDouble.hpp"
#include "njoy/dryad/format/gnds/convertEnergy.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace pops {

  /**
   *  @brief Create a energy values from a GNDS energy xml node
   *
   *  @param[in] energy   the GNDS energy node
   *  @param[in] style    the gnds style to process (default is eval)
   */
  inline std::optional< double >
  createEnergy( const pugi::xml_node& energy, const std::string& style = "eval" ) {

    // check that this is a valid energy node
    throwExceptionOnWrongNode( energy, "energy" );

    // get a double node if it exists, else return nullopt
    auto child = energy.find_child_by_attribute( "double", "label", style.c_str() );
    if ( child ) {

      auto content = readDouble( child );
      convertEnergy( content.first, content.second.value() );
      return content.first;
    }

    return std::nullopt;
  }

} // pops namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
