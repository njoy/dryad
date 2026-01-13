#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATESPINGROUP
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATESPINGROUP

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/resonances/moveCaptureToFront.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createBoundaryCondition.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createChannelData.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the spin groups for LRF7 resonance parameters
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] formalism    the formalism to be applied
   *  @param[in] boundary     the boundary condition to be applied
   *  @param[in] kinematics   the kinematics type to be applied
   *  @param[in] endf         the parsed ENDF LRF7 data
   */
  inline auto createSpinGroups( const id::ParticleID& projectile,
                                const id::ParticleID& target,
                                const dryad::resonances::Formalism& formalism,
                                const dryad::resonances::BoundaryCondition& boundary,
                                const dryad::resonances::Kinematics& kinematics,
                                const ENDFtk::section::Type< 2, 151 >::RMatrixLimited& endf ) {

    std::vector< dryad::resonances::SpinGroup > groups;

    // check the type of resonances
    bool reduced_amplitudes = endf.reducedWidths();

    // determine the boundary condition
    auto boundary_condition = lrf7::createBoundaryCondition( endf.particlePairs() );

    // go over each spin group and collect all channel data - keep it sorted
    std::vector< dryad::resonances::SpinGroup::ChannelData > channel_data;
    for ( const auto& group : endf.spinGroups() ) {

      // get the channel data in this spin group
      auto data = lrf7::createChannelData( projectile, target, boundary_condition,
                                           kinematics, reduced_amplitudes,
                                           endf.particlePairs(), group );

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

} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
