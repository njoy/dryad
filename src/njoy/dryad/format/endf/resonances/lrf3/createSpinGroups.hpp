#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF3_CREATESPINGROUP
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF3_CREATESPINGROUP

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/resonances/lrf3/createChannelData.hpp"
#include "ENDFtk/section/2/151.hpp"
#include <iostream>
namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf3 {

  /**
   *  @brief Create the spin groups for LRF3 resonance parameters
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] naps         the channel radius option as given in the ENDF file
   *  @param[in] nro          the energy dependent scattering radius (if defined, given in fm)
   *  @param[in] endf         the parsed ENDF LRF3 data
   */
  inline auto createSpinGroups( const id::ParticleID& projectile,
                                const id::ParticleID& target,
                                int naps,
                                const std::optional< dryad::resonances::TabulatedRadius >& nro,
                                const ENDFtk::section::Type< 2, 151 >::ReichMoore& endf ) {

    std::vector< dryad::resonances::SpinGroup > groups;

    // create all possible channel quantum numbers
    auto spin = endf.spin();
    auto nls = endf.numberLValues();
    auto available = dryad::resonances::ChannelQuantumNumbers::allowedChannelQuantumNumbers( 0.5, spin, nls );

    // the incident particle pair
    auto awri = endf.lValues().front().atomicWeightRatio();
    dryad::resonances::ParticlePair incident( dryad::resonances::Particle( projectile, constants::neutron_mass, 0.5, +1),
                                              dryad::resonances::Particle( target, awri * constants::neutron_mass, spin, +1) );

    // channel radius value
    auto ap = endf.scatteringRadius();

    // go over each l value and collect all channel data - keep it sorted
    std::vector< dryad::resonances::SpinGroup::ChannelData > channel_data;
    for ( const auto& lvalue : endf.lValues() ) {

      // get the channel data in this spin group
      auto data = lrf3::createChannelData( projectile, target, incident,
                                           naps, nro, ap, available, lvalue );

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
      groups.emplace_back( std::vector< dryad::resonances::SpinGroup::ChannelData >{ begin, iter },
                           dryad::resonances::Formalism::ReichMoore,
                           dryad::resonances::BoundaryCondition::ShiftFactor );
    }

    return groups;
  }

} // lrf3 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
