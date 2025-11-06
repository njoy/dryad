#ifndef NJOY_DRYAD_FORMAT_ENDF_RESONANCES_CREATERESONANCEPARAMETERS
#define NJOY_DRYAD_FORMAT_ENDF_RESONANCES_CREATERESONANCEPARAMETERS

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/dryad/format/endf/resonances/lrf7/createCompoundSystem.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace endf {
namespace resonances {

  /**
   *  @brief Create the resonance parameters from a parsed ENDF section
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] section      the parsed MF2 MT151 section
   */
  inline std::optional< dryad::resonances::ResonanceParameters >
  createResonanceParameters( const id::ParticleID& projectile,
                             const id::ParticleID& target,
                             const ENDFtk::section::Type< 2, 151 >& section ) {

    std::vector< dryad::resonances::CompoundSystem > resolved;

    for ( const auto& range : section.isotopes().front().resonanceRanges() ) {

      double lower = range.lowerEnergy();
      double upper = range.upperEnergy();

      if ( range.type() == 1 ) {

        Log::info( "Reading resolved resonance region between {} and {} eV", lower, upper );
        switch ( range.representation() ) {

          case 7 : {

            decltype(auto) parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >( range.parameters() );
            resolved.emplace_back( lrf7::createCompoundSystem( projectile, target, lower, upper, parameters ) );
            break;
          }
          default : {

            Log::info( "  Resolved formalism {} is currently uinsupported, skipping", range.representation() );
            continue;
          }
        }
      }
      else {

        Log::info( "Reading unresolved resonance region between {} and {} eV", lower, upper );
        Log::info( "  Unresolved formalism {} is currently uinsupported, skipping", range.representation() );
      }
    }

    if ( resolved.size() != 0 ) {

      return dryad::resonances::ResonanceParameters( std::move( resolved ) );
    }
    else {

      return std::nullopt;
    }
  }

} // resonances namespace
} // endf namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
