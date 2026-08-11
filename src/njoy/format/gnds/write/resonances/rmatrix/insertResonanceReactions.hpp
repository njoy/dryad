#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_INSERTRESONANCEREACTIONS
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_RMATRIX_INSERTRESONANCEREACTIONS

// system includes
#include <map>
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/CompoundSystem.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/insertQ.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/createFormalism.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/createBoundaryCondition.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Insert the resonance reactions node into a gnds node
   *
   *  @param[in,out] parent              the parent node
   *  @param[in]     option              the gnds write options
   *  @param[in]     compound            the compound system to be written out
   *  @param[in]     qvalues             the default reaction q values
   *  @param[in]     style               the style label to be used
   *  @param[in]     fullResonanceData   include all resonance data even if it is optional
   *                                     or duplicated (default is true)
   */
  inline pugi::xml_node
  insertResonanceReactions( pugi::xml_node& parent,
                            const Options& options,
                            const dryad::resonances::CompoundSystem& compound,
                            const std::map< dryad::id::ReactionID, double >& qvalues,
                            const std::string& style,
                            bool fullResonanceData = true ) {

    pugi::xml_node node = parent.append_child( "resonanceReactions" );
    for ( const auto& id : compound.reactions() ) {

      pugi::xml_node reaction = node.append_child( "resonanceReaction" );
      reaction.append_attribute( "label" ) = id.symbol();
      if ( id.particles().has_value() ) {

        reaction.append_attribute( "ejectile" ) = id.particles()->size() == 0 ? "g" : id.particles()->begin()->first.symbol();
        if ( compound.formalism() == dryad::resonances::Formalism::ReichMoore &&
             id.particles()->size() == 0 ) {

          reaction.append_attribute( "eliminated" ) = "true";
        }
      }

      pugi::xml_node link = reaction.append_child( "link" );
      link.append_attribute( "href" ) = "/reactionSuite/reactions/reaction[@label=\'" + id.symbol() + "\']";

      bool found_q = false;
      for ( const auto& group : compound.spinGroups() ) {

        for ( const auto& channel : group.channels() ) {

          if ( channel.reaction() == id ) {

            if ( fullResonanceData || channel.qValue() != qvalues.at( id ) ) {

              insertQ( reaction, options, channel.qValue(), compound.lowerEnergyLimit(), compound.upperEnergyLimit(), style );
            }

            found_q = true;
            break;
          }
        }

        if ( found_q ) {

          break;
        }
      }
    }

    return node;
  }

} // rmatrix namespace
} // resonances namespace
} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
