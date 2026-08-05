#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTREACTIONS
#define NJOY_FORMAT_GNDS_WRITE_INSERTREACTIONS

// system includes
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/revertScatterLevel.hpp"
#include "njoy/format/gnds/write/insertCrossSection.hpp"
#include "njoy/format/gnds/write/insertOutputChannel.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a gnds reactions node
   *
   *  @param[in,out] parent       the parent node
   *  @param[in]     option       the gnds write options
   *  @param[in]     reactions    the reactions
   *  @param[in]     resonances   the optional resonance parameters
   *  @param[in]     label        the style label to be used
   */
  inline pugi::xml_node
  insertReactions( pugi::xml_node& parent,
                   const Options& options,
                   const std::vector< dryad::Reaction >& reactions,
                   const std::optional< dryad::resonances::ResonanceParameters > resonances,
                   const std::string& label ) {

    pugi::xml_node reactions_node;

    auto projectile = reactions.front().identifier().projectile();
    auto target = reactions.front().identifier().target();

    auto is_primary = [] ( auto&& reaction ) {  return reaction.isPrimaryReaction(); };

    if ( std::any_of( reactions.begin(), reactions.end(), is_primary ) ) {

      reactions_node = parent.append_child( "reactions" );

      for ( const auto& reaction : reactions ) {

        if ( reaction.isPrimaryReaction() ) {

          pugi::xml_node reaction_node = reactions_node.append_child( "reaction" );
          reaction_node.append_attribute( "label" ) = reaction.identifier().symbol();
          if (  reaction.identifier().mt().has_value() ) {

            int mt = revertScatterLevel( projectile, target, reaction.identifier().mt().value() );
            reaction_node.append_attribute( "ENDF_MT" ) = mt;
          }

          //! @todo check the resonance parameters to see if we need to use background elements

          insertCrossSection( reaction_node, options, reaction.crossSection(), label );
          insertOutputChannel( reaction_node, options, reaction, label );
        }
      }
    }

    return reactions_node;
  }

} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
