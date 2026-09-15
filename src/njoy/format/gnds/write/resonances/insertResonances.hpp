#ifndef NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTRESONANCES
#define NJOY_FORMAT_GNDS_WRITE_RESONANCES_INSERTRESONANCES

// system includes
#include <string>
#include <variant>

// other includes
#include "pugixml.hpp"
#include "tools/overload.hpp"
#include "njoy/dryad/ProjectileTarget.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/format/gnds/write/Options.hpp"
#include "njoy/format/gnds/write/resonances/rmatrix/insertRMatrix.hpp"
#include "njoy/format/gnds/write/resonances/insertScatteringRadius.hpp"

namespace njoy {
namespace format {
namespace gnds {
namespace write {
namespace resonances {

  /**
   *  @brief Find the default channel radii in the data
   *
   *  @param[in] resolved     the resolved resonance compound systems
   *  @param[in] unresolved   the optional unresolved resonance compound system
   */
  static dryad::resonances::ChannelRadii
  findRadii( const std::vector< dryad::resonances::CompoundSystem>& resolved,
             const std::optional< dryad::resonances::UnresolvedCompoundSystem >& unresolved ) {

    std::vector< dryad::resonances::ChannelRadii > radii;
    std::vector< std::size_t > frequency;

    for ( auto&& compound : resolved ) {

      for ( auto&& group : compound.spinGroups() ) {

        for ( auto&& channel : group.channels() ) {

          if ( channel.isIncidentChannel() ) {

            auto iter = std::find( radii.begin(), radii.end(), channel.channelRadii() );
            if ( iter == radii.end() ) {

              radii.emplace_back( channel.channelRadii() );
              frequency.emplace_back( 1 );
            }
            else {

              std::size_t index = std::distance( radii.begin(), iter );
              ++frequency[index];
            }
          }
        }
      }
    }

    if ( unresolved.has_value() ) {

      for ( auto&& group : unresolved->spinGroups() ) {

        for ( auto&& channel : group.channels() ) {

          if ( channel.isIncidentChannel() ) {

            auto iter = std::find( radii.begin(), radii.end(), channel.channelRadii() );
            if ( iter == radii.end() ) {

              radii.emplace_back( channel.channelRadii() );
              frequency.emplace_back( 1 );
            }
            else {

              std::size_t index = std::distance( radii.begin(), iter );
              ++frequency[index];
            }
          }
        }
      }
    }

    if ( radii.size() != 0 ) {

      auto iter = std::max_element( frequency.begin(), frequency.end() );
      std::size_t index = std::distance( frequency.begin(), iter );
      return radii[index];
    }
    else {

      return dryad::resonances::ChannelRadii( 0. );
    }
  }

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
      if ( ! pt.resonances()->hasParameters() ) {

        double radius = pt.resonances()->scatteringRadius().has_value()
                        ? pt.resonances()->scatteringRadius().value() : 0.;
        insertScatteringRadius( node, options, radius,
                                pt.resonances()->lowerEnergyLimit(), pt.resonances()->upperEnergyLimit(),
                                style );
      }
      else {

        auto radii = findRadii( pt.resonances()->resolved(), pt.resonances()->unresolved() );
        insertScatteringRadius( node, options, radii.penetrabilityRadius(),
                                pt.resonances()->lowerEnergyLimit(), pt.resonances()->upperEnergyLimit(),
                                style );

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

      //! @todo handle unresolved resonances
    }

    return node;
  }

} // resonances namespace
} // write namespace
} // gnds namespace
} // format namespace
} // njoy namespace

#endif
