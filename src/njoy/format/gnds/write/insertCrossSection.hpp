#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTCROSSSECTION
#define NJOY_FORMAT_GNDS_WRITE_INSERTCROSSSECTION

// system includes
#include <optional>
#include <string>
#include <vector>

// other includes
#include "pugixml.hpp"
#include "njoy/dryad/TabulatedCrossSection.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertTabulatedFunction.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a tabulated cross section into a gnds node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     table    the tabulated data
   *  @param[in]     style    the style label to be used
   */
  inline pugi::xml_node
  insertCrossSection( pugi::xml_node& parent,
                      const Options& options,
                      const dryad::TabulatedCrossSection& table,
                      const std::string& style ) {

    pugi::xml_node node = parent.append_child( "crossSection" );

    //! @todo this is where we would convert units if we really wanted to

    insertTabulatedFunction( node, options, table.energies(), table.values(),
                             table.boundaries(), table.interpolants(),
                             "incidentEnergy", "crossSection", "eV", "b",
                             style );

    return node;
  }

} // read namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
