#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFRESONCHANNELS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF7_CREATEENDFRESONCHANNELS

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/overload.hpp"
#include "njoy/constants.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf7 {

  /**
   *  @brief Create the channel information in a spin group for LRF7 resonance parameters
   *
   *  @param[in] group       the spin group
   *  @param[in] endfPairs   the ENDF particle pairs
   */
  inline auto createEndfResonanceChannels( const dryad::resonances::SpinGroup& group,
                                           const ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ParticlePairs& endfPairs ) {

    double aj = group.totalAngularMomentum() * group.parity();
    double parity = aj == 0. ? group.parity() : 0.;

    std::vector< unsigned int > ppi, l;
    std::vector< double > s, b, ape, apt;

    int kbk = 0;
    int kps = 0;

    auto get_radius= tools::overload{

      [] ( double radius ) -> double {

        return radius;
      },
      [] ( const auto& ) -> double {

        Log::error( "Tabulated channel radii are not compatible with ENDF" );
        throw std::exception();
      }
    };

    auto incident = group.channels().front().incidentParticlePair().lightParticle().identifier();

    for ( const auto& channel : group.channels() ) {

      auto iter = std::find( endfPairs.MT().begin(), endfPairs.MT().end(),
                             channel.reaction().reactionType() == id::ReactionType::elastic( incident )
                               ? 2
                               : channel.reaction().mt().value() );
      std::size_t index = std::distance( endfPairs.MT().begin(), iter ) + 1;

      ppi.push_back( index );
      l.push_back( channel.quantumNumbers().orbitalAngularMomentum() );
      s.push_back( channel.quantumNumbers().spin() );
      b.push_back( channel.boundaryCondition().value_or( 0. ) );

      apt.push_back( std::visit( get_radius, channel.channelRadii().penetrabilityRadius() ) );
      ape.push_back( std::visit( get_radius, channel.channelRadii().phaseShiftRadius().value_or( apt.back() ) ) );

      if ( channel.background().has_value() ) {

        ++kbk;
      }
    }

    // transform radius values from fm to 10^-12 cm
    auto convert_radius = [&] ( auto&& value ) { return value * constants::deci; };
    std::transform( apt.begin(), apt.end(), apt.begin(), convert_radius );
    std::transform( ape.begin(), ape.end(), ape.begin(), convert_radius );

    using ResonanceChannels = ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceChannels;
    return ResonanceChannels( aj, parity,
                              std::move( ppi ), std::move( l ), std::move( s ), std::move( b ),
                              std::move( apt ), std::move( ape ), kbk, kps );
  }


} // lrf7 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
