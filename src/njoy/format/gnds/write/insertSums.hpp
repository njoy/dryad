#ifndef NJOY_FORMAT_GNDS_WRITE_INSERTSUMS
#define NJOY_FORMAT_GNDS_WRITE_INSERTSUMS

// system includes
#include <string>

// other includes
#include "pugixml.hpp"
#include "njoy/format/revertScatterLevel.hpp"
#include "njoy/format/gnds/write/insertCrossSectionSums.hpp"
#include "njoy/dryad/Reaction.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {

  /**
   *  @brief Insert a gnds sums node
   *
   *  @param[in,out] parent       the parent node
   *  @param[in]     option       the gnds write options
   *  @param[in]     reactions    the reactions
   *  @param[in]     resonances   the optional resonance parameters
   *  @param[in]     label        the style label to be used
   */
  inline pugi::xml_node
  insertSums( pugi::xml_node& parent,
              const Options& options,
              const std::vector< dryad::Reaction >& reactions,
              const std::optional< dryad::resonances::ResonanceParameters > resonances,
              const std::string& label ) {

    pugi::xml_node sums_node;

    auto is_cross_section_sum = [] ( auto&& reaction ) { return reaction.isSummationReaction(); };

    if ( std::any_of( reactions.begin(), reactions.end(), is_cross_section_sum ) ) {

      sums_node = parent.append_child( "sums" );
      insertCrossSectionSums( sums_node, options, reactions, resonances, label );
    }

    //! @todo multiplicity sums go here

    return sums_node;
  }

} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
