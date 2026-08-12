#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTCROSSSECTIONSUMS
#define NJOY_FORMAT_GNDS_WRITE_INSERTCROSSSECTIONSUMS

// system includes
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/revertScatterLevel.hpp"
#include "njoy/format/gnds/write/insertCrossSection.hpp"
#include "njoy/format/gnds/write/insertQ.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a gnds crossSectionSums node
   *
   *  @param[in,out] parent       the parent node
   *  @param[in]     option       the gnds write options
   *  @param[in]     reactions    the reactions
   *  @param[in]     resonances   the optional resonance parameters
   *  @param[in]     style        the style label to be used
   */
  inline pugi::xml_node
  insertCrossSectionSums( pugi::xml_node& parent,
                          const Options& options,
                          const std::vector< dryad::Reaction >& reactions,
                          const std::optional< dryad::resonances::ResonanceParameters > resonances,
                          const std::string& style ) {

    pugi::xml_node sums_node;

    auto projectile = reactions.front().identifier().projectile();
    auto target = reactions.front().identifier().target();

    auto is_cross_section_sum = [] ( auto&& reaction ) { return reaction.isSummationReaction(); };

    if ( std::any_of( reactions.begin(), reactions.end(), is_cross_section_sum ) ) {

      sums_node = parent.append_child( "crossSectionSums" );

      for ( const auto& reaction : reactions ) {

        if ( reaction.isSummationReaction() ) {

          pugi::xml_node sum_node = sums_node.append_child( "crossSectionSum" );
          sum_node.append_attribute( "label" ) = reaction.identifier().symbol();
          if (  reaction.identifier().mt().has_value() ) {

            int mt = revertScatterLevel( projectile, target, reaction.identifier().mt().value() );
            sum_node.append_attribute( "ENDF_MT" ) = mt;
          }

          pugi::xml_node summands_node = sum_node.append_child( "summands" );
          for ( const auto& partial : reaction.partialReactionIdentifiers().value() ) {

            pugi::xml_node add_node = summands_node.append_child( "add" );
            add_node.append_attribute( "href" ) = "/reactionSuite/reactions/reaction[@label=\'" + partial.symbol() + "\']/crossSection";
          }

          //! @todo check the resonance parameters to see if we need to use background elements

          insertCrossSection( sum_node, options, reaction.crossSection(), style );
        }
      }
    }

    return sums_node;
  }

} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
