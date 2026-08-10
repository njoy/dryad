#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTSPINGROUP
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTSPINGROUP

// system includes
#include <cmath>
#include <map>
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/insertChannels.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/insertResonanceParameters.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Insert a spin group node into a gnds node
   *
   *  @param[in,out] parent                   the parent node
   *  @param[in]     option                   the gnds write options
   *  @param[in]     group                    the spin group
   *  @param[in]     min                      the lower domain limit
   *  @param[in]     max                      the upper domain limit
   *  @param[in]     label                    the optional label for the node
   *  @param[in]     reducedWidthAmplitudes   use reduced width amplitudes (default is true)
   */
  inline pugi::xml_node
  insertSpinGroup( pugi::xml_node& parent,
                   const Options& options,
                   const dryad::resonances::SpinGroup& group,
                   double min,
                   double max,
                   const std::optional< std::string >& label = std::nullopt,
                   bool reducedWidthAmplitudes = true ) {

    auto toHalfIntegerString = [] ( const double a ) {

      double half;
      return std::modf( a, &half ) == 0. ?
                 // a is a full integer
                 std::to_string( static_cast< int >( half ) ) :
                 // a is a half integer value
                 std::to_string( 2 * static_cast< int >( half ) + 1 ) + "/2";
    };

    pugi::xml_node node = parent.append_child( "spinGroup" );
    node.append_attribute( "label" ) = ( toHalfIntegerString( group.totalAngularMomentum() )
                                         + ( group.parity() > 0 ? "+" : "-" ) ).c_str();
    node.append_attribute( "spin" ) = group.totalAngularMomentum();
    node.append_attribute( "parity" ) = group.parity() > 0 ? "+1" : "-1";

    insertChannels( node, options, group, min, max, label );
    insertResonanceParameters( node, options, group, reducedWidthAmplitudes );

    return node;
  }

} // rmatrix namespace
} // resonances namespace
} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
