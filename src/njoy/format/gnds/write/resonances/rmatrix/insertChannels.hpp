#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTCHANNELS
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTCHANNELS

// system includes
#include <map>
#include <optional>
#include <string>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/resonances/insertScatteringRadius.hpp"
#include "njoy/format/gnds/write/resonances/insertHardSphereRadius.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/insertExternalRMatrix.hpp"

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
   *  @param[in]     group               the spin group
   *  @param[in]     min                 the lower domain limit
   *  @param[in]     max                 the upper domain limit
   *  @param[in]     label               the optional label for the node
   *  @param[in]     fullResonanceData   include all resonance data even if it is duplicated (default is true)
   */
  inline pugi::xml_node
  insertChannels( pugi::xml_node& parent,
                  const Options& options,
                  const dryad::resonances::SpinGroup& group,
                  double min,
                  double max,
                  const std::optional< std::string >& label = std::nullopt,
                  bool /*fullResonanceData*/ = true ) {

    pugi::xml_node node = parent.append_child( "channels" );
    for ( std::size_t i = 0; i < group.numberChannels(); ++i ) {

      decltype(auto) channel = group.channels()[i];

      pugi::xml_node channel_node = node.append_child( "channel" );
      channel_node.append_attribute( "label" ) = channel.identifier().symbol();
      channel_node.append_attribute( "resonanceReaction" ) = channel.reaction().symbol();
      channel_node.append_attribute( "L" ) = channel.quantumNumbers().orbitalAngularMomentum();
      channel_node.append_attribute( "channelSpin" ) = channel.quantumNumbers().spin();
      if ( group.boundaryCondition() == dryad::resonances::BoundaryCondition::Constant ) {

        channel_node.append_attribute( "boundaryConditionValue" ) = channel.boundaryCondition().value();
      }
      channel_node.append_attribute( "columnIndex" ) = i + 1;

      insertScatteringRadius( channel_node, options, channel.channelRadii().penetrabilityRadius(), min, max, label );
      if ( channel.channelRadii().hasPhaseShiftRadius() &&
           channel.channelRadii().phaseShiftRadius() != channel.channelRadii().penetrabilityRadius() ) {

        insertHardSphereRadius( channel_node, options, channel.channelRadii().phaseShiftRadius().value(), min, max, label );
      }

      if ( channel.hasBackground() ) {

        insertExternalRMatrix( channel_node, options, channel.background().value() );
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
