#ifndef NJOY_FORMAT_ENDF_READ_RESONANCES_CREATERESONANCEPARAMETERS
#define NJOY_FORMAT_ENDF_READ_RESONANCES_CREATERESONANCEPARAMETERS

// system includes
#include <optional>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "njoy/dryad/resonances/ResonanceParameters.hpp"
#include "njoy/format/endf/read/resonances/createTabulatedRadius.hpp"
#include "njoy/format/endf/read/resonances/lrf3/createCompoundSystem.hpp"
#include "njoy/format/endf/read/resonances/lrf7/createCompoundSystem.hpp"
#include "njoy/format/endf/read/resonances/urr/caseA/createCompoundSystem.hpp"
#include "njoy/format/endf/read/resonances/urr/caseB/createCompoundSystem.hpp"
#include "njoy/format/endf/read/resonances/urr/caseC/createCompoundSystem.hpp"
#include "ENDFtk/section/2/151.hpp"

namespace njoy {
namespace format {
namespace endf {
namespace read {
namespace resonances {

  /**
   *  @brief Create the resonance parameters from a parsed ENDF section
   *
   *  @param[in] projectile   the projectile identifier
   *  @param[in] target       the target identifier
   *  @param[in] section      the parsed MF2 MT151 section
   */
  inline std::optional< dryad::resonances::ResonanceParameters >
  createResonanceParameters( const dryad::id::ParticleID& projectile,
                             const dryad::id::ParticleID& target,
                             const ENDFtk::section::Type< 2, 151 >& section ) {

    double lowerEnergy;
    double upperEnergy;
    std::optional< double > radius = std::nullopt;
    std::vector< dryad::resonances::CompoundSystem > resolved;
    std::optional< dryad::resonances::UnresolvedCompoundSystem > unresolved = std::nullopt;

    for ( const auto& range : section.isotopes().front().resonanceRanges() ) {

      double lower = range.lowerEnergy();
      double upper = range.upperEnergy();

      auto naps = range.scatteringRadiusCalculationOption();
      std::optional< dryad::resonances::TabulatedRadius > nro = std::nullopt;
      if ( range.scatteringRadius().has_value() ) {

        nro = createTabulatedRadius( range.scatteringRadius().value() );
      }

      if ( range.type() == 0 ) {

        Log::info( "Reading scattering radius between {} and {} eV", lower, upper );
        decltype(auto) parameters = std::get< njoy::ENDFtk::section::Type<2,151>::SpecialCase >( range.parameters() );

        lowerEnergy = lower;
        upperEnergy = upper;
        radius = parameters.scatteringRadius() * constants::deca;
      }
      else if ( range.type() == 1 ) {

        Log::info( "Reading resolved resonance region between {} and {} eV", lower, upper );
        switch ( range.representation() ) {

          case 3 : {

            decltype(auto) parameters = std::get< njoy::ENDFtk::section::Type<2,151>::ReichMoore >( range.parameters() );
            resolved.emplace_back( lrf3::createCompoundSystem( projectile, target, lower, upper, naps, nro, parameters ) );
            break;
          }
          case 7 : {

            decltype(auto) parameters = std::get< njoy::ENDFtk::section::Type<2,151>::RMatrixLimited >( range.parameters() );
            resolved.emplace_back( lrf7::createCompoundSystem( projectile, target, lower, upper, parameters ) );
            break;
          }
          default : {

            Log::info( "  Resolved formalism {} is currently unsupported, skipping", range.representation() );
            continue;
          }
        }
      }
      else {

        Log::info( "Reading unresolved resonance region between {} and {} eV", lower, upper );
        if ( range.representation() == 1 && ! range.averageFissionWidthFlag() ) {

          // Case A: energy-independent unresolved parameters (LRF = 1, LFW = 0)
          decltype(auto) parameters = std::get< njoy::ENDFtk::section::Type<2,151>::UnresolvedEnergyIndependent >( range.parameters() );
          unresolved = urr::caseA::createCompoundSystem( projectile, target, lower, upper, naps, nro, parameters );
        }
        else if ( range.representation() == 1 && range.averageFissionWidthFlag() ) {

          // Case B: energy-dependent-fission-width unresolved parameters (LRF = 1, LFW = 1)
          decltype(auto) parameters = std::get< njoy::ENDFtk::section::Type<2,151>::UnresolvedEnergyDependentFissionWidths >( range.parameters() );
          unresolved = urr::caseB::createCompoundSystem( projectile, target, lower, upper, naps, nro, parameters );
        }
        else if ( range.representation() == 2 ) {

          // Case C: fully energy-dependent unresolved parameters (LRF = 2)
          decltype(auto) parameters = std::get< njoy::ENDFtk::section::Type<2,151>::UnresolvedEnergyDependent >( range.parameters() );
          unresolved = urr::caseC::createCompoundSystem( projectile, target, lower, upper, naps, nro, parameters );
        }
        else {

          Log::info( "  Unresolved formalism LRF = {}, LFW = {} is currently unsupported, skipping",
                     range.representation(), range.averageFissionWidthFlag() );
          continue;
        }
      }
    }

    if ( resolved.size() != 0 || unresolved.has_value() ) {

      return dryad::resonances::ResonanceParameters( std::move( resolved ), std::move( unresolved ) );
    }
    else if ( radius.has_value() ) {

      return dryad::resonances::ResonanceParameters( lowerEnergy, upperEnergy, radius.value() );
    }
    else {

      return std::nullopt;
    }
  }

} // resonances namespace
} // read namespace
} // endf namespace
} // format namespace
} // njoy namespace

#endif
