#ifndef NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDSCATTERINGFUNCTION
#define NJOY_DRYAD_FORMAT_ACE_CREATETABULATEDSCATTERINGFUNCTION

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "dryad/format/createVector.hpp"
#include "dryad/TabulatedScatteringFunction.hpp"
#include "ACEtk/photoatomic/CoherentFormFactorBlock.hpp"
#include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock.hpp"

namespace njoy {
namespace dryad {
namespace format {
namespace ace {

  /**
   *  @brief Create a TabulatedScatteringFunction from a CoherentFormFactorBlock
   */
  TabulatedScatteringFunction
  createTabulatedScatteringFunction( const njoy::ACEtk::photoatomic::CoherentFormFactorBlock& block ) {

    try {

      Log::info( "Reading scattering function data" );
      auto x = createVector( block.momentum() );
      auto values = createVector( block.formFactors() );
      std::vector< std::size_t > boundaries = { x.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      return TabulatedScatteringFunction(
               std::move( x ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated scattering function" );
      throw;
    }
  }

  /**
   *  @brief Create a TabulatedScatteringFunction from a CoherentFormFactorBlock
   */
  TabulatedScatteringFunction
  createTabulatedScatteringFunction( const njoy::ACEtk::photoatomic::IncoherentScatteringFunctionBlock& block ) {

    try {

      Log::info( "Reading scattering function data" );
      auto x = createVector( block.momentum() );
      auto values = createVector( block.values() );
      std::vector< std::size_t > boundaries = { x.size() - 1 };
      std::vector< InterpolationType > interpolants = { InterpolationType::LinearLinear };
      return TabulatedScatteringFunction(
               std::move( x ), std::move( values ),
               std::move( boundaries ), std::move( interpolants ) );
    }
    catch ( ... ) {

      Log::info( "Error encountered while creating a tabulated scattering function" );
      throw;
    }
  }

} // ace namespace
} // format namespace
} // dryad namespace
} // njoy namespace

#endif
