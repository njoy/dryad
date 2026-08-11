#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTRESONANCES
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTRESONANCES

// system includes
#include <optional>
#include <string>
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/insertRMatrix.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {

  /**
   *  @brief Insert a resonances into a gnds node
   *
   *  @param[in,out] parent                   the parent node
   *  @param[in]     option                   the gnds write options
   *  @param[in]     pt                       the projectile target
   *  @param[in]     style                    the style label to be used
   *  @param[in]     reducedWidthAmplitudes   use reduced width amplitudes (default is true)
   */
  inline pugi::xml_node
  insertResonances( pugi::xml_node& parent,
                    const Options& options,
                    const dryad::ProjectileTarget& pt,
                    const std::string& style,
                    bool reducedWidthAmplitudes = true ) {

    pugi::xml_node node;
    if ( pt.resonances().has_value() ) {

      node = parent.append_child( "resonances" );

      std::map< dryad::id::ReactionID, double > qvalues;

      for ( const dryad::resonances::CompoundSystem& region : pt.resonances()->resolved() ) {

        for ( const dryad::id::ReactionID& id : region.reactions() ) {

          qvalues.try_emplace( id, pt.reaction( id ).reactionQValue().value() );
        }

        pugi::xml_node resolved = node.append_child( "resolved" );
        resolved.append_attribute( "domainMin" ) = toString( options, region.lowerEnergyLimit() );
        resolved.append_attribute( "domainMax" ) = toString( options, region.upperEnergyLimit() );
        resolved.append_attribute( "domainUnit" ) = "eV";

        rmatrix::insertRMatrix( resolved, options, region, qvalues, style, reducedWidthAmplitudes );
      }
    }

    return node;
  }

} // resonances namespace
} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
