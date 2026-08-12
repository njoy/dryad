#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTHARDSPHERERADIUS
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTHARDSPHERERADIUS

// system includes
#include <string>
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/TabulatedRadius.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertConstant1d.hpp"
#include "njoy/format/gnds/write/insertTabulatedFunction.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {

  /**
   *  @brief Insert a radius into a gnds node
   *
   *  @param[in,out] parent   the parent node
   *  @param[in]     option   the gnds write options
   *  @param[in]     radius   the scattering radius
   *  @param[in]     min      the lower domain limit
   *  @param[in]     max      the upper domain limit
   *  @param[in]     style    the style label to be used
   */
  inline pugi::xml_node
  insertHardSphereRadius( pugi::xml_node& parent,
                          const Options& options,
                          const std::variant< double, dryad::resonances::TabulatedRadius >& radius,
                          double min,
                          double max,
                          const std::string& style ) {

    pugi::xml_node node = parent.append_child( "hardSphereRadius" );

    //! @todo this is where we would convert units if we really wanted to

    auto insert = tools::overload{

      [&] ( double value ) -> pugi::xml_node {

        return insertConstant1d( node, options, value, min, max,
                                 "incidentEnergy", "radius", "eV", "fm", style );
      },
      [&] ( const dryad::resonances::TabulatedRadius& table ) -> pugi::xml_node {

        return insertTabulatedFunction( node, options, table.energies(), table.values(),
                                        table.boundaries(), table.interpolants(),
                                        "incidentEnergy", "radius", "eV", "fm", style );
      }
    };

    std::visit( insert, radius );
    return node;
  }

} // resonances namespace
} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
