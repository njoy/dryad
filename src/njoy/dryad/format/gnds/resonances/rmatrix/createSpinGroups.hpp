#ifndef NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATESPINGROUPS
#define NJOY_DRYAD_FORMAT_GNDS_RESONANCES_RMATRIX_CREATESPINGROUPS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/Formalism.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createBoundaryCondition.hpp"
#include "njoy/dryad/format/gnds/resonances/rmatrix/createChannelData.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace gnds {
namespace resonances {
namespace rmatrix {

  /**
   *  @brief Create the spin groups
   */
  inline auto createSpinGroups(
                  const dryad::resonances::Formalism& formalism,
                  const dryad::format::gnds::resonances::rmatrix::BoundaryCondition& boundary_condition,
                  const dryad::resonances::Kinematics& kinematics,
                  const dryad::format::gnds::resonances::rmatrix::ResonanceReactions& reactions,
                  const pugi::xml_node& spin_groups ) {

    // check that this is a valid spin groups node
    throwExceptionOnWrongNode( spin_groups, "spinGroups" );

    std::vector< dryad::resonances::SpinGroup > groups;

    // the boundary condition
    dryad::resonances::BoundaryCondition boundary = dryad::resonances::BoundaryCondition::ShiftFactor;
    if ( boundary_condition == dryad::format::gnds::resonances::rmatrix::BoundaryCondition::Constant ||
         boundary_condition == dryad::format::gnds::resonances::rmatrix::BoundaryCondition::NegativeOrbitalMomentum ) {

      boundary = dryad::resonances::BoundaryCondition::Constant;
    }

    // go over each spin group and collect all channel data - keep it sorted
    std::vector< dryad::resonances::SpinGroup::ChannelData > channel_data;
    for ( pugi::xml_node group = spin_groups.child( "spinGroup" );
          group; group = group.next_sibling( "spinGroup" ) ) {

      // get the channel data in this spin group
      auto data = createChannelData( boundary_condition, kinematics, reactions, group );

      // add each to the final channel data, keep it sorted and consolidate duplicate channels
      for ( auto&& channel : data ) {

        auto iter = std::lower_bound( channel_data.begin(), channel_data.end(),
                                      channel.first.identifier(),
                                      [] ( auto&& left, auto&& right )
                                         { return left.first.identifier() < right; } );
        if ( iter != channel_data.end() && iter->first.identifier() == channel.first.identifier() ) {

          iter->second += channel.second;
        }
        else {

          channel_data.insert( iter, std::move( channel ) );
        }
      }
    }

    // create the spin groups
    const auto getJpi = [] ( const auto& data ) {

      return std::make_tuple( data.first.quantumNumbers().totalAngularMomentum(),
                              data.first.quantumNumbers().parity() );
    };
    auto iter = channel_data.begin();
    while ( iter != channel_data.end() ) {

      // get all channel data for a given Jpi
      auto begin = iter;
      iter = std::upper_bound( begin, channel_data.end(),
                               getJpi( *begin ),
                               [&] ( auto&& left, auto&& right )
                                   { return left < getJpi( right ); } );

      std::vector< dryad::resonances::SpinGroup::ChannelData > data( begin, iter );
      groups.emplace_back( std::move( data ), formalism, boundary );
    }

    return groups;
  }

} // rmatrix namespace
} // resonances namespace
} // gnds namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
