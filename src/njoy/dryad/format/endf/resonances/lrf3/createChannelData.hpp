#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF3_CREATECHANNELDATA
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_LRF3_CREATECHANNELDATA

// system includes
#include <algorithm>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/id/ReactionID.hpp"
#include "njoy/dryad/id/ChannelID.hpp"
#include "njoy/dryad/resonances/SpinGroup.hpp"
#include "njoy/dryad/format/createVector.hpp"
#include "njoy/dryad/format/endf/resonances/createChannelRadii.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {
namespace lrf3 {

  inline dryad::resonances::ChannelQuantumNumbers
  retrieveQuantumNumber( unsigned int l, double j,
                         std::vector< dryad::resonances::ChannelQuantumNumbers >& available ) {

    auto find = [l,j] ( auto&& numbers ) {

      return numbers.orbitalAngularMomentum() == l &&
             numbers.totalAngularMomentum() == std::abs( j );
    };

    auto first = std::find_if( available.begin(), available.end(), find );
    if ( first != available.end() ) {

      auto second = std::find_if( first, available.end(), find );
      if ( second != available.end() ) {

        if ( j > 0 ) {

          first = second;
        }
      }

      auto numbers = *first;
      available.erase( first );
      return numbers;
    }
    else {

      throw std::runtime_error( "None of the expected spin groups has l = "
                                + std::to_string( l ) + " and J = "
                                + std::to_string( std::abs( j ) ) );
    }
  }

  /**
   *  @brief Create the channel data for Reich-Moore data for a given l value
   *
   *  @param[in] projectile             the projectile identifier
   *  @param[in] target                 the target identifier
   *  @param[in] incident               the incident particle pair
   *  @param[in] naps                   the channel radius option as given in the ENDF file
   *  @param[in] nro                    the energy dependent scattering radius (if defined, given in fm)
   *  @param[in] ap                     the l-dependent scattering radius (if defined, given in fm)
   *  @param[in,out] available          the quantum number combinations that are still available
   *  @param[in] endfReichMooreLValue   the parsed ENDF Reich-Moore l-value data
   */
  inline auto createChannelData(
                  const id::ParticleID& projectile,
                  const id::ParticleID& target,
                  const dryad::resonances::ParticlePair& incident,
                  int naps,
                  const std::optional< dryad::resonances::TabulatedRadius >& nro,
                  double ap,
                  std::vector< dryad::resonances::ChannelQuantumNumbers >& available,
                  const ENDFtk::section::Type< 2, 151 >::ReichMooreLValue& endfReichMooreLValue ) {

    std::vector< dryad::resonances::SpinGroup::ChannelData > channel_data;

    unsigned int l = endfReichMooreLValue.orbitalMomentum();
    double apl = endfReichMooreLValue.lDependentScatteringRadius() * constants::deca;
    double awri = endfReichMooreLValue.atomicWeightRatio();

    // create the channel radii (check for l-dependent radius)
    dryad::resonances::ChannelRadii radii = createChannelRadii( naps, nro, apl != 0. ? apl : ap, awri );

    // get all possible total angular momentum values
    std::vector< double > jvalues = createVector( endfReichMooreLValue.spinValues() );
    std::sort( jvalues.begin(), jvalues.end() );
    jvalues.erase( std::unique( jvalues.begin(), jvalues.end() ), jvalues.end() );

    // lambda to calculate reduced width
    auto reduced_width = [] ( auto&& width, auto&& penetrability ) {

      int sign = width >= 0. ? +1 : -1;
      return sign * std::sqrt( std::abs( width ) / 2. / penetrability );
    };

    // go over each one to create channel data
    for ( double j : jvalues ) {

      // elastic channel
      id::ChannelID elastic_id( id::ReactionID( projectile, target, 2 ),
                                retrieveQuantumNumber( l, j, available ) );
      dryad::resonances::Channel elastic( elastic_id, incident, incident, 0., std::nullopt, radii );

      // collect level energies and widths
      std::vector< double > energies;
      std::vector< double > elastic_widths;
      std::vector< double > capture_widths;
      std::vector< double > fission1_widths;
      std::vector< double > fission2_widths;

      // go over all resonances
      for ( unsigned int i = 0; i < endfReichMooreLValue.numberResonances(); ++i ) {

        if ( endfReichMooreLValue.spinValues()[i] == j ) {

          energies.emplace_back( endfReichMooreLValue.resonanceEnergies()[i] );
          elastic_widths.emplace_back( reduced_width( endfReichMooreLValue.neutronWidths()[i],
                                                      elastic.penetrability( energies.back() ) ) );
          capture_widths.emplace_back( reduced_width( endfReichMooreLValue.gammaWidths()[i], 1. ) );
          fission1_widths.emplace_back( reduced_width( endfReichMooreLValue.firstFissionWidths()[i], 1. ) );
          fission2_widths.emplace_back( reduced_width( endfReichMooreLValue.secondFissionWidths()[i], 1. ) );
        }
      }

      // treat elastic
      channel_data.emplace_back( std::move( elastic ), dryad::resonances::ResonanceTable{ { elastic_id }, energies, std::move( elastic_widths ) } );

      // treat capture
      dryad::resonances::ChannelQuantumNumbers other( l, 0, std::abs( j ), l%2 == 0 ? +1 : -1 );
      id::ChannelID capture_id( id::ReactionID( projectile, target, 102 ), other );
      dryad::resonances::ParticlePair capture_pair( { id::ParticleID::photon(), 0., 0., +1 },
                                                    { capture_id.reaction().residual().value(), 0., 0., +1 } );
      dryad::resonances::Channel capture( capture_id, incident, capture_pair, 0., std::nullopt, radii );
      channel_data.emplace_back( std::move( capture ), dryad::resonances::ResonanceTable{ { capture_id }, energies, std::move( capture_widths ) } );

      // check for fission
      auto is_non_zero = [] ( auto&& value ) { return value != 0.; };
      bool has_fission1 = std::any_of( fission1_widths.begin(), fission1_widths.end(), is_non_zero );
      bool has_fission2 = std::any_of( fission2_widths.begin(), fission2_widths.end(), is_non_zero );
      if ( has_fission1 && has_fission2 ) {

        id::ChannelID fission1_id( id::ReactionID( projectile, target, 18 ), other, 0 );
        id::ChannelID fission2_id( id::ReactionID( projectile, target, 18 ), other, 1 );
        dryad::resonances::Channel fission1( fission1_id, incident, std::nullopt, 0., std::nullopt, radii );
        dryad::resonances::Channel fission2( fission2_id, incident, std::nullopt, 0., std::nullopt, radii );
        channel_data.emplace_back( std::move( fission1 ), dryad::resonances::ResonanceTable{ { fission1_id }, energies, std::move( fission1_widths ) } );
        channel_data.emplace_back( std::move( fission2 ), dryad::resonances::ResonanceTable{ { fission2_id }, energies, std::move( fission2_widths ) } );

      }
      else if ( has_fission1 || has_fission2 ) {

        id::ChannelID fission_id( id::ReactionID( projectile, target, 18 ), other );
        dryad::resonances::Channel fission( fission_id, incident, std::nullopt, 0., std::nullopt, radii );
        if ( has_fission1 ) {

          channel_data.emplace_back( std::move( fission ), dryad::resonances::ResonanceTable{ { fission_id }, energies, std::move( fission1_widths ) } );
        }
        else {

          channel_data.emplace_back( std::move( fission ), dryad::resonances::ResonanceTable{ { fission_id }, energies, std::move( fission2_widths ) } );
        }
      }
    }

    return channel_data;
  }

} // lrf3 namespace
} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
